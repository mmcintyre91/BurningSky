#include "PlayScene.h"
#include <glad/glad.h>

#include "BurningSky/Graphics/Renderer2D.h"


namespace BurningSky {
	PlayScene::PlayScene(OrthographicCamera& camera)
		:m_Camera(camera)
	{
		m_TestTexture = std::make_unique<Texture2D>("assets/textures/test.png");
	}

	SceneType PlayScene::OnUpdate(float dt)
	{
		//auto advance to "lose" after 5 seconds
		m_Timer += dt;
		if (m_Timer > 5.0f)
			return SceneType::Lose;

		return SceneType::Play;

	}


	void PlayScene::OnRender()
	{
		glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer2D::BeginFrame(m_Camera);

		Renderer2D::DrawSprite({ 640.0f,360.0f }, *m_TestTexture);

		// Fake player + enemy blocks for now
		Renderer2D::DrawQuad({ 640.0f, 120.0f }, { 70.0f, 70.0f }, { 0.3f, 0.8f, 0.9f, 1.0f });
		Renderer2D::DrawQuad({ 640.0f, 560.0f }, { 90.0f, 90.0f }, { 0.9f, 0.3f, 0.3f, 1.0f });

		Renderer2D::EndFrame();

	}

}