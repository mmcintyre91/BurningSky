#include "PlayScene.h"
#include <glad/glad.h>

#include "BurningSky/Graphics/Renderer2D.h"


namespace BurningSky {
	PlayScene::PlayScene(OrthographicCamera& camera, TextureLibrary& textures)
		:m_Camera(camera), m_Textures(textures)
	{
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

		auto tex = m_Textures.Get("test");
		Renderer2D::DrawSprite({ 640.0f,360.0f }, *tex);

		// Fake player + enemy blocks for now
		Renderer2D::DrawQuad({ 640.0f, 120.0f }, { 70.0f, 70.0f }, { 0.3f, 0.8f, 0.9f, 1.0f });
		Renderer2D::DrawQuad({ 640.0f, 560.0f }, { 90.0f, 90.0f }, { 0.9f, 0.3f, 0.3f, 1.0f });

		Renderer2D::EndFrame();

	}

}