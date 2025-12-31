#include "BaseScene.h"
#include "Rendering/Shader.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Renderer.h"
#include "rotations.h"
#include "Puma/IKSolver.h"

namespace m = kbm;

namespace kb
{
	BaseScene::BaseScene(AppState& appstate)
		: m_State(appstate),
		m_PumaState(
			IKSolver::Compute(
				appstate.Params.EffStartPos, 
				QuatRotation(appstate.Params.QuatStart), 
				{appstate.Params.Length1, appstate.Params.Length3, appstate.Params.Length4})),
		m_PumaPrevState(m_PumaState),
		m_PUMA(m_PumaState),
		m_EffectorEndPosModelMtx(kbm::TranslationMatrix(appstate.Params.EffEndPos)* QuatRotation(appstate.Params.QuatEnd)* kbm::ScaleMatrix(0.3f, 0.3f, 0.3f))
	{ }

	void BaseScene::OnUpdate(float dt)
	{
		ProcessAnimation(dt);
	}

	void BaseScene::OnRender(const m::Mat4& viewProjection, const kbm::Vec3& cameraPos)
	{
		RenderGrid(viewProjection);
		m_PUMA.Render(viewProjection, {1.0f, 5.0f, 1.0f});
		RenderGizmo(m_EffectorEndPosModelMtx, viewProjection);
	}

	void BaseScene::OnStateChange(AppState& s)
	{
		auto& p = s.Params;
		auto& df = s.DirtyPuma;

		if (s.ShouldResetPUMA)
		{
			// todo: reset PUMA
		}
		if (df.EndPos || df.EulerEnd || df.QuatEnd)
		{
			// update end effector
			m_EffectorEndPosModelMtx = kbm::TranslationMatrix(p.EffEndPos) * kbm::QuatRotation(p.QuatEnd) * kbm::ScaleMatrix(0.3f, 0.3f, 0.3f);
		}
		if (df.Check())
		{
			auto newState = IKSolver::Compute(p.EffStartPos, kbm::QuatRotation(p.QuatStart), { p.Length1, p.Length3, p.Length4 });
			m_PUMA.Update(newState);
			df.Clear();
		}
	}

	void BaseScene::ProcessAnimation(float dt)
	{
		if (!m_State.AnimationStarted)
		{
			return;
		}
		if (!m_State.AnimationPaused)
			m_State.AnimationElapsedTime += dt;
		if (m_State.AnimationElapsedTime >= m_State.AnimationTotalTime)
			m_State.AnimationPaused = true;
	}

	void BaseScene::RenderGrid(const m::Mat4& viewProjection)
	{
		auto shader = ShaderLib::Get("Grid");
		RenderCommand::ToggleDepthTest(false);
		shader->SetMat4("u_VP", viewProjection);
		Renderer::SubmitProcedural(shader, 6, GL_TRIANGLES);
		RenderCommand::ToggleDepthTest(true);
	}

	void BaseScene::RenderGizmo(const kbm::Mat4& model, const kbm::Mat4& viewProjection)
	{
		auto shader = ShaderLib::Get("Gizmo");
		shader->SetMat4("u_VP", viewProjection);
		shader->SetMat4("u_Model", model);
		RenderCommand::SetLineThickness(10.0f);
		Renderer::SubmitProcedural(shader, 6, GL_LINES);
		RenderCommand::SetLineThickness(1.0f);
	}

}