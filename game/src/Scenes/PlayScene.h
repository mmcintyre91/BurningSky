#pragma once
#include <memory>
#include "Scene.h"
#include "BurningSky/Core/Window.h"
#include "BurningSky/Graphics/OrthographicCamera.h"
#include "BurningSky/Graphics/Texture2D.h"
#include "BurningSky/Graphics/TextureLibrary.h"


namespace BurningSky {
	class PlayScene : public Scene
	{
	public:
		explicit PlayScene(OrthographicCamera& camera, TextureLibrary& textures, Window& window);

		SceneType OnUpdate(float dt) override;

		void OnRender() override;

		std::unique_ptr<BurningSky::Texture2D> m_TestTexture;

	private:
		OrthographicCamera& m_Camera;

		float m_Timer = 0.0f;

		TextureLibrary& m_Textures;

		Window& m_Window;

		struct Player {
			glm::vec2 pos{ 640.0f, 120.0f };
			glm::vec2 size{ 64.0f, 64.0f };
			float speed = 450.0f; //pix per sec
		} m_Player;
	};

}