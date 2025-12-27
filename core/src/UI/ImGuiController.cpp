#include "ImGuiController.h"


namespace kb
{
	ImGuiController::ImGuiController()
		: m_BaseStyle({})
	{
		m_Panels = std::vector<std::shared_ptr<UIPanel>>();
	}

	ImGuiController::~ImGuiController()
	{
		Shutdown();
	}

	void ImGuiController::AddPanel(std::shared_ptr<UIPanel> panel)
	{
		m_Panels.push_back(panel);
	}

	void ImGuiController::Initialize(SDL_Window* window, SDL_GLContext glContext)
	{
		// 1. Core Init
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		// 2. Theme
		//SetBessTheme();
		SetLightGreenTheme();
		m_BaseStyle = ImGui::GetStyle();

		// 3. Backend Init
		// SDL3
		ImGui_ImplSDL3_InitForOpenGL(window, glContext);
		ImGui_ImplOpenGL3_Init("#version 460");

		// 4. Scaling
		float scale_factor = SDL_GetWindowDisplayScale(window);
		ResizeUI(scale_factor);
	}

	void ImGuiController::ProcessEvent(const SDL_Event* event)
	{
		ImGui_ImplSDL3_ProcessEvent(event);
	}

	void ImGuiController::ResizeUI(float scale_factor)
	{
		ImGui::GetStyle() = m_BaseStyle;
		if (scale_factor <= 0.0f)
			scale_factor = 1.0f;
		ImGui::GetStyle().ScaleAllSizes(scale_factor);

		// Font size
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->Clear();
		io.Fonts->AddFontFromFileTTF("src/Resources/Fonts/jbmono.ttf", 16.0f * scale_factor);
		io.Fonts->Build();
	}

	void ImGuiController::RenderPanels()
	{
		for (const auto& panel : m_Panels)
		{
			if (panel) panel->Render();
		}
	}

	void ImGuiController::RenderDemo()
	{
		ImGui::ShowDemoWindow();
	}

	void ImGuiController::BeginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
	}

	void ImGuiController::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiController::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();

		if (ImGui::GetCurrentContext()) ImGui::DestroyContext();
	}

	void ImGuiController::SetBessTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.18f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.30f, 0.40f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.35f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.32f, 0.40f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.35f, 0.38f, 0.50f, 1.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.18f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.27f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.35f, 0.50f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.25f, 0.38f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.13f, 0.17f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.25f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.50f, 0.70f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.70f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.80f, 1.00f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.50f, 0.70f, 1.00f, 0.50f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.60f, 0.80f, 1.00f, 0.75f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.70f, 0.90f, 1.00f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.35f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.50f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.45f, 0.45f, 0.55f, 1.00f);

		style.WindowRounding = 5.0f;
		style.FrameRounding = 5.0f;
		style.GrabRounding = 5.0f;
		style.TabRounding = 5.0f;
		style.PopupRounding = 5.0f;
		style.ScrollbarRounding = 5.0f;
		style.WindowPadding = ImVec2(10, 10);
		style.FramePadding = ImVec2(6, 4);
		style.ItemSpacing = ImVec2(8, 6);
		style.PopupBorderSize = 0.1f;
	}

	void ImGuiController::SetLightGreenTheme()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		ImVec4 colorPrimary = ImVec4(0.42f, 0.56f, 0.44f, 1.00f);
		ImVec4 colorHover = ImVec4(colorPrimary.x + 0.10f, colorPrimary.y + 0.10f, colorPrimary.z + 0.10f, 1.00f);
		ImVec4 colorActive = ImVec4(colorPrimary.x - 0.05f, colorPrimary.y - 0.05f, colorPrimary.z - 0.05f, 1.00f);
		ImVec4 colorGhost = ImVec4(colorPrimary.x, colorPrimary.y, colorPrimary.z, 0.35f);

		colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.96f, 0.96f, 0.96f, 0.98f);
		colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.10f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.92f, 0.92f, 0.92f, 0.51f);
		colors[ImGuiCol_TitleBgActive] = colors[ImGuiCol_TitleBg];
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);

		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.03f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(colorPrimary.x, colorPrimary.y, colorPrimary.z, 0.40f);
		colors[ImGuiCol_ScrollbarGrabHovered] = colorPrimary;
		colors[ImGuiCol_ScrollbarGrabActive] = colorActive;

		colors[ImGuiCol_CheckMark] = colorActive;
		colors[ImGuiCol_SliderGrab] = colorPrimary;
		colors[ImGuiCol_SliderGrabActive] = colorActive;

		colors[ImGuiCol_Button] = colorGhost;
		colors[ImGuiCol_ButtonHovered] = colorHover;
		colors[ImGuiCol_ButtonActive] = colorActive;

		colors[ImGuiCol_Header] = colorGhost;
		colors[ImGuiCol_HeaderHovered] = colorHover;
		colors[ImGuiCol_HeaderActive] = colorActive;

		colors[ImGuiCol_Separator] = ImVec4(0.00f, 0.00f, 0.00f, 0.10f);
		colors[ImGuiCol_SeparatorHovered] = colorPrimary;
		colors[ImGuiCol_SeparatorActive] = colorActive;

		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_ResizeGripHovered] = colorHover;
		colors[ImGuiCol_ResizeGripActive] = colorActive;

		colors[ImGuiCol_Tab] = colorGhost;
		colors[ImGuiCol_TabHovered] = colorHover;
		colors[ImGuiCol_TabActive] = colorPrimary;
		colors[ImGuiCol_TabUnfocused] = colorGhost;
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(colorPrimary.x, colorPrimary.y, colorPrimary.z, 0.70f);

		colors[ImGuiCol_PlotLines] = colorActive;
		colors[ImGuiCol_PlotLinesHovered] = colorHover;
		colors[ImGuiCol_PlotHistogram] = colorPrimary;
		colors[ImGuiCol_PlotHistogramHovered] = colorHover;

		colors[ImGuiCol_TextSelectedBg] = ImVec4(colorPrimary.x, colorPrimary.y, colorPrimary.z, 0.35f);
		colors[ImGuiCol_DragDropTarget] = colorActive;
		colors[ImGuiCol_NavHighlight] = colorPrimary;
	}

}