#pragma once

namespace BurningSky {

// VertexBuffer wraps an OpenGL VBO (Vertex Buffer Object).
// A VBO stores raw vertex data on the GPU (positions, UVs, colors, etc).
//
// In OpenGL terms, this class manages:
//  - glGenBuffers
//  - glBindBuffer(GL_ARRAY_BUFFER, ...)
//  - glBufferData / glBufferSubData
//  - glDeleteBuffers

class VertexBuffer 
{
	
public:
	explicit VertexBuffer(unsigned int size);

	//create and init buffer
	VertexBuffer(const void* data, unsigned int size);

	~VertexBuffer();


	//non copyable
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator = (const VertexBuffer&) = delete;

	//movable
	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator = (VertexBuffer&& other) noexcept;

	//bind / unbind VBO as GL_ARRAY_BUFFER
	void Bind() const;
	static void Unbind();

	//update buffer
	//offset is in bytes from start of buffer
	void SetData(const void* data, unsigned int size, unsigned int offset = 0);

	unsigned int GetRedererID() const { return m_RendererID; }

private:
	unsigned int m_RendererID = 0;
};


}