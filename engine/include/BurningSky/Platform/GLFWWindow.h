#pragma once
#include "BurningSky/Core/Window.h"

struct GLFWwindow;

namespace BurningSky {
	
	class GLFWWindow final : public Window{
	public:
		//constr gets WindowProps
		explicit GLFWWindow(const WindowProps& props);

		//destruc 
		~GLFWWindow() override;

		//implement interface
		void PollEvents() override;
		void SwapBuffer() override;
		bool ShouldClose() const override;

		void* GetNativeHandle() const override;

	private:
		void Init(const WindowProps& props);
		void Shutdown();

		GLFWwindow* m_Window = nullptr; // actual glfw handle
	};

}