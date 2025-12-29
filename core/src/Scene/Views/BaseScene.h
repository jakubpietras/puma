#pragma once
#include "Scene/Scene.h"
#include "Core/AppState.h"
#include "Puma/PUMA.h"
#include "Puma/PUMAStructs.h"

namespace kb
{
	class BaseScene : public Scene
	{
	public:
		BaseScene(const AppState& appstate);

		void OnUpdate(float dt) override;
		void OnRender(const kbm::Mat4& viewProjection) override;
		void OnStateChange(AppState& state);

		void RenderParamPUMA(const kbm::Mat4& viewProjection);
		void RenderEffectorPUMA(const kbm::Mat4& viewProjection);
	private:
		const AppState& m_State;
		PUMAState m_ParamPUMAState, m_ParamPUMAPrevState;
		PUMAState m_EffectorPUMAState, m_EffectorPUMAPrevState;
		PUMA m_ParamPUMA, m_EffectorPUMA;

		void RenderGrid(const kbm::Mat4& viewProjection);
	};
}