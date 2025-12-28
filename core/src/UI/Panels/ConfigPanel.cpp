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
		RenderAnimationControl();
	}

	void ConfigPanel::RenderPositionControl()
	{
		ImGui::Begin("Effector's Position");
		ImGui::TextWrapped("Set effector's translation.");
		ImGui::SeparatorText("Start");
		if (kb::UIWidget::DragVec3("s", m_State.Params.EffStartPos, { "X", "Y", "Z" }, -20.f, 20.f))
			m_State.DirtyPuma.StartPos = true;
		ImGui::SeparatorText("End");
		if (kb::UIWidget::DragVec3("e", m_State.Params.EffEndPos, { "X", "Y", "Z" }, -20.f, 20.f))
			m_State.DirtyPuma.EndPos = true;
		ImGui::End();
	}

	void ConfigPanel::RenderQuaternionControl()
	{
		ImGui::Begin("Effector's Rotation (Quaternion)");
		ImGui::TextWrapped("Set effector's local rotation in quaternions.");
		ImGui::SeparatorText("Start");
		if (kb::UIWidget::DragQuat("qs", m_State.Params.QuatStart))
			m_State.DirtyPuma.QuatStart = true;
		ImGui::SeparatorText("End");
		if (kb::UIWidget::DragQuat("qe", m_State.Params.QuatEnd))
			m_State.DirtyPuma.QuatEnd = true;
		ImGui::End();
	}

	void ConfigPanel::RenderEulerControl()
	{
		ImGui::Begin("Effector's Rotation (Euler)");
		ImGui::TextWrapped("Set effector's rotation in Euler (ZXZ) angles.");
		ImGui::SeparatorText("Start");
		if (kb::UIWidget::DragVec3("s", m_State.Params.EulerStart, { "alpha", "beta", "gamma" }, 0.0f, 360.f))
			m_State.DirtyPuma.EulerStart = true;
		ImGui::SeparatorText("End");
		if (kb::UIWidget::DragVec3("e", m_State.Params.EulerEnd, { "alpha", "beta", "gamma" }, 0.0f, 360.0f))
			m_State.DirtyPuma.EulerEnd = true;
		ImGui::End();
	}

	void ConfigPanel::RenderLengthsControl()
	{
		ImGui::Begin("Arm Lengths");
		ImGui::TextWrapped("Set constant arm lengths.");

		ImGui::Text("L1: ");
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat("##l1length", &m_State.Params.Length1, 0.1f, 0.0f, 10.0f))
			m_State.DirtyPuma.Lengths = true;
		ImGui::PopItemWidth();

		ImGui::Text("L3: ");
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat("##l3length", &m_State.Params.Length3, 0.1f, 0.0f, 10.0f))
			m_State.DirtyPuma.Lengths = true;
		ImGui::PopItemWidth();

		ImGui::Text("L4: ");
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::DragFloat("##l4length", &m_State.Params.Length4, 0.1f, 0.0f, 10.0f))
			m_State.DirtyPuma.Lengths = true;
		ImGui::PopItemWidth();

		ImGui::End();
	}

	void ConfigPanel::RenderAnimationControl()
	{
		ImGui::Begin("Animation");

		if (ImGui::Button(fmt::format("{}", m_State.AnimationStarted ? "Stop" : "Start").c_str()))
		{
			m_State.AnimationStarted = !m_State.AnimationStarted;
		}
		ImGui::SameLine();
		if (ImGui::Button(fmt::format("{}", m_State.AnimationPaused ? "Play" : "Pause").c_str()))
		{
			m_State.AnimationPaused = !m_State.AnimationPaused;
		}

		ImGui::End();
	}

}