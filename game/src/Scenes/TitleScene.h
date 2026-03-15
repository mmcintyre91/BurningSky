#pragma once
#include "Scene.h"
#include "BurningSky/Graphics/OrthographicCamera.h"
#include "BurningSky/Graphics/TextureLibrary.h"


namespace BurningSky {
	class TitleScene : public Scene
	{
	public:
		explicit TitleScene(OrthographicCamera& camera, TextureLibrary& textures);

		SceneType OnUpdate(float dt) override;

		void OnRender() override;

	private:
		OrthographicCamera& m_Camera;
		float m_Timer = 0.0f;

		TextureLibrary& m_Textures;
	};

}