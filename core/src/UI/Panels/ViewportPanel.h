#pragma once
#include "UI/UIPanel.h"
#include "Rendering/Framebuffer.h"
#include <memory>
#include <string>
#include <imgui.h>

namespace kb
{
	class ViewportPanel : public UIPanel
	{
	public:
		ViewportPanel(std::shared_ptr<kb::Framebuffer> framebuffer, const std::string& name);
		void Render() override;
		bool IsHovered() const { return m_IsHovered; }
		bool WasResized() const { return m_Resized; }
		void ClearResizeState() { m_Resized = false; }
		ImVec2 GetSize() const { return m_ViewportSize; }
	private:
		std::shared_ptr<kb::Framebuffer> m_Framebuffer;
		std::string m_Name;
		ImVec2 m_ViewportSize;
		bool m_IsHovered = false, m_Resized = false;
	};
}