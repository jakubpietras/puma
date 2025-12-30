#include "MeshGenerator.h"
#include <numbers>

namespace kb
{
	std::shared_ptr<kb::VertexArray> MeshGenerator::Cylinder(float radius, float height,
		size_t samples)
	{
		auto mesh = std::make_shared<VertexArray>();
		auto vbo = std::make_shared<VertexBuffer>(CylinderVerts(radius, height, samples));
		auto ebo = std::make_shared<IndexBuffer>(CylinderIdx(samples));
		BufferLayout layout({ BufferElement(ShaderDataType::Float3, "Pos", false) });
		vbo->SetLayout(layout);
		mesh->AddVertexBuffer(vbo);
		mesh->SetIndexBuffer(ebo);
		return mesh;
	}

	std::shared_ptr<kb::VertexArray> MeshGenerator::ShadedCylinder(float radius, float height, size_t samples)
	{
		auto mesh = std::make_shared<VertexArray>();
		auto vbo = std::make_shared<VertexBuffer>(ShadedCylinderVerts(radius, height, samples));
		auto ebo = std::make_shared<IndexBuffer>(CylinderIdx(samples));
		BufferLayout layout({
			BufferElement(ShaderDataType::Float3, "Pos", false), 
			BufferElement(ShaderDataType::Float3, "Normal", false)
			});
		vbo->SetLayout(layout);
		mesh->AddVertexBuffer(vbo);
		mesh->SetIndexBuffer(ebo);
		return mesh;
	}

	std::vector<kbm::Vec3> MeshGenerator::CylinderVerts(float radius, float height, size_t samples)
	{
		auto pi = std::numbers::pi;
		float sectorStep = 2 * pi / samples;
		float angle;
		std::vector<kbm::Vec3> verts;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < samples; j++)
			{
				angle = j * sectorStep;
				auto x = radius * cos(angle);
				auto y = height * i;
				auto z = radius * sin(angle);
				verts.emplace_back(x, y, z);
			}
		}
		return verts;
	}

	std::vector<VertPosNorm> MeshGenerator::ShadedCylinderVerts(float radius, float height, size_t samples)
	{
		auto pi = std::numbers::pi;
		float sectorStep = 2 * pi / samples;
		float angle;
		std::vector<VertPosNorm> verts;

		std::vector<kbm::Vec3> pos;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < samples; j++)
			{
				angle = j * sectorStep;
				auto x = radius * cos(angle);
				auto y = height * i;
				auto z = radius * sin(angle);
				kbm::Vec3 normal = { cos(angle), 0.f, sin(angle)};
				verts.push_back(VertPosNorm{ { x,y,z }, normal });
			}
		}
		return verts;
	}

	std::vector<uint32_t> MeshGenerator::CylinderIdx(uint32_t samples)
	{
		std::vector<uint32_t> idx;
		// side walls
		for (uint32_t i = 0; i < samples; i++)
		{
			uint32_t next = (i + 1) % samples;
			idx.insert(idx.end(), { i, samples + next, next });
			idx.insert(idx.end(), { i, samples + i, samples + next });
		}
		// bottom base (ccw)
		for (uint32_t j = 1; j < samples - 1; j++)
			idx.insert(idx.end(), { 0, j, j + 1 });
		// top base (cw)
		for (uint32_t j = 1; j < samples - 1; j++)
			idx.insert(idx.end(), { samples, samples + j + 1, samples + j });
		return idx;
	}

}