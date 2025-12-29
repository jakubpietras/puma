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
		m_ParamPUMAState(PUMAState{ {30.0f, 0.0f, 0.0f, 30.0f, 10.0f}, {kbm::Vec3{0,0,0},kbm::Vec3{0,2,0},kbm::Vec3{3,2,0},kbm::Vec3{3,1,0},kbm::Vec3{3.5,1,0}}, { 2.0f, 3.0f, 1.0f, 0.5f } }),
		m_ParamPUMAPrevState(m_ParamPUMAState),
		m_EffectorPUMAState(PUMAState{ {30.0f, 0.0f, 0.0f, 30.0f, -20.0f}, {kbm::Vec3{0,0,0},kbm::Vec3{0,2,0},kbm::Vec3{3,2,0},kbm::Vec3{3,1,0},kbm::Vec3{3.5,1,0}}, { 2.0f, 3.0f, 1.0f, 0.5f } }),
		m_EffectorPUMAPrevState(m_EffectorPUMAState),
		m_ParamPUMA(m_ParamPUMAState),
		m_EffectorPUMA(m_EffectorPUMAState)
	{ 
	}

	void BaseScene::OnUpdate(float dt)
	{
		// todo run simulation
	}

	void BaseScene::OnRender(const m::Mat4& viewProjection)
	{
		RenderGrid(viewProjection);
	}

	void BaseScene::OnStateChange(AppState& state)
	{
		// any changes in the UI reset the whole animation (simulation data is separate from
		// whatever is happening here)

		if (state.DirtyPUMA.Check())
		{
			
		}
		if (state.DirtyPUMA.StartPos)
		{
			
			state.DirtyPUMA.StartPos = false;
		}
		if (state.DirtyPUMA.EndPos)
		{
			// todo
			state.DirtyPUMA.EndPos = false;
		}
		if (state.DirtyPUMA.EulerStart)
		{
			// todo
			state.DirtyPUMA.EulerStart = false;
		}
		if (state.DirtyPUMA.EulerEnd)
		{
			// todo
			state.DirtyPUMA.EulerEnd = false;
		}
		if (state.DirtyPUMA.QuatStart)
		{
			// todo
			state.DirtyPUMA.QuatStart = false;
		}
		if (state.DirtyPUMA.QuatEnd)
		{
			// todo
			state.DirtyPUMA.QuatEnd = false;
		}
		if (state.DirtyPUMA.Lengths)
		{
			
			state.DirtyPUMA.Lengths = false;
		}
	}

	void BaseScene::RenderParamPUMA(const kbm::Mat4& viewProjection)
	{
		RenderGrid(viewProjection);
		m_ParamPUMA.Render(viewProjection);
	}

	void BaseScene::RenderEffectorPUMA(const kbm::Mat4& viewProjection)
	{
		RenderGrid(viewProjection);
		m_EffectorPUMA.Render(viewProjection);
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