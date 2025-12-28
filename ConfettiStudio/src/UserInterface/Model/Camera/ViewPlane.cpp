#include "ViewPlane.hpp"

#include <glm/gtc/matrix_transform.hpp>

void ViewPlane::updateProjectionMatrix()
{
	m_projectionMatrix = glm::ortho(0.0f, m_size.x, 0.0f, m_size.y);
}

ViewPlane::ViewPlane(const glm::vec2& size) :
	m_projectionMatrix(),
	m_size(size)
{
	updateProjectionMatrix();
}

const glm::mat4& ViewPlane::getProjectionMatrix() const
{
	return m_projectionMatrix;
}

const glm::vec2& ViewPlane::getSize() const
{
	return m_size;
}

void ViewPlane::setSize(const glm::vec2& size)
{
	m_size = size;
	updateProjectionMatrix();
}