#pragma once
#include <string>
#include <unordered_map>
#include <glm/mat4x4.hpp>

namespace BurningSky {

	class Shader 
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		~Shader();

		//making the shader non-copyable
		Shader(const Shader&) = delete;
		Shader& operator = (const Shader&) = delete;

		//movable: allows storage of shaders in containers
		Shader(Shader&& other) noexcept;
		Shader& operator = (Shader&& other) noexcept;

		//bind
		void Bind() const;

		//unbind
		static void Unbind();

		//uniform helpers
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetFloat4(const std::string& name, float v0, float v1, float v2, float v3);
		void SetMat4(const std::string& name, const glm::mat4& matrix);

		//expose the openGl prog ID
		unsigned int GetRendererID() const { return m_RendererID; }

	private:
		//read whole file into string
		static std::string ReadFile(const std::string& path);

		//compile single stage & return shader obj
		static unsigned int CompileStage(unsigned int type, const std::string& source);

		//get uniform location
		int GetUniformLocation(const std::string& name);

		unsigned int m_RendererID = 0;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};



}