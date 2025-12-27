#pragma once
#include "kbmath.h"
#include "Rendering/Texture.h"
#include "Rendering/VertexArray.h"

using VAO = std::shared_ptr<kb::VertexArray>;

namespace kb
{
	class RenderCommand
	{
	public:
		static void SetViewport(int x, int y, uint32_t width, uint32_t height);
		static void SetClearColor(const kbm::Vec4 color);
		static void Clear();
		
		static void ToggleDepthTest(bool enabled);
		static void ToggleBlendColor(bool enabled);
		static void SetDepthMask(uint32_t flag);
		static void BindTexture(std::shared_ptr<Texture> texture, size_t slot);
		
		static void SetPointSize(float size = 1.);
		static void SetLineThickness(float width = 1.);

		static void Draw(const VAO& vertexArray, uint32_t vertexCount, GLenum mode = GL_TRIANGLES,
			uint32_t instanceCount = 1);
		static void DrawIndexed(const VAO& vertexArray, GLenum mode = GL_TRIANGLES,
			uint32_t instanceCount = 1);
	};
}

