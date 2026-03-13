#include "BurningSky/Graphics/Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace BurningSky {

	//helper - read whole file into string
	std::string Shader::ReadFile(const std::string& path) 
	{
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if(!in)
		{
			throw std::runtime_error("Shader::ReadFile failed to open " + path);
		}

		//read file content into string
		std::stringstream ss;
		ss << in.rdbuf();
		return ss.str();
	}

	//helper - compile one shader stage (vertex or fragment)
	unsigned int Shader::CompileStage(unsigned int type, const std::string& source) 
	{
		//create empty shader obj on gpu
		unsigned int shader = glCreateShader(type);

		//shader source as c-string ptr
		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);

		//compile the shader on gpu driver
		glCompileShader(shader);

		//check compile status
		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) 
		{
			int length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			std::string infoLog(length, '\0');
			glGetShaderInfoLog(shader, length, &length, infoLog.data());

			std::string stageName = (type == GL_VERTEX_SHADER) ? "VERTEX" :
									(type == GL_FRAGMENT_SHADER) ? "FRAGMENT" : "UNKNOWN";

			std::cerr << "[Shader] " << stageName << " compile error: \n" << infoLog << "\n";

			glDeleteShader(shader);
			throw std::runtime_error("Shader stage compilation failed");
		}
		return shader;
	}

	//										//
	// Constructor : load, compile, link	//
	//										//
	Shader::Shader(const std::string & vertexPath, const std::string& fragmentPath)
	{
		//read shader source from files
		const std::string vertexSrc = ReadFile(vertexPath);
		const std::string fragmentSrc = ReadFile(fragmentPath);

		//compile each stage
		const unsigned int vertexShader = CompileStage(GL_VERTEX_SHADER, vertexSrc);
		const unsigned int fragmentShader = CompileStage(GL_FRAGMENT_SHADER, fragmentSrc);

		//create a program obj
		m_RendererID = glCreateProgram();

		//attach compiled stages to program
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		//link the program
		glLinkProgram(m_RendererID);

		//validate link status
		int linked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &linked);
		if (linked == GL_FALSE) {

			int length = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length);

			std::string infoLog(length, '\0');
			glGetProgramInfoLog(m_RendererID, length, &length, infoLog.data());

			std::cerr << "[Shader] Program Link Error: \n" << infoLog << "\n";

			glDeleteProgram(m_RendererID);
			m_RendererID = 0;

			//stages created successfully BUT the program failed to link
			throw std::runtime_error("Shader program linking failed");
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	//										//
	// Destructor							//
	//										//
	Shader::~Shader() 
	{
		if (m_RendererID != 0)
			glDeleteProgram(m_RendererID);
	}

	///Move constructor/ move assignment
	Shader::Shader(Shader&& other) noexcept 
	{
		//take ownership of other program id, set other to 0 to avoid deletion
		m_RendererID = std::exchange(other.m_RendererID, 0);
		m_UniformLocationCache = std::move(other.m_UniformLocationCache);
	}

	Shader& Shader::operator = (Shader&& other) noexcept
	{
		if(this != &other) 
		{
			//clean up current program if we own one
			if (m_RendererID != 0) glDeleteProgram(m_RendererID);

			//take ownership
			m_RendererID = std::exchange(other.m_RendererID, 0);
			m_UniformLocationCache = std::move(other.m_UniformLocationCache);
		}
		return *this;
	}

	///bind / unbind ///
	void Shader::Bind() const 
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	///uniform location caching

	int Shader::GetUniformLocation(const std::string& name) 
	{
		//if we already looked it up, return cached val
		if (auto it = m_UniformLocationCache.find(name); it != m_UniformLocationCache.end())
			return it-> second;

		//otherwise ask opengl for loc
		int location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1) 
		{
			std::cerr << "[Shader] Warning: uniform '" << name << "' not found or optimized out. \n";
		}

		m_UniformLocationCache[name] = location;
		return location;
	}

	//uniform setters
	void Shader::SetInt(const std::string& name, int value)
	{
		Bind();
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetFloat(const std::string& name, float value) 
	{
		Bind();
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetFloat4(const std::string& name, float v0, float v1, float v2, float v3)
	{
		Bind();
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) 
	{
		Bind();
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

}