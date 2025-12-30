#pragma once
#include "kbmath.h"
#include <vector>
#include <memory>
#include "Rendering/VertexArray.h"
#include "Rendering/VertexContainers.h"

namespace kb
{
	class MeshGenerator
	{
	public:
		static std::shared_ptr<VertexArray> Cylinder(float radius, float height, size_t samples);
		static std::shared_ptr<VertexArray> ShadedCylinder(float radius, float height, size_t samples);
	private:
		static std::vector<kbm::Vec3> CylinderVerts(float radius, float height, size_t samples);
		static std::vector<VertPosNorm> ShadedCylinderVerts(float radius, float height, size_t samples);
		static std::vector<uint32_t> CylinderIdx(uint32_t samples);
		

	};
}