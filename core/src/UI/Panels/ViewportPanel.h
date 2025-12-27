#pragma once
#include "UI/UIPanel.h"
#include "Rendering/Framebuffer.h"
#include <memory>
#include <string>
#include <imgui.h>
#include "Scene/CameraController.h"

namespace kb
{
	class ViewportPanel : public UIPanel
	{
	public:
		ViewportPanel(std::shared_ptr<kb::Framebuffer> framebuffer, std::shared_ptr< kb::CameraController> cameraController, const std::string& name);
		ViewportPanel(uint32_t width, uint32_t height, const std::string& name);

		void Render() override;
		bool IsHovered() const { return m_IsHovered; }
		bool WasResized() const { return m_Resized; }
		void ClearResizeState() { m_Resized = false; }
		ImVec2 GetSize() const { return m_ViewportSize; }

		std::shared_ptr<kb::Framebuffer>& Framebuffer() { return m_Framebuffer; }
		std::shared_ptr<kb::CameraController>& CamController() { return m_Camera; }


	private:
		std::shared_ptr<kb::Framebuffer> m_Framebuffer;
		std::shared_ptr<kb::CameraController> m_Camera;
		std::string m_Name;
		ImVec2 m_ViewportSize;
		bool m_IsHovered = false, m_Resized = false;
	};
}