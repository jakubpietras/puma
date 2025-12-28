#pragma once
#include "Configuration.h"
#include <optional>

namespace kb
{
	class PUMASolver
	{
	public:
		static PUMAState ComputeIK(const Effector& effector, std::optional<PUMAState> prevSolution = std::nullopt);
	};
}