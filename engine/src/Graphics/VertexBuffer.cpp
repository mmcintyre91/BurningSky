#include "BurningSky/Graphics/VertexBuffer.h"

#include <glad/glad.h>
#include <utility>
#include <cstring>


namespace BurningSky {

	//constructor - allocate empty buffer
	VertexBuffer::VertexBuffer(unsigned int size)
	{
		//glgen creates a new buffer obj name (id)
		glGenBuffers(1, &m_RendererID);

		//bind the buff to GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		//alocate gpu mem for the buffer (size bytes) with no data
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}

	//constructor - upload initial data
	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		//allocate and init with provided data
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	//destructor - free gpu buffer
	VertexBuffer::~VertexBuffer() 
	{
		if (m_RendererID != 0) 
		{
			glDeleteBuffers(1, &m_RendererID);
		}
	}

	//move constructor / assignment
	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept 
	{
		//take ownership of opengl buffer id, set other to 0 so it wont delete
		m_RendererID = std::exchange(other.m_RendererID, 0);
	
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept 
	{
		if (this != &other) 
		{
			//clean up current buff if we own
			if (m_RendererID != 0) 
			{
				glDeleteBuffers(1, &m_RendererID);
			}
		
			//take ownership
			m_RendererID = std::exchange(other.m_RendererID, 0);
		}
		return *this;
	}

	//bind / unbind
	void VertexBuffer::Bind() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);	
	}

	void VertexBuffer::Unbind() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//update buffer data
	void VertexBuffer::SetData(const void* data, unsigned int size, unsigned int offset) 
	{
		//bind before update
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

		//glBufferSubData updates an existing buffers content
		//assumes buffer was already allocated large enough
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

	}


}