#pragma once
#include "PUMA.h"
#include "PUMAStructs.h"

namespace kb
{
	class PUMAEffectorSimulator
	{
	public:
		PUMAEffectorSimulator(PUMAParams& initParams, float totalTime);
		void Reset(PUMAParams& initParams, float totalTime);
		void Update(PUMA& puma, float dt);

	private:
		float m_Elapsed = 0.f, m_TotalTime = 0.f;
		PUMAParams m_Params;
		PUMAState m_Current, m_Prev;

		PUMAState SolveIK(kbm::Vec3 effPos, kbm::Mat4 effRot);
		float Angle(kbm::Vec3 v, kbm::Vec3 w);
	};
}