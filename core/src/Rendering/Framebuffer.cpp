#include "Framebuffer.h"
#include "Core/Log.h"

namespace kb
{
	Framebuffer::Framebuffer(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		Invalidate();
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteRenderbuffers(1, &m_DepthAttachment);
	}

	void Framebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteRenderbuffers(1, &m_DepthAttachment);
		}

		glCreateFramebuffers(1, &m_RendererID);

		// 1. Color Attachment (Texture)
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Width, m_Height);

		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_ColorAttachment, 0);

		// 2. Depth Attachment (Renderbuffer - szybciej, jeœli nie samplujemy)
		glCreateRenderbuffers(1, &m_DepthAttachment);
		glNamedRenderbufferStorage(m_DepthAttachment, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glNamedFramebufferRenderbuffer(m_RendererID, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment);

		if (glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			P_ERROR("Framebuffer is incomplete!");
		}
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || (width == m_Width && height == m_Height))
			return;

		m_Width = width;
		m_Height = height;
		Invalidate();
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}