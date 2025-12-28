#pragma once
#include "Configuration.h"

namespace kb
{
	// Container for PUMA state, handles rendering
	class PUMA
	{
	public:
		PUMA(PUMAState& initState);
		void Update(PUMAState& newState);
		void Render();

	private:
		const std::vector<kbm::Vec3> m_RotationAxes = 
		{
			{0.0f, 1.0f, 0.0f}, // arm 1 - Y
			{0.0f, 0.0f, 1.0f}, // arm 2 - Z
			{0.0f, 0.0f, 1.0f}, // arm 3 - Z
			{0.0f, 1.0f, 0.0f}	// arm 4 - Y
		};
		const size_t m_ArmsCount = 4;

		std::vector<Arm> m_Arms;
		Effector m_Effector;
		
		void UpdateMesh();
	};
}