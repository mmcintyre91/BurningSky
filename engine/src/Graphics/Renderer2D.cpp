#include "BurningSky/Graphics/Renderer2D.h"
#include "BurningSky/Graphics/Shader.h"
#include "BurningSky/Graphics/VertexArray.h"
#include "BurningSky/Graphics/VertexBuffer.h"
#include "BurningSky/Graphics/IndexBuffer.h"
#include "BurningSky/Graphics/OrthographicCamera.h"
#include "BurningSky/Graphics/Texture2D.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BurningSky {
	std::unique_ptr<VertexArray> Renderer2D::s_QuadVAO;
	std::unique_ptr<Shader> Renderer2D::s_ColorShader;
    std::unique_ptr<Shader> Renderer2D::s_TextureShader;
    glm::mat4 Renderer2D::s_ViewProjection{ 1.0f };



	void Renderer2D::Init() 
	{
        float quadVertices[] = {
            //  x,    y,    u,    v
            -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-left
             0.5f, -0.5f, 1.0f, 0.0f,  // bottom-right
             0.5f,  0.5f, 1.0f, 1.0f,  // top-right
            -0.5f,  0.5f, 0.0f, 1.0f   // top-left
        };

        //two triangles using the indices (0,1,2) and (2,3,0)
        unsigned int quadIndices[] = {
            0, 1, 2,
            2, 3, 0
        };

        //create VAO obj
        s_QuadVAO = std::make_unique<VertexArray>();

        //create and attach VBO
        auto vbo = std::make_unique<VertexBuffer>(quadVertices, sizeof(quadVertices));
        s_QuadVAO->SetVertexBuffer(std::move(vbo));

        //create and attach ibo
        auto ibo = std::make_unique<IndexBuffer>(quadIndices, 6);
        s_QuadVAO->SetIndexBuffer(std::move(ibo));

        //load the shader used to draw colored quads

        s_ColorShader = std::make_unique<Shader>(
            "assets/shaders/renderer2d_color.vert",
            "assets/shaders/renderer2d_color.frag"
        );

        //load the shader used to draw textured quads (ie assets/textures)
        s_TextureShader = std::make_unique<Shader>(
            "assets/shaders/renderer2d_texture.vert",
            "assets/shaders/renderer2d_texture.frag"
        );

        s_TextureShader->Bind();
        s_TextureShader->SetInt("u_Texture", 0);
	}

    void Renderer2D::Shutdown() 
    {
        // unique_ptr cleanup will destroy the resources.
        // - VertexArray destructor deletes the VAO
        // - VertexBuffer/IndexBuffer destructors delete their buffers
        // - Shader destructor deletes the program
        s_ColorShader.reset();
        s_TextureShader.reset();
        s_QuadVAO.reset();
    }

    void Renderer2D::BeginFrame(const OrthographicCamera& camera) 
    {
        s_ViewProjection = camera.GetViewProjection();
    }

    void Renderer2D::EndFrame() 
    {
    
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        // Build a model matrix (translate + scale)
        // This matrix transforms our unit quad into the correct position/size.
        // Currently position/size are in NDC units:
        // - position (0,0) is screen center
        // - x,y ranges around [-1,1]
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

        //bind shader and set uniforms
        s_ColorShader->Bind();
        s_ColorShader->SetMat4("u_ViewProjection", s_ViewProjection);
        s_ColorShader->SetMat4("u_Model", model);
        s_ColorShader->SetFloat4("u_Color", color.r, color.g, color.b, color.a);

        //bind geometry and draw
        s_QuadVAO->Bind();
        glDrawElements(
            GL_TRIANGLES,
            s_QuadVAO->GetIndexBuffer().GetCount(),
            GL_UNSIGNED_INT,
            nullptr
        );
        VertexArray::Unbind();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size,
        const Texture2D& texture, const glm::vec4& tint) 
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

        s_TextureShader->Bind();
        s_TextureShader->SetMat4("u_ViewProjection", s_ViewProjection);
        s_TextureShader->SetMat4("u_Model", model);
        s_TextureShader->SetFloat4("u_Tint", tint.r, tint.g, tint.b, tint.a);

        texture.Bind(0);

        //bind geometry and draw
        s_QuadVAO->Bind();
        glDrawElements(
            GL_TRIANGLES,
            s_QuadVAO->GetIndexBuffer().GetCount(),
            GL_UNSIGNED_INT,
            nullptr
        );
        VertexArray::Unbind();
    }


    void Renderer2D::DrawSprite(const glm::vec2& position, const Texture2D& texture,
        const glm::vec4& tint) 
    {

        //auto size, use the textures pixel dimensions as draw size
        DrawQuad(position,
            { (float)texture.GetWidth(), (float)texture.GetHeight() },
            texture,
            tint);
    }


}