#pragma once
#include <string>
#include <glad/glad.h>

namespace kb
{
	class Texture
	{
	public:
		Texture(const std::string& path);
		Texture(uint32_t width, uint32_t height);
		~Texture();

		void Bind(uint32_t slot = 0) const;

		uint32_t GetID() const { return m_RendererID; }
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		// Metoda dla ImGui (zwraca ID jako void*)
		void* GetImGuiID() const { return (void*)(intptr_t)m_RendererID; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
		std::string m_FilePath;
		GLenum m_InternalFormat, m_DataFormat;
	};
}