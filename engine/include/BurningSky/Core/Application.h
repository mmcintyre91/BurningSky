#pragma once

#include <memory>
#include <vector>

#include "BurningSky/Core/Window.h"
#include "BurningSky/Core/Layer.h"

namespace BurningSky {
	//owns window + main loop
	//calls OnUpdate/OnRender on all layers.
	class Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(std::unique_ptr<Layer> layer);

		Window& GetWindow() { return *m_Window; }

	protected:
		//optional app wide update hook
		virtual void OnAppUpdate(float dt) { (void)dt; }

	private:
		std::unique_ptr<Window> m_Window;
		std::vector<std::unique_ptr<Layer>> m_Layers;

	};
}