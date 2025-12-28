#pragma once
#include "Scene/Scene.h"
#include "Core/AppState.h"
#include "Puma/PUMA.h"
#include "Puma/Configuration.h"

namespace kb
{
	class BaseScene : public Scene
	{
	public:
		BaseScene(const AppState& appstate);

		void OnUpdate(float dt) override;
		void OnRender(const kbm::Mat4& viewProjection) override;
	private:
		const AppState& m_State;
		PUMAState m_PumaState, m_PumaPrevState;
		PUMA m_PUMA;

		void RenderGrid(const kbm::Mat4& viewProjection);
	};
}