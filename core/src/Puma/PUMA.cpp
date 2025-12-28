#include "PUMA.h"
#include <exception>

namespace kb
{
	PUMA::PUMA(PUMAState& initState)
	{
		m_Arms.reserve(m_ArmsCount);
		for (int i = 0; i < m_ArmsCount; i++)
		{
			m_Arms[i] = {
				initState.l[i],
				initState.p[i],
				m_RotationAxes[i],
				initState.a[i]
			};
		}
		m_Effector = { initState.p[4], initState.a[4] };
		UpdateMesh();
	}

	void PUMA::Update(PUMAState& newState)
	{
		for (int i = 0; i < m_ArmsCount; i++)
		{
			auto& arm = m_Arms[i];
			arm.Angle = newState.a[i];
			arm.Length = newState.l[i];
			arm.Origin = newState.p[i];
		}
		m_Effector = { newState.p[4], newState.a[4] };
		UpdateMesh();
	}

	void PUMA::Render()
	{
		// todo
	}

	void PUMA::UpdateMesh()
	{
		// todo
	}
}