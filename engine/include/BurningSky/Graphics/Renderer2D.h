#pragma once
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace BurningSky {


	class Shader;
	class VertexArray;
	class OrthographicCamera;

	class Renderer2D 
	{
	public:
		//init gpu - VAO, VBO, IBO, shaders.
		static void Init();

		//free gpu resources
		static void Shutdown();

		//begin a frame/scene. takes camera.
		static void BeginFrame(const OrthographicCamera& camera);

		//end a frame scene.
		static void EndFrame();

		//draw a colored quad in woirld units using pixels.
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

	private:
		//owned by the renderer
		static std::unique_ptr<VertexArray> s_QuadVAO;
		static std::unique_ptr<Shader> s_ColorShader;

		//stored for the current scene/frame
		static glm::mat4 s_ViewProjection;
	};
}
