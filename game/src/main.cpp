#include <iostream>
#include <stdexcept>
#include <memory>

#include <glad/glad.h>

#include "BurningSky/Core/Window.h"
#include "BurningSky/Graphics/Shader.h"
#include "BurningSky/Graphics/VertexArray.h"
#include "BurningSky/Graphics/VertexBuffer.h"
#include "BurningSky/Graphics/IndexBuffer.h"


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

    //quad in NDC :: 4 vertices
    // (x,y)
    float quadVertices[] = {
        -0.5f, -0.5f, //bot left
        0.5f, -0.5f, //bot right
        0.5f, 0.5f, //top right
        -0.5f, 0.5f //top left
    };

    //two triangles using the indices (0,1,2) and (2,3,0)
    unsigned int quadIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    //create VAO and attach buffers
    BurningSky::VertexArray vao;

    auto vbo = std::make_unique<BurningSky::VertexBuffer>(quadVertices, sizeof(quadVertices));
    vao.SetVertexBuffer(std::move(vbo));

    auto ibo = std::make_unique<BurningSky::IndexBuffer>(quadIndices, 6);
    vao.SetIndexBuffer(std::move(ibo));



    // -----------------------------
    // Main loop
    // -----------------------------
    while (!window->ShouldClose())
    {
        window->PollEvents();

      

        // Clear the screen each frame
        glClearColor(0.05f, 0.05f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        shader.Bind();
        shader.SetFloat4("u_Color", 0.2f, 0.8f, 0.4f, 1.0f);

        vao.Bind();

        glDrawElements(GL_TRIANGLES, vao.GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr);
        vao.Unbind();

        window->SwapBuffer(); // or SwapBuffers if you later standardize on that name
    }

    return 0;
}