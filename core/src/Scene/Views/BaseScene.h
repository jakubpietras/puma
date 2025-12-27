#pragma once
#include "Scene/Scene.h"
#include "Core/AppState.h"

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

		void RenderGrid(const kbm::Mat4& viewProjection);
	};
}