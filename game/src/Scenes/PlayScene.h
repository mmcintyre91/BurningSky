#pragma once
#include <memory>
#include "Scene.h"
#include "BurningSky/Graphics/OrthographicCamera.h"
#include "BurningSky/Graphics/Texture2D.h"
#include "BurningSky/Graphics/TextureLibrary.h"


namespace BurningSky {
	class PlayScene : public Scene
	{
	public:
		explicit PlayScene(OrthographicCamera& camera, TextureLibrary& textures);

		SceneType OnUpdate(float dt) override;

		void OnRender() override;

		std::unique_ptr<BurningSky::Texture2D> m_TestTexture;

	private:
		OrthographicCamera& m_Camera;
		float m_Timer = 0.0f;

		TextureLibrary& m_Textures;
	};

}