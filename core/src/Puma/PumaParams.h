#pragma once
#include "kbmath.h"

namespace kb
{
	struct PumaParams
	{
		kbm::Vec3 EffStartPos, EffEndPos;	// effector's position
		kbm::Vec3 EulerStart, EulerEnd;		// effector's local rotation (euler)
		kbm::Quat QuatStart, QuatEnd;		// effector's local rotation (quaternion)
		float Length1 = 1.0f, Length3 = 1.0f, Length4 = 1.0f;
	};
}