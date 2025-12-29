#pragma once
#include "Core/Core.h"
#include "kbmath.h"
#include "Puma/PUMAStructs.h"

namespace kb
{
	struct AppState
	{
		PUMAParams Params{};
		PUMADirtyFlag DirtyPUMA{};

		// Simulation
		float AnimationTotalTime = 1.0f;
		float AnimationElapsedTime = 0.0f;
		bool AnimationTotalTimeChanged = false;
		bool AnimationStarted = false;
		bool AnimationPaused = false;
	};
}