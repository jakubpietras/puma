#include "IKSolver.h"
#include <numbers>


namespace kb
{

	kb::PUMAState IKSolver::Compute(kbm::Vec3 pos, kbm::Mat4 rotation, std::vector<float> armLengths, std::optional<kb::PUMAState> prevState)
	{
		PUMAState s;
		auto x5 = kbm::Vec3(rotation * kbm::Vec4{ 1.0f, 0.0f, 0.0f, 0.f });

		auto p5 = pos;
		auto p0 = kbm::Vec3{ 0.f, 0.f, 0.f };
		auto p1 = p0;
		auto p2 = p0 + kbm::Vec3{ 0.f, armLengths[0], 0.f };
		auto p4 = p5 - armLengths[2] * x5;

		auto n024 = kbm::Cross(p4 - p0, p2 - p0);
		if (kbm::Length(n024) < 1e-6) // edge case: cross product == 0
		{
			if (prevState.has_value())
			{
				// previous n024 won't be zero since it's handled here
				auto& p4p = prevState->p[3], & p2p = prevState->p[1];
				n024 = kbm::Normalize(kbm::Cross(p4p - p0, p2p - p0));
			}
			else
			{
				// first/last frame
				n024 = kbm::Cross(p5 - p4, p0 - p4);
				if (kbm::Length(n024) < 1e-6) // p0/1/2/4/5 all in one line - choosing any vector
					n024 = kbm::Vec3(0.0f, 0.0f, 1.0f);	
				else
					n024 = kbm::Normalize(n024);
			}
		}
		else
			n024 = kbm::Normalize(n024);
		
		auto y4 = kbm::Cross(n024, x5);
		if (kbm::Length(y4) < 1e-6) // edge case: cross product == 0
			y4 = kbm::Normalize(p2 - p4);	// p4-p3 and p2-p3 lie on the same line
		else
			y4 = kbm::Normalize(y4);

		// choosing p3 to be the closest to previous configuration
		kbm::Vec3 p3;
		if (prevState.has_value())
		{
			auto p31 = p4 + armLengths[1] * y4;
			auto p32 = p4 - armLengths[1] * y4;
			p3 =
				(kbm::LengthSquared(prevState->p[2] - p31) >= kbm::LengthSquared(prevState->p[2] - p32))
				? p32 : p31;
		}
		else
			p3 = p4 + armLengths[1] * y4;	// without previous state always choose the "up" way
		
		// angles
		auto halfPi = static_cast<float>(std::numbers::pi / 2);
		float a1;
		float p4L = p4.x * p4.x + p4.z * p4.z;
		if (p4L < 1e-12)
		{
			if (prevState.has_value())
				a1 = kbm::Radians(prevState->a[0]);
			else
				a1 = 0.0f;
		}
		else
		{
			a1 = -static_cast<float>(atan2(p4.z, p4.x));
		}

		auto a2 = SignedAngle(p2 - p0, p3 - p2, n024);
		auto q2 = kbm::Length(p3 - p2);
		auto a3 = SignedAngle(p3 - p2, p3 - p4, n024);
		auto a4 = SignedAngle(n024, p5-p4, p3-p4) - halfPi;
		auto a5 = SignedAngle(p3 - p4, y5, p5-p4);

		s.a = { kbm::Degrees(a1), kbm::Degrees(a2), kbm::Degrees(a3), kbm::Degrees(a4), kbm::Degrees(a5) };
		s.l = { armLengths[0], q2, armLengths[1], armLengths[2] };
		s.p = { p1, p2, p3, p4, p5 };
		return s;
	}

	float IKSolver::SignedAngle(kbm::Vec3 a, kbm::Vec3 b, kbm::Vec3 rotAxis)
	{
		return std::atan2(
			kbm::Dot(kbm::Cross(a, b), kbm::Normalize(rotAxis)),
			kbm::Dot(a, b)
		);
	}
}