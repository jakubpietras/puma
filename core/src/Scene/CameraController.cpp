#include "CameraController.h"

namespace m = kbm;

namespace kb
{
	CameraController::CameraController(float fov, float aspectRatio, float nearPlane,
		float farPlane, float initArcballRadius)
		: m_FOV(fov), m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane),
		m_ArcballRadius(initArcballRadius), m_Camera(std::make_shared<PerspectiveCamera>()),
		m_MoveSpeed(0.01f), m_Offset(m::Vec3(0.f, 0.f, 0.f))
	{
		Rotate(-30, -25, 0);
		m_Camera->UpdateProjection(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
		UpdatePosition();
		m_Camera->UpdateView(m_Position, m_Offset);
	}

	void CameraController::OnUpdate()
	{
	}

	void CameraController::ProcessEvent(const SDL_Event* event)
	{
		const float ROTATION_SPEED = 0.3f;
		const float PAN_SPEED = 0.02f;
		const float ZOOM_SPEED = 0.5f;

		switch (event->type)
		{
		case SDL_EVENT_MOUSE_WHEEL:
		{
			float scrollAmount = event->wheel.y;
			UpdateArcballRadius(-scrollAmount * ZOOM_SPEED);
			break;
		}

		case SDL_EVENT_MOUSE_MOTION:
		{
			if (event->motion.state & SDL_BUTTON_MMASK)
			{
				bool isShiftDown = SDL_GetModState() & SDL_KMOD_SHIFT;

				float deltaX = event->motion.xrel;
				float deltaY = event->motion.yrel;

				if (isShiftDown)
					Pan(-deltaX * PAN_SPEED, deltaY * PAN_SPEED);
				else
					Rotate(deltaY * ROTATION_SPEED, -deltaX * ROTATION_SPEED, 0.0f);
			}
			break;
		}

		case SDL_EVENT_KEY_DOWN:
		{
			if (event->key.key == SDLK_R)
			{
				m_Offset = m::Vec3(0.f, 0.f, 0.f);
				Rotate(0, 0, 0);
				UpdatePosition();
				m_Camera->UpdateView(m_Position, m_Offset);
			}
			break;
		}
		}
	}

	void CameraController::Pan(float dx, float dy)
	{
		auto dh = m_Camera->GetRight() * dx * 0.05;	// horizontal change
		auto dv = m_Camera->GetUp() * dy * 0.05;		// vertical change
		m_Offset += dh + dv;
		m_Camera->UpdateView(m_Position, m_Offset);
	}

	void CameraController::Rotate(float dPitchDeg, float dYawDeg, float dRollDeg)
	{
		UpdateRotation(dPitchDeg, dYawDeg, dRollDeg);
		// Rotation causes the local frame to change its basis vectors:
		m_Camera->UpdateOrientation(m_RotationQuat);
		// Based on the new orientation we calculate the position:
		UpdatePosition();
		// Based on the new position and local frame we calculate view matrix:
		m_Camera->UpdateView(m_Position, m_Offset);
	}

	void CameraController::UpdateArcballRadius(float dRadius)
	{
		m_ArcballRadius += dRadius;
		if (m_ArcballRadius < 0.5f)
			m_ArcballRadius = 0.5f;
		UpdatePosition();
		// Based on the new position we calculate view matrix:
		m_Camera->UpdateView(m_Position, m_Offset);
	}

	void CameraController::SetAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		m_Camera->UpdateProjection(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
	}

	void CameraController::UpdatePosition()
	{
		m_Position = m_Target - m_Camera->GetForward() * m_ArcballRadius;
	}

	void CameraController::UpdateRotation(float dPitchDeg, float dYawDeg, float dRollDeg)
	{
		m_RotationRPY.x += dPitchDeg;
		m_RotationRPY.y += dYawDeg;
		m_RotationRPY.z += dRollDeg;
		m_RotationQuat = RPYToQuat(m_RotationRPY);
	}
}