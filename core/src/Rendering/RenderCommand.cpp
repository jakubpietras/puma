#include "RenderCommand.h"

namespace kb
{

	void RenderCommand::SetViewport(int x, int y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void RenderCommand::SetClearColor(const kbm::Vec4 color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
	}

	void RenderCommand::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void RenderCommand::ToggleDepthTest(bool enabled)
	{
		if (enabled) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}

	void RenderCommand::ToggleBlendColor(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else glDisable(GL_BLEND);
	}

	void RenderCommand::SetDepthMask(uint32_t flag)
	{
		glDepthMask(flag);
	}

	void RenderCommand::BindTexture(std::shared_ptr<Texture> texture, size_t slot)
	{
		texture->Bind(slot);
	}

	void RenderCommand::SetPointSize(float size /*= 1.*/)
	{
		glPointSize(size);
	}

	void RenderCommand::SetLineThickness(float width /*= 1.*/)
	{
		glLineWidth(width);
	}

	void RenderCommand::Draw(const VAO& vertexArray, uint32_t vertexCount, GLenum mode /*= GL_TRIANGLES*/, uint32_t instanceCount /*= 1*/)
	{
		vertexArray->Bind();
		glDrawArraysInstanced(mode, 0, vertexCount, instanceCount);
		vertexArray->Unbind();
	}

	void RenderCommand::DrawIndexed(const VAO& vertexArray, GLenum mode /*= GL_TRIANGLES*/, uint32_t instanceCount /*= 1*/)
	{
		vertexArray->Bind();
		if (auto& ib = vertexArray->GetIndexBuffer())
		{
			glDrawElementsInstanced(mode, ib->GetCount(), GL_UNSIGNED_INT, nullptr, instanceCount);
		}
		vertexArray->Unbind();
	}
}