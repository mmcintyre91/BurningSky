#include <iostream>
#include <stdexcept>
#include <memory>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "BurningSky/Core/Window.h"
#include "BurningSky/Graphics/Shader.h"
#include "BurningSky/Graphics/VertexArray.h"
#include "BurningSky/Graphics/VertexBuffer.h"
#include "BurningSky/Graphics/IndexBuffer.h"
#include "BurningSky/Graphics/Renderer2D.h"
#include "BurningSky/Graphics/OrthographicCamera.h"


int main()
{
	BurningSky::WindowProps props;
	props.Title = "Burning Sky - Test";
    props.Width = 1280;
    props.Height = 720;

	std::unique_ptr<BurningSky::Window> window(BurningSky::Window::Create(props));

    BurningSky::Renderer2D::Init();

    //pixel camera: (0,0) bottom left, (width,height) top right
    BurningSky::OrthographicCamera camera(0.0f, (float)props.Width, 0.0f, (float)props.Height);

    // -----------------------------
    // Main loop
    // -----------------------------
    while (!window->ShouldClose())
    {
        window->PollEvents();

      

        // Clear the screen each frame
        glClearColor(0.05f, 0.05f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        BurningSky::Renderer2D::BeginFrame(camera);
        
        // Draw a 200x200 quad centered around (640,360)
        BurningSky::Renderer2D::DrawQuad({ 640.0f, 360.0f }, { 200.0f, 200.0f }, { 0.2f, 0.8f, 0.4f, 1.0f });

        // Draw a "pillar" on the left
        BurningSky::Renderer2D::DrawQuad({ 150.0f, 360.0f }, { 60.0f, 400.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });

        BurningSky::Renderer2D::EndFrame();



        window->SwapBuffer(); // or SwapBuffers if you later standardize on that name
    }
    BurningSky::Renderer2D::Shutdown();

    return 0;
}