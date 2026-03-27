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
		m_LastW = m_Window.GetWidth();
		m_LastH = m_Window.GetHeight();
		m_Camera.SetProjection(0.0f, (float)m_LastW, 0.0f, (float)m_LastH);
	}

	SceneType PlayScene::OnUpdate(float dt)
	{
		// --- Window size & camera projection update ---
		const int w = m_Window.GetWidth();
		const int h = m_Window.GetHeight();

		if (w != m_LastW || h != m_LastH)
		{
			m_LastW = w;
			m_LastH = h;
			m_Camera.SetProjection(0.0f, (float)w, 0.0f, (float)h);
		}

		const float wf = (float)w;
		const float hf = (float)h;

		// --- Movement input ---
		glm::vec2 dir(0.0f);

		if (Input::IsKeyDown(Key::A) || Input::IsKeyDown(Key::Left))  dir.x -= 1.0f;
		if (Input::IsKeyDown(Key::D) || Input::IsKeyDown(Key::Right)) dir.x += 1.0f;
		if (Input::IsKeyDown(Key::S) || Input::IsKeyDown(Key::Down))  dir.y -= 1.0f;
		if (Input::IsKeyDown(Key::W) || Input::IsKeyDown(Key::Up))    dir.y += 1.0f;

		if (dir.x != 0.0f || dir.y != 0.0f)
			dir = glm::normalize(dir);

		// Move in pixels/sec
		m_Player.pos += dir * m_Player.speed * dt;

		// --- Clamp to window bounds (center-based) ---
		const float halfW = m_Player.size.x * 0.5f;
		const float halfH = m_Player.size.y * 0.5f;

		m_Player.pos.x = glm::clamp(m_Player.pos.x, halfW, wf - halfW);
		m_Player.pos.y = glm::clamp(m_Player.pos.y, halfH, hf - halfH);

		// --- Background scroll (wrap) ---
		m_BackgroundOffsetY -= m_ScrollSpeed * dt;

		// Keep offset in [-hf, 0)
		if (m_BackgroundOffsetY <= -hf)
			m_BackgroundOffsetY += hf;

		return SceneType::Play;
	}


	void PlayScene::OnRender()
	{

		glClearColor(0.02f, 0.02f, 0.06f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float w = (float)m_Window.GetWidth();
		float h = (float)m_Window.GetHeight();

		//center pos for two stacked screens
		glm::vec2 bgSize(w, h);

		//base background tile centered at half screen, shifted by offset
		glm::vec2 bg1Pos(w * 0.5f, h * 0.5f + m_BackgroundOffsetY);
		glm::vec2 bg2Pos(w * 0.5f, h * 1.5f + m_BackgroundOffsetY);
		auto bg = m_Textures.Get("bg_mid");
		
		Renderer2D::BeginFrame(m_Camera);


		auto player = m_Textures.Get("ship");

		Renderer2D::DrawQuad(bg1Pos, bgSize, *bg);
		Renderer2D::DrawQuad(bg2Pos, bgSize, *bg);
		Renderer2D::DrawQuad(m_Player.pos, m_Player.size, *player);
	

		Renderer2D::EndFrame();

	}

}