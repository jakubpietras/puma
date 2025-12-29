#include "Log.h"
#include "Application.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderCommand.h"
#include "rotations.h"
#include "Rendering/MeshGenerator.h"
#include "Rendering/Renderer.h"

namespace kb
{
	Application::Application()
		: m_Window(1920, 1080),
		m_State(), m_Scene(std::make_shared<BaseScene>(m_State))
	{ 
		m_UIController.Initialize(m_Window.GetHandle(), m_Window.GetContext());
		auto panel1 = std::make_shared<ViewportPanel>(400, 400, "Internal interpolation");
		m_ViewportPanels.push_back(panel1);
		m_UIController.AddPanel(panel1);
		auto panel2 = std::make_shared<ViewportPanel>(400, 400, "Effector interpolation");
		m_ViewportPanels.push_back(panel2);
		m_UIController.AddPanel(panel2);
		m_ConfigPanel = std::make_shared<ConfigPanel>(m_State);
		m_UIController.AddPanel(m_ConfigPanel);
		ShaderLib::Init();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		bool isRunning = true;
		SDL_Event e;
		u64 freq = SDL_GetPerformanceFrequency(), 
			lastCounter = SDL_GetPerformanceCounter(), 
			currentCounter = SDL_GetPerformanceCounter(),
			counterElapsed = currentCounter - lastCounter;
		float deltaTime = 0.f;

		// ===== Test
		auto cyl = MeshGenerator::Cylinder(0.5f, 1.0f, 15);
		auto shader = ShaderLib::Get("Ambient");

		// ==========

		// TODO: Main loop
		while (isRunning)
		{
			// TIME
			currentCounter = SDL_GetPerformanceCounter();
			counterElapsed = currentCounter - lastCounter;
			deltaTime = static_cast<float>((double)counterElapsed / (double)freq);
			if (deltaTime > 0.05f)
				deltaTime = 0.05f;
			lastCounter = currentCounter;

			// INPUT
			while (SDL_PollEvent(&e))
			{
				m_UIController.ProcessEvent(&e);
				if (e.type == SDL_EVENT_QUIT)
					isRunning = false;
				OnEvent(e);

				bool isViewportHovered = false;
				for (auto& vp : m_ViewportPanels)
				{
					if (vp->IsHovered())
					{
						isViewportHovered = true;
						break;
					}
				}
					
				bool isCapturing = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MMASK);

				if (isViewportHovered || isCapturing)
				{
					if (e.type == SDL_EVENT_MOUSE_WHEEL ||
						e.type == SDL_EVENT_MOUSE_MOTION ||
						e.type == SDL_EVENT_KEY_DOWN)
					{
						for (auto& vp : m_ViewportPanels)
							vp->CamController()->ProcessEvent(&e);
					}
				}
			}

			// UPDATE
			for (auto& vp : m_ViewportPanels)
			{
				if (vp->WasResized())
				{
					auto newSize = vp->GetSize();
					auto aspectRatio = newSize.x / newSize.y;
					vp->CamController()->SetAspectRatio(aspectRatio);
					vp->ClearResizeState();
				}
			}
			ProcessStateChanges();
			m_Scene->OnStateChange(m_State.Params, m_State.DirtyPuma);
			m_Scene->OnUpdate(deltaTime);

			// RENDER
			m_UIController.BeginFrame();
			for (auto& vp : m_ViewportPanels)
			{
				RenderScene(vp);
			}
			m_UIController.RenderPanels();
			m_UIController.EndFrame();
			m_Window.SwapBuffers();
		}
	}

	void Application::OnEvent(const SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_EVENT_KEY_DOWN:
		{
			if (e.key.key == SDLK_ESCAPE)
				break;
			if (e.key.key == SDLK_F1)
				break;
		}
		case SDL_EVENT_MOUSE_WHEEL:
		{
			break;
		}
		case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
		{
			m_UIController.ResizeUI(SDL_GetWindowDisplayScale(m_Window.GetHandle()));
			break;
		}
		}

	}

	void Application::RenderScene(std::shared_ptr<ViewportPanel>& viewport)
	{
		viewport->Framebuffer()->Bind();

		RenderCommand::SetClearColor(kbm::Vec4(0.18f, 0.18f, 0.24f, 1.0f));
		RenderCommand::Clear();
		m_Scene->OnRender(viewport->CamController()->GetCamera()->GetVP());

		viewport->Framebuffer()->Unbind();
	}

	void Application::ProcessStateChanges()
	{
		
	}
}