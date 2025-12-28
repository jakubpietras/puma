#pragma once
#include "matrix_types.h"
#include "quaternion.h"

namespace kbm
{
	// => ROTATION MATRIX
	Mat4 EulerZXZRotation(const Vec3& angles);
	Mat4 EulerZXZRotation(float phi, float theta, float psi);
	Mat4 RotationX(float angleDeg);
	Mat4 RotationY(float angleDeg);
	Mat4 RotationZ(float angleDeg);
	Mat4 QuatRotation(const Quat& q);

	// EULER => QUATERNION
	Quat EulerZXZToQuat(const Vec3& angles);
	Quat EulerZXZToQuat(float phi, float theta, float psi);

	// QUATERNION => EULER
	Vec3 QuatToEulerZXZ(const Quat& q);

	// MATRIX => EULER
	Vec3 MatToEulerZXZ(Mat4 rotation);
}