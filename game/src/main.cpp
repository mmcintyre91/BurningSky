#include <iostream>
#include <stdexcept>
#include <memory>
#include <glad/glad.h>
#include "BurningSky/Core/Window.h"


int main() 
{
	BurningSky::WindowProps props;
	props.Title = "Burning Sky - Test";

	std::unique_ptr<BurningSky::Window> window(BurningSky::Window::Create(props));

	while (!window->ShouldClose()) 
	{
		window->PollEvents();

		glClearColor(0.05f, 0.05f, 0.09f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window->SwapBuffer();
	}

	return 0;

}
