#include "VertexArray.h"
#include <glad/glad.h>

namespace kb
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}
		return 0;
	}

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexArrayAttrib(m_RendererID, m_VertexBufferIndex);
				glVertexArrayAttribBinding(m_RendererID, m_VertexBufferIndex, 0);

				// DSA version of glVertexAttribPointer
				if (element.Type >= ShaderDataType::Int && element.Type <= ShaderDataType::Int4)
				{
					glVertexArrayAttribIFormat(m_RendererID, m_VertexBufferIndex, element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type), element.Offset);
				}
				else
				{
					glVertexArrayAttribFormat(m_RendererID, m_VertexBufferIndex, element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, element.Offset);
				}

				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexArrayAttrib(m_RendererID, m_VertexBufferIndex);
					glVertexArrayAttribBinding(m_RendererID, m_VertexBufferIndex, 0);
					glVertexArrayAttribFormat(m_RendererID, m_VertexBufferIndex, count,
						ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized,
						element.Offset + sizeof(float) * count * i);
					glVertexArrayBindingDivisor(m_RendererID, m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			}
		}

		glVertexArrayVertexBuffer(m_RendererID, 0, vertexBuffer->GetID(), 0, layout.GetStride());

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glVertexArrayElementBuffer(m_RendererID, indexBuffer->GetID());
		m_IndexBuffer = indexBuffer;
	}
}