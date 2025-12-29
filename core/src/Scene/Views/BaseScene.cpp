#include "BaseScene.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Renderer.h"
#include "rotations.h"
#include "Puma/IKSolver.h"

namespace m = kbm;

namespace kb
{
	BaseScene::BaseScene(const AppState& appstate)
		: m_State(appstate),
		m_PumaState(
			IKSolver::Compute(
				appstate.Params.EffStartPos, 
				EulerZXZRotation(appstate.Params.EulerStart), 
				{appstate.Params.Length1, appstate.Params.Length3, appstate.Params.Length4})),
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

	void BaseScene::OnStateChange(PUMAParams& p, PUMADirtyFlag& df)
	{
		if (df.Check())
		{
			auto newState = IKSolver::Compute(p.EffStartPos, EulerZXZRotation(p.EulerStart), { p.Length1, p.Length3, p.Length4 });
			m_PUMA.Update(newState);
			df.Clear();
		}
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