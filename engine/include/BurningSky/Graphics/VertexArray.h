#pragma once

#include <memory>
#include "BurningSky/Graphics/VertexBuffer.h"
#include "BurningSky/Graphics/IndexBuffer.h"

namespace BurningSky {

	// VertexArray wraps an OpenGL VAO.
	// It owns:
	//  - a VAO ID
	//  - one vertex buffer (for now)
	//  - one index buffer
	//
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator =(const VertexArray&) = delete;

		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator = (VertexArray&& other) noexcept;

		void Bind() const;
		static void Unbind();

		//attach buffers to this VAO
		void SetVertexBuffer(std::unique_ptr<VertexBuffer> vertexBuffer);
		void SetIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);

		const VertexBuffer& GetVertexBuffer() const { return *m_VertexBuffer; }
		const IndexBuffer& GetIndexBuffer() const { return *m_IndexBuffer; }

	private:
		unsigned int m_RendererID = 0;

		//store buffers as unique pts so this VAO owns them
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};



}