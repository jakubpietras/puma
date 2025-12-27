#include "ConfigPanel.h"
#include <imgui.h>
#include "UI/Widgets/UIWidget.h"
#include "UI/ScopedDisable.h"
#include "fmt/format.h"

namespace kb
{
	
	ConfigPanel::ConfigPanel(AppState& appstate)
		: m_State(appstate)
	{

	}

	void ConfigPanel::Render()
	{
		ImGui::Begin("Config");
		
		ImGui::Text("Config");
			
		ImGui::End();
	}

}