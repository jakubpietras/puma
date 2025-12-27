#include "PerspectiveCamera.h"
#include "transformations.h"

namespace m = kbm;

namespace kb
{
	PerspectiveCamera::PerspectiveCamera()
		: m_Forward({ 0.0f, 0.0f, 1.0f, 0.0f }), m_Up({ 0.0f, 1.0f, 0.0f, 0.0f }), m_Right({ 1.0f, 0.0f, 0.0f, 0.0f }),
		m_Projection(m::Identity()), m_InvProjection(m::Identity()),
		m_View(m::Identity()), m_InvView(m::Identity())
	{
		m_ViewProjection = m_Projection * m_View;
	}

	void PerspectiveCamera::UpdateView(m::Vec4 position, m::Vec3 offset)
	{
		m_View = LookAt(m_Right, m_Up, m_Forward, position) * m::TranslationMatrix(offset);
		m_ViewProjection = m_Projection * m_View;
		m_InvView = m::TranslationMatrix(-offset) * InvLookAt(m_Right, m_Up, m_Forward, position);
	}
	void PerspectiveCamera::UpdateProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		m_Projection = m::Perspective(fov, aspectRatio, nearPlane, farPlane);
		m_ViewProjection = m_Projection * m_View;
		m_InvProjection = m::InvPerspective(fov, aspectRatio, nearPlane, farPlane);
	}
	void PerspectiveCamera::UpdateOrientation(m::Quat rotation)
	{
		m_Forward = m::Normalize(m::Rotate({ 0.0f, 0.0f, 1.0f, 0.0f }, rotation));
		m_Up = m::Normalize(m::Rotate({ 0.0f, 1.0f, 0.0f, 0.0f }, rotation));
		m_Right = m::Normalize(m::Rotate({ 1.0f, 0.0f, 0.0f, 0.0f }, rotation));
	}
}

