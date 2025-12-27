#pragma once

#include <SDL3/SDL.h>
#include "Rendering/PerspectiveCamera.h"

namespace kb
{
	class CameraController
	{
	public:
		CameraController(float fov, float aspectRatio, float nearPlane,
			float farPlane, float initArcballRadius);
		void OnUpdate();
		void ProcessEvent(const SDL_Event* event);

		inline std::shared_ptr<PerspectiveCamera> GetCamera() const { return m_Camera; }
		inline const kbm::Vec4& GetPosition() { return m_Position; }
		inline const float GetFOV() { return m_FOV; }
		inline const kbm::Vec3& GetOffset() { return m_Offset; }

		void Pan(float dx, float dy);
		void Rotate(float dPitchDeg, float dYawDeg, float dRollDeg);
		void UpdateArcballRadius(float dRadius);
		void SetAspectRatio(float aspectRatio);

		void UpdatePosition();
		void UpdateRotation(float dPitchDeg, float dYawDeg, float dRollDeg);

	private:
		/*bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);*/

		kbm::Vec3 m_Offset;
		kbm::Vec4 m_Position, m_Target;
		float m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane;
		float m_ArcballRadius;
		kbm::Quat m_RotationQuat; kbm::Vec3 m_RotationRPY;
		float m_MoveSpeed;


		std::shared_ptr<PerspectiveCamera> m_Camera;
	};
}

