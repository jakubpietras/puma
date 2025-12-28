#pragma once
#include "UI/UIPanel.h"
#include "Core/AppState.h"
#include "Puma/PumaParams.h"

namespace kb
{
	class ConfigPanel : public UIPanel
	{
	public:
		ConfigPanel(AppState& appstate);
		void Render() override;

	private:
		AppState& m_State;

		void RenderPositionControl();
		void RenderQuaternionControl();
		void RenderEulerControl();
		void RenderLengthsControl();
		void RenderAnimationControl();
	};
}