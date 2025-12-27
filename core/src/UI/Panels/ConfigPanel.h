#pragma once
#include "UI/UIPanel.h"
#include "Core/AppState.h"

namespace kb
{
	class ConfigPanel : public UIPanel
	{
	public:
		ConfigPanel(AppState& appstate);
		void Render() override;

	private:
		AppState& m_State;

	};
}