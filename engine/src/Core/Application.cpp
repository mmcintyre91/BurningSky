#include "BurningSky/Core/Application.h"
#include "BurningSky/Core/Input.h"

#include <chrono>

namespace BurningSky {

	Application::Application() 
	{
		//create the platform window thru Window class
		m_Window.reset(Window::Create(WindowProps{}));
		Input::SetWindow(m_Window.get());
	}


	Application::~Application() 
	{
		//detach layers (reverse order)
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it) 
		{
			(*it)->OnDetach();
		}
	
	}

	void Application::PushLayer(std::unique_ptr<Layer> layer) 
	{
		layer->SetWindow(m_Window.get());
		layer->OnAttach();
		m_Layers.emplace_back(std::move(layer));
	}

	void Application::Run() 
	{
		using clock = std::chrono::high_resolution_clock;

		auto last = clock::now();

		while (!m_Window->ShouldClose()) 
		{
			auto now = clock::now();
			std::chrono::duration<float> elapsed = now - last;
			last = now;

			float dt = elapsed.count();

			m_Window->PollEvents();

			OnAppUpdate(dt);


			for (auto& layer : m_Layers)
				layer->OnUpdate(dt);

			for (auto& layer : m_Layers)
				layer->OnRender();

			m_Window->SwapBuffer();
		}
	}

}

