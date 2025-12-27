#include "ViewportPanel.h"

namespace kb
{
	ViewportPanel::ViewportPanel(std::shared_ptr<kb::Framebuffer> framebuffer, std::shared_ptr< kb::CameraController> cameraController, const std::string& name)
		: m_Framebuffer(framebuffer), m_Name(name), m_ViewportSize({0., 0.}), m_Camera(cameraController)
	{ }

	ViewportPanel::ViewportPanel(uint32_t width, uint32_t height, const std::string& name)
		: m_Framebuffer(std::make_shared<kb::Framebuffer>(width, height)), m_Name(name), 
		m_ViewportSize({ 0., 0. }), m_Camera(std::make_shared<CameraController>(45.0f, 1, 0.1f, 100.f, 5.f))
	{ }

	void ViewportPanel::Render()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin(m_Name.c_str());

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();

		m_IsHovered = ImGui::IsWindowHovered();
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();

		if (viewportSize.x > 0.0f && viewportSize.y > 0.0f &&
			(viewportSize.x != m_ViewportSize.x || viewportSize.y != m_ViewportSize.y))
		{
			m_ViewportSize = viewportSize;
			m_Resized = true;
			m_Framebuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		}

		ImGui::Image(
			(ImTextureID)m_Framebuffer->GetImGuiTextureID(),
			m_ViewportSize,
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		ImGui::End();
		ImGui::PopStyleVar();
	}
}