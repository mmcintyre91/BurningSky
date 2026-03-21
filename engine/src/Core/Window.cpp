#include "BurningSky/Core/Window.h"
#include "BurningSky/Platform/GLFWWindow.h"

namespace BurningSky{

	Window* Window::Create(const WindowProps& props) 
	{

		return new GLFWWindow(props);
	}

}