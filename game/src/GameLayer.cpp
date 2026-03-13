#include "GameLayer.h"

#include "Scenes/TitleScene.h"
#include "Scenes/PlayScene.h"
#include "Scenes/LoseScene.h"

#include "BurningSky/Graphics/Renderer2D.h"

namespace BurningSky {

	GameLayer::GameLayer() :
		Layer("GameLayer"),
		m_Camera(0.0f, 1280.0f, 0.0f, 720.0f) 
	{
	}

	void GameLayer::OnAttach() 
	{
		Renderer2D::Init();
		SwitchScene(SceneType::Title);
	}

	void GameLayer::OnDetach() 
	{
		if (m_CurrentScene) 
		{
			m_CurrentScene->OnExit();
		}

		Renderer2D::Shutdown();
	}

	void GameLayer::OnUpdate(float dt) 
	{
		if (!m_CurrentScene) return;
		
		SceneType requested = m_CurrentScene->OnUpdate(dt);
		if (requested != m_CurrentType) 
		{
			SwitchScene(requested);
		}
	}

	void GameLayer::OnRender() 
	{
		if (m_CurrentScene)
			m_CurrentScene->OnRender();

	}

	void GameLayer::SwitchScene(SceneType type) 
	{
		if (m_CurrentScene)
			m_CurrentScene->OnExit();

		m_CurrentType = type;

		switch (type) 
		{
			case SceneType::Title: m_CurrentScene = std::make_unique<TitleScene>(m_Camera); break;
			case SceneType::Play: m_CurrentScene = std::make_unique<PlayScene>(m_Camera); break;
			case SceneType::Lose: m_CurrentScene = std::make_unique<LoseScene>(m_Camera); break;
		}

		m_CurrentScene->OnEnter();
	}
}