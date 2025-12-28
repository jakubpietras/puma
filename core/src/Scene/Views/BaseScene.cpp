#include "BaseScene.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Renderer.h"
#include "rotations.h"

namespace m = kbm;

namespace kb
{
	BaseScene::BaseScene(const AppState& appstate)
		: m_State(appstate),
		m_PumaState(PUMAState{ {30.0f, 0.0f, 0.0f, 30.0f, 10.0f}, {kbm::Vec3{0,0,0},kbm::Vec3{0,2,0},kbm::Vec3{3,2,0},kbm::Vec3{3,1,0},kbm::Vec3{3.5,1,0}}, { 2.0f, 3.0f, 1.0f, 0.5f } }),
		m_PumaPrevState(m_PumaState),
		m_PUMA(m_PumaState)
	{ }

	void BaseScene::OnUpdate(float dt)
	{
		
	}

	void BaseScene::OnRender(const m::Mat4& viewProjection)
	{
		RenderGrid(viewProjection);
		m_PUMA.Render(viewProjection);
	}

	void BaseScene::RenderGrid(const m::Mat4& viewProjection)
	{
		auto shader = ShaderLib::Get("Grid");
		RenderCommand::ToggleDepthTest(false);
		shader->SetMat4("u_VP", viewProjection);
		Renderer::SubmitProcedural(shader, 6, GL_TRIANGLES);
		RenderCommand::ToggleDepthTest(true);
	}
}