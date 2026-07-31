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

	unsigned int m_width;
	unsigned int m_height;

public:
	Camera(unsigned int width, unsigned int height);

	glm::vec3 screenToWorld(unsigned int x, unsigned int y) const;

	cft::View getView() const;
};