#pragma once
#include <string>


// Texture2D wraps an OpenGL 2D texture object.
// It is responsible for:
//  - loading image pixels from disk (via stb_image in the .cpp)
//  - creating an OpenGL texture (glGenTextures)
//  - setting sampling/wrapping parameters
//  - uploading pixel data (glTexImage2D)
//  - deleting the texture (glDeleteTextures)


namespace BurningSky {
	
	class Texture2D {
	public:
		//load a texture
		explicit Texture2D(const std::string& path);

		//create empty texture
		Texture2D(unsigned int width, unsigned int height);

		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D(Texture2D&& other) noexcept;
		Texture2D& operator=(Texture2D&& other) noexcept;

		//bind this texture to a texture slot (0 = GL_TEXTURE0)
		void Bind(unsigned int slot = 0) const;

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }
		unsigned int GetRendererID() const { return m_RendererID; }

		const std::string& GetPath() const { return m_Path; }

	private:
		unsigned int m_RendererID = 0;
		unsigned int m_Width = 0, m_Height = 0;

		//OpenGl formats 
		unsigned int m_InternalFormat = 0;
		unsigned int m_DataFormat = 0;

		std::string m_Path;
	};
}