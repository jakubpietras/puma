#pragma once
#include "Scene/Scene.h"
#include "Core/AppState.h"
#include "Puma/PUMA.h"
#include "Puma/PUMAStructs.h"
#include <optional>

namespace kb
{
	class BaseScene : public Scene
	{
	public:
		BaseScene(AppState& appstate);

		void OnUpdate(float dt) override;
		void OnRender(const kbm::Mat4& viewProjection, const kbm::Vec3& cameraPos = {}) override;
		void RenderA(const kbm::Mat4& viewProjection, const kbm::Vec3& cameraPos = {});
		void RenderB(const kbm::Mat4& viewProjection, const kbm::Vec3& cameraPos = {});

		void OnStateChange(AppState& s);
	private:
		AppState& m_State;
		PUMAState m_PUMAStartState, m_PUMAEndState;
		PUMA m_PUMAA, m_PUMAB; // A - interpolated params, B - interpolated effector
		kbm::Mat4 m_EffectorEndPosModelMtx;

		void ProcessAnimation(float dt);
		void RenderGrid(const kbm::Mat4& viewProjection);
		void RenderGizmo(const kbm::Mat4& model, const kbm::Mat4& viewProjection);

		PUMAState InterpolateParameters(PUMAState start, PUMAState end, float t);
		PUMAState InterpolateEffector(PUMAParams params, std::optional<PUMAState> prevState, float t);
		void AnimatePUMAParamInterpolation(float t);
		void AnimatePUMAEffectorInterpolation(float t);

		float LerpEuler(float start, float end, float t);
		float ClampEuler(float angle);
	};
}