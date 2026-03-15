#include "LoseScene.h"

#include <glad/glad.h>

#include "BurningSky/Graphics/Renderer2D.h"

namespace BurningSky {
	LoseScene::LoseScene(OrthographicCamera& camera, TextureLibrary& textures)
		:m_Camera(camera), m_Textures(textures)
	{
	}

	SceneType LoseScene::OnUpdate(float dt)
	{
		//auto advance to "lose" after 5 seconds
		m_Timer += dt;
		if (m_Timer > 5.0f)
			return SceneType::Title;

		return SceneType::Lose;

	}


	void LoseScene::OnRender()
	{
		glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer2D::BeginFrame(m_Camera);

		Renderer2D::DrawQuad({ 640.0f, 360.0f }, { 600.0f, 240.0f }, { 0.6f, 0.1f, 0.1f, 1.0f });

		Renderer2D::EndFrame();

	}

}