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
		BaseScene(AppState& appstate);

		void OnUpdate(float dt) override;
		void OnRender(const kbm::Mat4& viewProjection, const kbm::Vec3& cameraPos = {}) override;
		void OnStateChange(AppState& s);
	private:
		AppState& m_State;
		PUMAState m_PumaState, m_PumaPrevState;
		PUMA m_PUMA;
		kbm::Mat4 m_EffectorEndPosModelMtx;

		void ProcessAnimation(float dt);
		void RenderGrid(const kbm::Mat4& viewProjection);
		void RenderGizmo(const kbm::Mat4& model, const kbm::Mat4& viewProjection);
	};
}