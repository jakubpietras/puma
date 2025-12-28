#pragma once
#include "kbmath.h"

namespace kb
{
	struct Arm
	{
		float Length = 1.f;
		kbm::Vec3 Origin;
		kbm::Vec3 RotationAxis;
		float Angle = 0.f;
	};

	struct Effector
	{
		kbm::Vec3 p;
		float a;
	};

	struct PUMAState
	{
		std::array<float, 5> a{};			// rotations
		std::array<kbm::Vec3, 5> p{};		// origin points
		std::array<float, 4> l{};			// arm lengths
	};

}