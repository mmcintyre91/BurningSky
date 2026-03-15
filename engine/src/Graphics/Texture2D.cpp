#include "BurningSky/Graphics/Texture2D.h"

#include <stdexcept>
#include <utility>

#include <glad/glad.h>

//stb_image is header only image loader. DO not include anywhere else

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace BurningSky {
	
	Texture2D::Texture2D(const std::string& path) 
		: m_Path(path)
	{
		//stb_image loads with 0,0 at top left. OpenGL assumes 0,0 is bottom left. Flip it
		stbi_set_flip_vertically_on_load(1);

		int width = 0, height = 0, channels = 0;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!data)
			throw std::runtime_error("Texture2D: failed to load image " + path);

		m_Width = (unsigned int)width;
		m_Height = (unsigned int)height;

		//channels 
		//3 -> RGB
		//4 -> RGBA

		if (channels == 4) 
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}

		else if (channels == 3) 
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		
		else 
		{
			stbi_image_free(data);
			throw std::runtime_error("Texture2D: Unsupported Channel count (" + std::to_string(channels));
		}

		//create openGL texture object
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		//texture sampling params, min_filter = drawn smaller than orig size, mag_filter opposite
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//wrapping params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//upload pixels to gpu
		glTexImage2D(
			GL_TEXTURE_2D,
			0,                      //mip level 0
			(GLint)m_InternalFormat,//how gpu stores
			(GLsizei)m_Width,
			(GLsizei)m_Height,
			0,
			m_DataFormat,
			GL_UNSIGNED_BYTE,
			data
		);


		//optional - generate mipmaps (improve vis quality when scaling down)
		glad_glGenerateMipmap(GL_TEXTURE_2D);

		//free cpu image mem now that its on the GPU
		stbi_image_free(data);

		//unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height)
	{
		//default to rgba8
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//allocate storage with no init data (nullptr)
		glTexImage2D(
			GL_TEXTURE_2D,
			0,                      //mip level 0
			(GLint)m_InternalFormat,//how gpu stores
			(GLsizei)m_Width,
			(GLsizei)m_Height,
			0,
			m_DataFormat,
			GL_UNSIGNED_BYTE,
			nullptr
		);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D() 
	{
		if (m_RendererID != 0)
			glDeleteTextures(1, &m_RendererID);
	}

	Texture2D::Texture2D(Texture2D&& other) noexcept 
	{
		m_RendererID = std::exchange(other.m_RendererID, 0);
		m_Width = std::exchange(other.m_Width, 0);
		m_Height = std::exchange(other.m_Height, 0);
		m_InternalFormat = std::exchange(other.m_InternalFormat, 0);
		m_DataFormat = std::exchange(other.m_DataFormat, 0);
		m_Path = std::move(other.m_Path);
	}


	Texture2D& Texture2D::operator=(Texture2D&& other) noexcept 
	{
		if (this != &other) 
		{
			if (m_RendererID != 0)
				glDeleteTextures(1, &m_RendererID);


			m_RendererID = std::exchange(other.m_RendererID, 0);
			m_Width = std::exchange(other.m_Width, 0);
			m_Height = std::exchange(other.m_Height, 0);
			m_InternalFormat = std::exchange(other.m_InternalFormat, 0);
			m_DataFormat = std::exchange(other.m_DataFormat, 0);
			m_Path = std::move(other.m_Path);
		}
		return *this;
	}

	void Texture2D::Bind(unsigned int slot) const
	{
		//texture slots are gl_texture0 + slot
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}