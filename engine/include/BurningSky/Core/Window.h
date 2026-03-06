#pragma once
#include <string>

namespace BurningSky
{
	struct WindowProps {
		std::string Title = "Burning Sky";
		int Width = 1280;
		int Height = 720;
	};


	class Window {
	public:
		//virt destructor, use Window* or std::unique_ptr<Window> when destroying.
		virtual ~Window() = default;

		//poll OS events
		virtual void PollEvents() = 0;

		//swap the front/back buffers
		virtual void SwapBuffer() = 0;

		//true if user clicks close
		virtual bool ShouldClose() const = 0;

		// Gives access to the underlying platform handle (GLFWwindow* later).
		// Returned as void* so engine headers don’t need GLFW includes.
		virtual void* GetNativeHandle() const = 0;

		// “Factory” function: creates the correct Window implementation
		// for the current platform (GLFWWindow on Windows for now).
		// This lets game code ask for “a Window” without knowing the platform class.
		static Window* Create(const WindowProps& props);

	};



}