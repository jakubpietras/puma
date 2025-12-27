#pragma once
#include <glad/glad.h>
#include <cstdint>

namespace kb
{
	class Framebuffer
	{
	public:
		Framebuffer(uint32_t width, uint32_t height);
		~Framebuffer();

		void Resize(uint32_t width, uint32_t height);

		void Bind();
		void Unbind();

		uint32_t GetTextureID() const { return m_ColorAttachment; }
		void* GetImGuiTextureID() const { return (void*)(intptr_t)m_ColorAttachment; }

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

	private:
		void Invalidate();

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		uint32_t m_Width, m_Height;
	};
}