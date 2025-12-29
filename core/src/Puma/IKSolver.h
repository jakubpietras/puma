#pragma once
#include "PUMAStructs.h"

namespace kb
{
	class IKSolver
	{
	public:
		static PUMAState Compute(kbm::Vec3 pos, kbm::Mat4 rotation);

	private:
		float Angle(kbm::Vec3 v, kbm::Vec3 w);

	};
}