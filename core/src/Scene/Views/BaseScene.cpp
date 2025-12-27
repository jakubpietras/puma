#include "BaseScene.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Renderer.h"
#include "rotations.h"

namespace m = kbm;

namespace kb
{
	BaseScene::BaseScene(const AppState& appstate)
		: m_State(appstate)
	{ }

	void BaseScene::OnUpdate(float dt)
	{
		
	}

	void BaseScene::OnRender(const m::Mat4& viewProjection)
	{
		RenderGrid(viewProjection);
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