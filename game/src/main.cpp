#include <iostream>
#include <stdexcept>
#include <memory>

#include <glad/glad.h>

#include "BurningSky/Core/Window.h"
#include "BurningSky/Graphics/Shader.h"

int main()
{
	BurningSky::WindowProps props;
	props.Title = "Burning Sky - Test";

	std::unique_ptr<BurningSky::Window> window(BurningSky::Window::Create(props));

	//shader files loaded from current working dir.
	BurningSky::Shader shader(
		"assets/shaders/simple.vert",
		"assets/shaders/simple.frag"
		);

	shader.Bind();

	float time = 0.0f;

	while (!window->ShouldClose()) 
	{
		window->PollEvents();

		time += 0.016f; 
		shader.SetFloat("u_Time", time);

		glClearColor(0.05f, 0.05f, 0.09f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window->SwapBuffer();
	}

	return 0;

}
