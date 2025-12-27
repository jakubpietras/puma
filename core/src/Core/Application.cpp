#include "Log.h"
#include "Application.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderCommand.h"
#include "rotations.h"

namespace kb
{
	Application::Application()
		: m_Window(1920, 1080),
		m_Framebuffer(std::make_shared<Framebuffer>(400, 400)),
		m_CamController(45.0f, 1, 0.1f, 100.f, 5.f),
		m_State(),
		m_Scene(std::make_shared<BaseScene>(m_State)),
		m_ViewportPanels{}
	{ 
		m_UIController.Initialize(m_Window.GetHandle(), m_Window.GetContext());
		auto panel = std::make_shared<ViewportPanel>(m_Framebuffer, "PUMA");
		m_ViewportPanels.push_back(panel);
		m_UIController.AddPanel(panel);
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
						m_CamController.ProcessEvent(&e);
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
					m_CamController.SetAspectRatio(aspectRatio);
					vp->ClearResizeState();
				}
			}
			ProcessStateChanges();
			m_Scene->OnUpdate(deltaTime);

			// RENDER
			m_UIController.BeginFrame();
			RenderScene();
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

	void Application::RenderScene()
	{
		m_Framebuffer->Bind();

		RenderCommand::SetClearColor(kbm::Vec4(0.18f, 0.18f, 0.24f, 1.0f));
		RenderCommand::Clear();
		m_Scene->OnRender(m_CamController.GetCamera()->GetVP());

		m_Framebuffer->Unbind();
	}

	void Application::ProcessStateChanges()
	{
		
	}
}