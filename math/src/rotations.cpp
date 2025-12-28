#include "rotations.h"

namespace kbm
{
	// TODO: Euler -> Macierz obrotu
	Mat4 EulerZXZRotation(const Vec3& anglesDeg)
	{
		// x <=> alpha (second Z)
		// y <=> beta (X)
		// z <=> gamma (first Z)

		return EulerZXZRotation(anglesDeg.x, anglesDeg.y, anglesDeg.z);
	}

	Mat4 EulerZXZRotation(float alphaDeg, float betaDeg, float gammaDeg)
	{
		// ZXZ convention
		// 
		// 1. rotate by alpha around Z
		// 2. rotate by beta around rotated X
		// 3. rotate by gamma around rotated Z
		// 
		// in scene's frame angles reversed:
		// first gamma round Z, then beta around X, then alpha around Z

		float c_alpha = cos(Radians(alphaDeg));
		float s_alpha = sin(Radians(alphaDeg));
		float c_beta = cos(Radians(betaDeg));
		float s_beta = sin(Radians(betaDeg));
		float c_gamma = cos(Radians(gammaDeg));
		float s_gamma = sin(Radians(gammaDeg));

		Mat4 rot = Identity();

		rot(0, 0) = c_alpha * c_gamma - c_beta * s_alpha * s_gamma;
		rot(0, 1) = -c_alpha * s_gamma - c_beta * c_gamma * s_alpha;
		rot(0, 2) = s_alpha * s_beta;

		rot(1, 0) = c_gamma * s_alpha + c_alpha * c_beta * s_gamma;
		rot(1, 1) = -s_alpha * s_gamma + c_alpha * c_beta * c_gamma;
		rot(1, 2) = -c_alpha * s_beta;

		rot(2, 0) = s_beta * s_gamma;
		rot(2, 1) = c_gamma * s_beta;
		rot(2, 2) = c_beta;

		return rot;
	}

	kbm::Mat4 RotationX(float angleDeg)
	{
		return EulerZXZRotation(0, angleDeg, 0);
	}

	kbm::Mat4 RotationY(float angleDeg)
	{
		return EulerZXZRotation(90.0f, angleDeg, -90.0f);
	}

	kbm::Mat4 RotationZ(float angleDeg)
	{
		return EulerZXZRotation(angleDeg, 0.0f, 0.0f);
	}

	// TODO: Kwaternion -> Macierz obrotu
	Mat4 QuatRotation(const Quat& q)
	{
		float w = q.w, x = q.x, y = q.y, z = q.z;

		Mat4 mat = Identity();
		mat(0, 0) = 1 - 2 * (y * y + z * z);
		mat(0, 1) = 2 * (x * y - w * z);
		mat(0, 2) = 2 * (x * z + w * y);

		mat(1, 0) = 2 * (x * y + w * z);
		mat(1, 1) = 1 - 2 * (x * x + z * z);
		mat(1, 2) = 2 * (y * z - w * x);

		mat(2, 0) = 2 * (x * z - w * y);
		mat(2, 1) = 2 * (y * z + w * x);
		mat(2, 2) = 1 - 2 * (x * x + y * y);

		return mat;
	}

	// TODO: Euler -> Kwaternion
	kbm::Quat EulerZXZToQuat(float alphaDeg, float betaDeg, float gammaDeg)
	{
		return kbm::Normalize(
			kbm::FromAxisAngle(alphaDeg, { 0,0,1 })
			* kbm::FromAxisAngle(betaDeg, { 1,0,0 })
			* kbm::FromAxisAngle(gammaDeg, { 0,0,1 })
		);
	}

	kbm::Quat EulerZXZToQuat(const Vec3& anglesDeg)
	{
		return EulerZXZToQuat(anglesDeg.x, anglesDeg.y, anglesDeg.z);
	}

	// TODO: Kwaternion -> Euler
	kbm::Vec3 QuatToEulerZXZ(const Quat& q)
	{
		// rotation matrix
		auto rot = QuatRotation(q);
		
		// matrix => euler zxz
		auto alpha = atan2(rot(0, 2), -rot(1, 2));
		auto beta = atan2(rot(0, 2) * sin(alpha) - rot(1, 2) * cos(alpha), rot(2, 2));
		auto gamma = atan2(-rot(0, 1) * cos(alpha) - rot(1, 1) * sin(alpha), rot(0, 0) * cos(alpha) + rot(1, 0) * sin(alpha));
		
		return { Degrees(alpha), Degrees(beta), Degrees(gamma) };
	}

}