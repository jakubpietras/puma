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
	};
}