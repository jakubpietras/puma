#pragma once
#include "SDLWindow.h"
#include "UI/ImGuiController.h"
#include <memory>
#include "Rendering/Framebuffer.h"
#include "UI/Panels/ViewportPanel.h"
#include "UI/Panels/ConfigPanel.h"
#include "Scene/CameraController.h"
#include "Scene/Views/BaseScene.h"
#include "Core/AppState.h"

namespace kb
{
	class Application
	{
	public:
		Application();
		~Application();
		void Run();

	private:
		SDLWindow m_Window;
		ImGuiController m_UIController;
		AppState m_State;

		std::shared_ptr<ConfigPanel> m_ConfigPanel;
		std::shared_ptr<BaseScene> m_Scene;
		bool m_IsCameraRotating = false;
		std::vector<std::shared_ptr<ViewportPanel>> m_ViewportPanels;

		void OnEvent(const SDL_Event& e);
		//void RenderScene(std::shared_ptr<ViewportPanel>& viewport);
		void RenderSceneParamPUMA(std::shared_ptr<ViewportPanel>& viewport);
		void RenderSceneEffectorPUMA(std::shared_ptr<ViewportPanel>& viewport);
	};
}