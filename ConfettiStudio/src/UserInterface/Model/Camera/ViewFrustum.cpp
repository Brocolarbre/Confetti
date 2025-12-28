#include "ViewFrustum.hpp"

#include <glm/gtc/matrix_transform.hpp>

void ViewFrustum::updateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_size.x / m_size.y, m_distance.x, m_distance.y);
}

ViewFrustum::ViewFrustum(const glm::vec2& distance, const glm::vec2& size, float fov) :
	m_projectionMatrix(),
	m_distance(distance),
	m_size(size),
	m_fov(fov)
{
	updateProjectionMatrix();
}

const glm::mat4 ViewFrustum::getProjectionMatrix() const
{
	return m_projectionMatrix;
}

const glm::vec2& ViewFrustum::getDistance() const
{
	return m_distance;
}

const glm::vec2& ViewFrustum::getSize() const
{
	return m_size;
}

float ViewFrustum::getFov() const
{
	return m_fov;
}

void ViewFrustum::setDistance(const glm::vec2& distance)
{
	m_distance = distance;
	updateProjectionMatrix();
}

void ViewFrustum::setSize(const glm::vec2& size)
{
	m_size = size;
	updateProjectionMatrix();
}

void ViewFrustum::setFov(float fov)
{
	m_fov = fov;
	updateProjectionMatrix();
}