#include "Renderer.h"
#include "RenderCommand.h"
#include "Core/Log.h"

namespace kb
{
	std::shared_ptr<VertexArray> Renderer::s_DummyVAO = nullptr;

	void Renderer::Init()
	{
		RenderCommand::ToggleDepthTest(true);
		RenderCommand::ToggleBlendColor(true);
	}

	void Renderer::Shutdown() { }

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader,
		const std::shared_ptr<VertexArray>& vertexArray,
		const kbm::Mat4& model /*= am::Identity()*/,
		uint32_t instanceCount /*= 1*/)
	{
		shader->Use();
		shader->SetMat4("u_Model", model);
		if (vertexArray->GetIndexBuffer())
			RenderCommand::DrawIndexed(vertexArray, instanceCount);
		else
		{
			const auto& vertexBuffers = vertexArray->GetVertexBuffers();
			if (!vertexBuffers.empty())
			{
				uint32_t vertexCount = vertexBuffers[0]->GetVertexCount();
				RenderCommand::Draw(vertexArray, vertexCount, instanceCount);
			}
			else
				P_WARN("Renderer::Submit - VAO has no buffers!");
		}
	}

	void Renderer::SubmitProcedural(
		const std::shared_ptr<Shader>& shader,
		uint32_t vertexCount, 
		GLenum mode /*= GL_TRIANGLES*/,
		uint32_t instanceCount /*= 1*/)
	{
		if (!s_DummyVAO)
			s_DummyVAO = std::make_shared<VertexArray>();

		shader->Use();
		RenderCommand::Draw(s_DummyVAO, vertexCount, mode, instanceCount);
	}

}