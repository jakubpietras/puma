#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "UIPanel.h" 
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

namespace kb
{
	class ImGuiController
	{
	public:
		ImGuiController();
		~ImGuiController();

		void AddPanel(std::shared_ptr<UIPanel> panel);
		void Initialize(SDL_Window* window, SDL_GLContext glContext);
		void RenderPanels();
		void RenderDemo();
		void BeginFrame();
		void EndFrame();
		void Shutdown();
		void ProcessEvent(const SDL_Event* event);
		void ResizeUI(float scale_factor);

	private:
		ImGuiStyle m_BaseStyle;
		std::vector<std::shared_ptr<UIPanel>> m_Panels;
		void SetBessTheme();
		void SetLightGreenTheme();
	};
}