#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "kbmath.h"

namespace kb
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray,
			const kbm::Mat4& model = kbm::Identity(),
			uint32_t instanceCount = 1);
		static void SubmitProcedural(const std::shared_ptr<Shader>& shader,
			uint32_t vertexCount,
			GLenum mode = GL_TRIANGLES, 
			uint32_t instanceCount = 1);
	private:
		static std::shared_ptr<VertexArray> s_DummyVAO;
	};
}