#include "TitleScene.h"

#include <glad/glad.h>

#include "BurningSky/Graphics/Renderer2D.h"

namespace BurningSky {
	TitleScene::TitleScene(OrthographicCamera& camera)
		:m_Camera(camera)
	{
	}

	SceneType TitleScene::OnUpdate(float dt) 
	{
		//auto advance to play after 2 seconds
		m_Timer += dt;
		if (m_Timer > 2.0f)
			return SceneType::Play;

		return SceneType::Title;
	
	}


	void TitleScene::OnRender()
	{
		glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer2D::BeginFrame(m_Camera);

		//title screen
		Renderer2D::DrawQuad({ 640.0f, 420.0f }, { 500.0f, 200.0f }, { 0.15f, 0.15f, 0.35f, 1.0f });

		//fake start button
		Renderer2D::DrawQuad({ 640.0f, 260.0f }, { 240.0f, 80.0f }, { 0.2f, 0.7f, 0.3f, 1.0f });

		Renderer2D::EndFrame();

	}

}