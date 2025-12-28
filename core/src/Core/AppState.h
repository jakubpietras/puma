#pragma once
#include "Core/Core.h"
#include "kbmath.h"
#include "Puma/PumaParams.h"

namespace kb
{
	struct AppState
	{
		PumaParams Params{};
		PumaDirtyFlag DirtyPuma{};

		// Simulation
		float AnimationTotalTime = 1.0f;
		float AnimationElapsedTime = 0.0f;
		bool AnimationTotalTimeChanged = false;
		bool AnimationStarted = false;
		bool AnimationPaused = false;
	};
}