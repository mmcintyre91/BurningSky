#include "BurningSky/Graphics/IndexBuffer.h"

#include <glad/glad.h>
#include <utility>

namespace BurningSky {
	
	//constructor - upload indices
	IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
		: m_Count(count) 
	{
		//create gpu buffer obj id
		glGenBuffers(1, &m_RendererID);

		//index buffers bound to gl_ELEMENT_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

		//upload the index data to gpu
		//store count * sizeof(unsigned int) bytes

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			count * sizeof(unsigned int),
			indices,
			GL_STATIC_DRAW
		);
	}

	//destructor
	IndexBuffer::~IndexBuffer() 
	{
		if (m_RendererID != 0) 
		{
			glDeleteBuffers(1, &m_RendererID);
		}
	
	}

	//move constructor / assignment
	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
		: m_RendererID(std::exchange(other.m_RendererID, 0)),
		  m_Count(std::exchange(other.m_Count, 0)) 
	{
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other) 
		{
			if (m_RendererID != 0) 
			{
				glDeleteBuffers(1, &m_RendererID);
			}
			
			m_RendererID = std::exchange(other.m_RendererID, 0);
			m_Count = std::exchange(other.m_Count, 0);
		}
		return *this;
	}

	//bind/unbind
	void IndexBuffer::Bind() const 
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


}