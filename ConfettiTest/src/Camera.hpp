#pragma once

#include <Confetti/Rendering/View.hpp>

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_right;
	glm::vec3 m_up;
	glm::vec3 m_forward;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

public:
	Camera(unsigned int width, unsigned int height);

	cft::View getView() const;
};