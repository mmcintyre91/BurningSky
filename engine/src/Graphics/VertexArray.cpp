#include "BurningSky/Graphics/VertexArray.h"

#include <glad/glad.h>
#include <utility>

namespace BurningSky {
	
	VertexArray::VertexArray() 
	{
		//create VAO obj ID
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() 
	{
		if(m_RendererID != 0)
		{
			glDeleteVertexArrays(1, &m_RendererID);
		}
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept 
	{
		m_RendererID = std::exchange(other.m_RendererID, 0);
		m_VertexBuffer = std::move(other.m_VertexBuffer);
		m_IndexBuffer = std::move(other.m_IndexBuffer);
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept 
	{
		if (this != &other) 
		{
			if (m_RendererID != 0) 
			{
				glDeleteVertexArrays(1, &m_RendererID);
			}

			m_RendererID = std::exchange(other.m_RendererID, 0);
			m_VertexBuffer = std::move(other.m_VertexBuffer);
			m_IndexBuffer = std::move(other.m_IndexBuffer);
		}
		return *this;
	}

	void VertexArray::Bind() const 
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() 
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer) 
	{
		//store the buffer
		m_VertexBuffer = std::move(vertexBuffer);

		// Bind VAO FIRST, then bind VBO, then set attribute pointers.
		// Attribute pointer state is stored in the VAO.
		Bind();
		m_VertexBuffer->Bind();

		//hardcoded layout: location 0, vec2 float position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			2 * sizeof(float),
			(void*)0
		);

		//clean up binds
		VertexBuffer::Unbind();
		Unbind();
	}

	void VertexArray::SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) 
	{
		m_IndexBuffer = std::move(indexBuffer);

		//the GL_ELEMENT_ARRAY_BUFFER binding is part of VAO state, bind VAO first, then bind index buffer

		Bind();
		m_IndexBuffer->Bind();
		Unbind();
	}


}