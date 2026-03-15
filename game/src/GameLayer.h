#pragma once
#include <memory>

#include "Scenes/Scene.h"
#include "BurningSky/Core/Layer.h"
#include "BurningSky/Graphics/OrthographicCamera.h"
#include "BurningSky/Graphics/TextureLibrary.h"

namespace BurningSky {
	
	class GameLayer : public Layer 
	{
	public:
		GameLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnRender() override;

	private:
		void SwitchScene(SceneType type);

	private:
		OrthographicCamera m_Camera;

		SceneType m_CurrentType = SceneType::Title;
		std::unique_ptr<Scene> m_CurrentScene;

		TextureLibrary m_Textures;
	};


}