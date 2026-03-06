#include "BurningSky/Platform/GLFWWindow.h"

#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BurningSky {
	static void GLFWErrorCallback(int error, const char* description)
	{
		std::cerr << "[GLFW ERROR] (" << error << "): " << description << "\n";
	}

	GLFWWindow::GLFWWindow(const WindowProps& props)
	{
		Init(props);
	}

	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::Init(const WindowProps& props)
	{
		glfwSetErrorCallback(GLFWErrorCallback);

		if (!glfwInit()) throw std::runtime_error("Failed to Init GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(__APPLE__)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif // defined(__APPLE__)

		//create the window and opengl context
		m_Window = glfwCreateWindow(
			props.Width,
			props.Height,
			props.Title.c_str(),
			nullptr, // monitor null = windowed
			nullptr //share context null = no share
		);

		if (!m_Window)
			throw std::runtime_error("Failed to create GLFW Window");

		glfwMakeContextCurrent(m_Window);

		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to init GLAD");

		std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << "\n";
		std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << "\n";
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";


		int fbWidth = 0, fbHeight = 0;
		glfwGetFramebufferSize(m_Window, &fbWidth, &fbHeight);
		glViewport(0, 0, fbWidth, fbHeight);


		//set this pointer inside the window for callbacks
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
			});
	}


	void GLFWWindow::Shutdown()
	{
		//destroy the glwf window if it exists
		if (m_Window)
		{
			glfwDestroyWindow(m_Window);
			m_Window = nullptr;
		}
		glfwTerminate();
	}

	//interface functions

	void GLFWWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void GLFWWindow::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	bool GLFWWindow::ShouldClose() const 
	{
		//return true if user clicks the X or OS close
		return glfwWindowShouldClose(m_Window) == GLFW_TRUE;
	}

	void* GLFWWindow::GetNativeHandle() const 
	{
		return m_Window;
	}


}
