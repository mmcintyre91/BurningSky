#pragma once

namespace BurningSky {
	class IndexBuffer {
	public:
		//create and upload indices immediately
		IndexBuffer(const unsigned int* indices, unsigned int count);

		~IndexBuffer();

		//non copyable 
		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		//movable
		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		//Bind/unbind
		void Bind() const;
		static void Unbind();

		//num of indices stored 
		unsigned int GetCount() const { return m_Count; }

		unsigned int GetRendererID() const { return m_RendererID; }

	private:
		unsigned int m_RendererID = 0; //opengl buffer id
		unsigned int m_Count = 0; //index count

	};

}