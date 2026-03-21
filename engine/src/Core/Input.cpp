#include "BurningSky/Core/Input.h"
#include "BurningSky/Core/Window.h"

#include <stdexcept>

#include <GLFW/glfw3.h>

namespace BurningSky {
	
	Window* Input::s_Window = nullptr;

	void Input::SetWindow(Window* window) 
	{
		s_Window = window;
	}

	bool Input::IsKeyDown(Key key) 
	{
		if (!s_Window)
			throw std::runtime_error("Input::SetWindow must be called before input::IsKeyDown");

		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(s_Window->GetNativeHandle());

		int glfwKey = ToGLFWKey(key);
		int state = glfwGetKey(glfwWindow, glfwKey);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	int Input::ToGLFWKey(Key key) {
		switch (key)
		{
		case Key::A: return GLFW_KEY_A;
		case Key::D: return GLFW_KEY_D;
		case Key::W: return GLFW_KEY_W;
		case Key::S: return GLFW_KEY_S;
		case Key::Space: return GLFW_KEY_SPACE;
		case Key::Left: return GLFW_KEY_LEFT;
		case Key::Right: return GLFW_KEY_RIGHT;
		case Key::Up: return GLFW_KEY_UP;
		case Key::Down: return GLFW_KEY_DOWN;
		case Key::Escape: return GLFW_KEY_ESCAPE;
		default: return GLFW_KEY_UNKNOWN;
		}
	}

}