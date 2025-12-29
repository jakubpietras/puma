#include "IKSolver.h"

namespace kb
{

	kb::PUMAState IKSolver::Compute(kbm::Vec3 pos, kbm::Mat4 rotation)
	{
		PUMAState s;
		return s;
	}

	float IKSolver::Angle(kbm::Vec3 v, kbm::Vec3 w)
	{
		auto dot = kbm::Dot(v, w);
		auto denom = kbm::Length(v) * kbm::Length(w);
		return dot / denom;
	}

	//kb::PUMAState BaseScene::ComputeIK(kbm::Vec3 effPos, kbm::Mat4 effRot)
	//{
	//	auto x5 = kbm::Vec3(effRot * kbm::Vec4{ 1.0f, 0.0f, 0.0f, 0.f });
	//	auto y5 = kbm::Vec3(effRot * kbm::Vec4{ 0.0f, 1.0f, 0.0f, 0.f });

	//	auto p5 = effPos;
	//	auto p0 = kbm::Vec3{ 0.f, 0.f, 0.f };
	//	auto p1 = p0;
	//	auto p2 = p0 + kbm::Vec3{ 0.f, m_State.Params.Length1, 0.f };
	//	auto p4 = p5 - m_State.Params.Length4 * x5;

	//	auto n024 = kbm::Normalize(kbm::Cross(p4 - p0, p2 - p0));
	//	auto y4 = kbm::Normalize(kbm::Cross(n024, x5));
	//	// todo: handle edge cases
	//	auto p3 = p4 + m_State.Params.Length3 * y4;

	//	// angles
	//	auto halfPi = static_cast<float>(std::numbers::pi / 2);
	//	auto a1 = static_cast<float>(atan2(p3.z, p3.x));
	//	auto a2 = Angle(p2 - p0, p3 - p2) - halfPi;
	//	auto q2 = kbm::Length(p3 - p2);
	//	auto a3 = Angle(p3 - p2, p4 - p3) - halfPi;
	//	auto a4 = Angle(n024, x5) + halfPi;
	//	auto a5 = Angle(p3 - p4, y5);

	//	PUMAState s;
	//	s.a = { kbm::Degrees(a1), kbm::Degrees(a2), kbm::Degrees(a3), kbm::Degrees(a4), kbm::Degrees(a5) };
	//	s.l = { m_State.Params.Length1, q2, m_State.Params.Length3, m_State.Params.Length4 };
	//	s.p = { p1, p2, p3, p4, p5 };
	//	return s;
	//}

}