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
		RenderPositionControl();
		RenderQuaternionControl();
		RenderEulerControl();
		RenderLengthsControl();
	}

	void ConfigPanel::RenderPositionControl()
	{
		ImGui::Begin("Effector's Position");

		ImGui::End();
	}

	void ConfigPanel::RenderQuaternionControl()
	{
		ImGui::Begin("Effector's Rotation (Quaternion)");

		ImGui::End();
	}

	void ConfigPanel::RenderEulerControl()
	{
		ImGui::Begin("Effector's Rotation (Euler)");

		ImGui::End();
	}

	void ConfigPanel::RenderLengthsControl()
	{
		ImGui::Begin("Arm Lengths");

		ImGui::End();
	}

}