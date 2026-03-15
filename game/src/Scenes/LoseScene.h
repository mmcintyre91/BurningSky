#pragma once
#include "Scene.h"
#include "BurningSky/Graphics/OrthographicCamera.h"
#include "BurningSky/Graphics/TextureLibrary.h"

namespace BurningSky {
	class LoseScene : public Scene
	{
	public:
		explicit LoseScene(OrthographicCamera& camera, TextureLibrary& textures);

		SceneType OnUpdate(float dt) override;

		void OnRender() override;

	private:
		OrthographicCamera& m_Camera;
		float m_Timer = 0.0f;

		TextureLibrary& m_Textures;
	};

}