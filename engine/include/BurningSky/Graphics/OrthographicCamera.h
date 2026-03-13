#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace BurningSky {
	
	class OrthographicCamera {
	public:
		//  left/right/bottom/top define the visible rect in world units(pixels)
		OrthographicCamera(float left, float right, float bottom, float top);


		//camera pos in world space
		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() const { return m_Position; }

		//camera rotation around z-axis. Optional for later
		void SetRotation(float degrees);
		float GetRotation() const { return m_Rotation; }

		//set the projection bounds (used when window size changes)
		void SetProjection(float left, float right, float bottom, float top);

		//combined matrix used by the Renderer2D
		//clip = ViewProjection * worldPosition
		const glm::mat4& GetViewProjection() const { return m_ViewProjection; }

	private:
		//recompute view and view-proj after pos/rotation changes
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_Projection{ 1.0f };
		glm::mat4 m_View{ 1.0f };
		glm::mat4 m_ViewProjection{ 1.0f };

		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f; //degrees
	};
}