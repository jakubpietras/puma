#pragma once
#include "PUMAStructs.h"
#include <optional>

namespace kb
{
	class IKSolver
	{
	public:
		static PUMAState Compute(kbm::Vec3 pos, kbm::Mat4 rotation, std::vector<float> armLengths, std::optional<kb::PUMAState> prevState = std::nullopt);

	private:
		static float Angle(kbm::Vec3 v, kbm::Vec3 w);
		static float SignedAngle(kbm::Vec3 a, kbm::Vec3 b, kbm::Vec3 rotAxis);
	};
}