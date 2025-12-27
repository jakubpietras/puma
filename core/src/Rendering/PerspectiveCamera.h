#pragma once
#include "kbmath.h"

namespace kb
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera();

		inline const kbm::Mat4& GetView() { return m_View; }
		inline const kbm::Mat4& GetProjection() { return m_Projection; }
		inline const kbm::Mat4& GetInvView() { return m_InvView; }
		inline const kbm::Mat4& GetInvProjection() { return m_InvProjection; }
		inline const kbm::Mat4& GetVP() { return m_ViewProjection; }
		inline const kbm::Vec4& GetForward() const { return m_Forward; }
		inline const kbm::Vec4& GetRight() const { return m_Right; }
		inline const kbm::Vec4& GetUp() const { return m_Up; }

		void UpdateView(kbm::Vec4 position, kbm::Vec3 offset);
		void UpdateProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
		void UpdateOrientation(kbm::Quat rotation);

	private:
		kbm::Vec4 m_Forward, m_Up, m_Right;
		kbm::Mat4 m_Projection, m_InvProjection, m_View, m_InvView, m_ViewProjection;
	};
}

