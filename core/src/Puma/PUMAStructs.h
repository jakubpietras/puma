#pragma once
#include "kbmath.h"

namespace kb
{
	// PUMAParams is for UI controls
	struct PUMAParams
	{
		kbm::Vec3 EffStartPos, EffEndPos;	// effector's position
		kbm::Vec3 EulerStart, EulerEnd;		// effector's local rotation (euler)
		kbm::Quat QuatStart, QuatEnd;		// effector's local rotation (quaternion)
		float Length1 = 3.0f, Length3 = 2.0f, Length4 = 0.5f;
	};

	// PUMAState holds a full configuration of the robot
	struct PUMAState
	{
		std::array<float, 5> a{};			// rotations
		std::array<kbm::Vec3, 5> p{};		// origin points
		std::array<float, 4> l{};			// arm lengths
	};

	// PUMADirtyFlag is self explanatory
	struct PUMADirtyFlag
	{
		bool StartPos = false, EndPos = false;
		bool EulerStart = false, EulerEnd = false;
		bool QuatStart = false, QuatEnd = false;
		bool Lengths = false;
		bool Check() const { return StartPos || EndPos || EulerStart || EulerEnd || QuatStart || QuatEnd || Lengths; }
		void Clear() {
			StartPos = EndPos = EulerStart = EulerEnd = QuatStart = QuatEnd = Lengths = false;
		}
	};
}