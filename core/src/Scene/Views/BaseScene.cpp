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
		m_PUMAStartState(
			IKSolver::Compute(
				appstate.Params.EffStartPos, 
				QuatRotation(appstate.Params.QuatStart), 
				{appstate.Params.Length1, appstate.Params.Length3, appstate.Params.Length4})),
		m_PUMAEndState(IKSolver::Compute(
			appstate.Params.EffEndPos,
			QuatRotation(appstate.Params.QuatEnd),
			{ appstate.Params.Length1, appstate.Params.Length3, appstate.Params.Length4 })),
		m_PUMAA(m_PUMAStartState),
		m_PUMAB(m_PUMAStartState),
		m_EffectorEndPosModelMtx(kbm::TranslationMatrix(appstate.Params.EffEndPos)* QuatRotation(appstate.Params.QuatEnd)* kbm::ScaleMatrix(0.3f, 0.3f, 0.3f))
	{ }

	void BaseScene::OnUpdate(float dt)
	{
		ProcessAnimation(dt);
	}

	void BaseScene::OnRender(const m::Mat4& viewProjection, const kbm::Vec3& cameraPos)
	{
		RenderGrid(viewProjection);
	}

	void BaseScene::RenderA(const kbm::Mat4& viewProjection, const kbm::Vec3& cameraPos /*= {}*/)
	{
		RenderGrid(viewProjection);
		m_PUMAA.Render(viewProjection, cameraPos);
		RenderGizmo(m_EffectorEndPosModelMtx, viewProjection);
	}

	void BaseScene::RenderB(const kbm::Mat4& viewProjection, const kbm::Vec3& cameraPos /*= {}*/)
	{
		RenderGrid(viewProjection);
		m_PUMAB.Render(viewProjection, cameraPos);
		RenderGizmo(m_EffectorEndPosModelMtx, viewProjection);
	}

	void BaseScene::OnStateChange(AppState& s)
	{
		auto& p = s.Params;
		auto& df = s.DirtyPuma;

		if (s.ShouldResetPUMA)
		{
			m_PUMAA.Reset(m_PUMAStartState);
			m_PUMAB.Reset(m_PUMAStartState);
			s.ShouldResetPUMA = false;
		}
		if (df.EndPos || df.EulerEnd || df.QuatEnd)
		{
			// update end effector
			m_EffectorEndPosModelMtx = kbm::TranslationMatrix(p.EffEndPos) * kbm::QuatRotation(p.QuatEnd) * kbm::ScaleMatrix(0.3f, 0.3f, 0.3f);
		}
		if (df.Check())
		{
			// startState and endState are only computed once (for internal parameter interpolation)
			// so endState's previous state is startState

			auto startState = IKSolver::Compute(p.EffStartPos, kbm::QuatRotation(p.QuatStart), { p.Length1, p.Length3, p.Length4 });
			auto endState = IKSolver::Compute(p.EffEndPos, kbm::QuatRotation(p.QuatEnd), { p.Length1, p.Length3, p.Length4 }, startState);
			
			m_PUMAA.Update(startState);
			m_PUMAB.Update(startState);
			m_PUMAStartState = startState;
			m_PUMAEndState = endState;

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
		{
			m_State.AnimationElapsedTime += dt;
			auto t = m_State.AnimationElapsedTime / m_State.AnimationTotalTime;
			AnimatePUMAParamInterpolation(t);
			AnimatePUMAEffectorInterpolation(t);
		}
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

	kb::PUMAState BaseScene::InterpolateParameters(PUMAState start, PUMAState end, float t)
	{
		PUMAState s;
		s.a = {
			LerpEuler(start.a[0], end.a[0], t),
			LerpEuler(start.a[1], end.a[1], t),
			LerpEuler(start.a[2], end.a[2], t),
			LerpEuler(start.a[3], end.a[3], t),
			LerpEuler(start.a[4], end.a[4], t)
		};
		s.l = {
			start.l[0],
			kbm::Lerp(start.l[1], end.l[1], t),
			start.l[2],
			start.l[3]
		};
		s.p = {
			kbm::Lerp(start.p[0], end.p[0], t),
			kbm::Lerp(start.p[1], end.p[1], t),
			kbm::Lerp(start.p[2], end.p[2], t),
			kbm::Lerp(start.p[3], end.p[3], t),
			kbm::Lerp(start.p[4], end.p[4], t)
		};
		return s;
	}

	kb::PUMAState BaseScene::InterpolateEffector(PUMAParams params, std::optional<PUMAState> prevState, float t)
	{
		auto ep = kbm::Lerp(params.EffStartPos, params.EffEndPos, t);
		auto er = kbm::Slerp(params.QuatStart, params.QuatEnd, t);
		return IKSolver::Compute(ep, kbm::QuatRotation(er), { params.Length1, params.Length3, params.Length4 }, prevState);
	}

	void BaseScene::AnimatePUMAParamInterpolation(float t)
	{
		auto prevA = m_PUMAA.GetCurrentState();
		auto newA = InterpolateParameters(m_PUMAStartState, m_PUMAEndState, t);
		m_PUMAA.Update(newA);
	}

	void BaseScene::AnimatePUMAEffectorInterpolation(float t)
	{
		auto prevB = m_PUMAB.GetCurrentState();
		auto newB = InterpolateEffector(m_State.Params, prevB, t);
		m_PUMAB.Update(newB);
	}

	float BaseScene::LerpEuler(float start, float end, float t)
	{
		auto diff = end - start;
		return start + ClampEuler(diff) * t;
	}

	float BaseScene::ClampEuler(float angle)
	{
		angle = std::fmod(angle + 180.0f, 360.0f);
		if (angle < 0.0f) angle += 360.0f;
		return angle - 180.0f;
	}

}