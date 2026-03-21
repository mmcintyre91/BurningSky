#include "PlayScene.h"

#include <glad/glad.h>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>
#include <iostream>

#include "BurningSky/Graphics/Renderer2D.h"
#include "BurningSky/Core/Input.h"
#include "BurningSky/Core/KeyCodes.h"


namespace BurningSky {
	PlayScene::PlayScene(OrthographicCamera& camera, TextureLibrary& textures, Window& window)
		:m_Camera(camera), m_Textures(textures), m_Window(window)
	{
	}

	SceneType PlayScene::OnUpdate(float dt)
	{

		//movement input
		glm::vec2 dir(0.0f);

		if (Input::IsKeyDown(Key::A) || Input::IsKeyDown(Key::Left)) dir.x -= 1.0f;
		if (Input::IsKeyDown(Key::D) || Input::IsKeyDown(Key::Right)) dir.x += 1.0f;
		if (Input::IsKeyDown(Key::S) || Input::IsKeyDown(Key::Down)) dir.y -= 1.0f;
		if (Input::IsKeyDown(Key::W) || Input::IsKeyDown(Key::Up)) dir.y += 1.0f;

		//normalize so diag isnt faster
		if (dir.x != 0.0f || dir.y != 0.0f)
			dir = glm::normalize(dir);

		//move in pix per sec
		m_Player.pos += dir * m_Player.speed * dt;

		//clamp movement to window
		float halfW = m_Player.size.x * 0.5f;
		float halfH = m_Player.size.y * 0.5f;

		float w = (float)m_Window.GetWidth();
		float h = (float)m_Window.GetHeight();

		m_Player.pos.x = glm::clamp(m_Player.pos.x, halfW, w - halfW);
		m_Player.pos.y = glm::clamp(m_Player.pos.y, halfH, h - halfH);

		return SceneType::Play;

	}


	void PlayScene::OnRender()
	{
		glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer2D::BeginFrame(m_Camera);

		Renderer2D::DrawQuad(m_Player.pos, m_Player.size, { 0.3f, 0.8f, 0.9f, 1.0f });

		Renderer2D::EndFrame();

	}

}