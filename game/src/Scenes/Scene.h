#pragma once

namespace BurningSky {
	
	enum class SceneType {
		Title,
		Play,
		Lose
	};

	//scene is game level state. not engine level
	class Scene 
	{
	public:
		virtual ~Scene() = default;

		//called when scene becomes active
		virtual void OnEnter() {}

		//called when scene is about to be replaced
		virtual void OnExit() {}

		//update returns desired next scene
		//return the current scene type to stay
		virtual SceneType OnUpdate(float dt) = 0;

		//render scene
		virtual void OnRender() = 0;
	};

}