#pragma once
#include "Configuration.h"
#include "Rendering/VertexArray.h"

namespace kb
{
	// Container for PUMA state, handles rendering
	class PUMA
	{
	public:
		PUMA(PUMAState& initState);
		void Update(PUMAState& newState);
		void Render(const kbm::Mat4& viewProjection);

	private:
		const std::vector<kbm::Vec3> m_RotationAxes = 
		{
			{0.0f, 1.0f, 0.0f}, // arm 1 - Y
			{0.0f, 0.0f, 1.0f}, // arm 2 - Z
			{0.0f, 0.0f, 1.0f}, // arm 3 - Z
			{0.0f, 1.0f, 0.0f}	// arm 4 - Y
		};
		const size_t m_ArmsCount = 4;
		const std::vector<kbm::Vec3> m_ArmColors =
		{
			{1.0f, 0.0f, 0.0f},	// arm 1 - red
			{0.0f, 1.0f, 0.0f},	// arm 2 - green
			{0.0f, 0.0f, 1.0f},	// arm 3 - blue
			{1.0f, 1.0f, 0.0f}	// arm 4 - yellow
		};

		std::vector<Arm> m_Arms;
		std::vector<kbm::Mat4> m_BaseArmModelMtx, m_ArmModelMtx;
		kbm::Mat4 m_EffectorModelMtx;
		std::shared_ptr<VertexArray> m_BaseArmMesh;

		Effector m_Effector;
		
		void UpdateModelMatrices();
	};
}