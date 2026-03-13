#include "BurningSky/Graphics/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp> //ortho, translate, rotate

namespace BurningSky {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
	{
		//projection matrix converts from world coord > clip coords
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

		//start with identity matrix (camera at origin)
		m_View = glm::mat4(1.0f);

		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) 
	{
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjection = m_Projection * m_View;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position) 
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float degrees) 
	{
		m_Rotation = degrees;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix() 
	{
		//view matrix is the inverese of cam transform. I.e. if camera moves +x, the world appears to move -x
		//camera transform = translate * rotate
		//view = inverese(camera transform)

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f),
			glm::radians(m_Rotation),
			glm::vec3(0.0f, 0.0f, 1.0f));

		m_View = glm::inverse(transform);
		m_ViewProjection = m_Projection * m_View;
	
	}

}

