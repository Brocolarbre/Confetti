#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::vec3 Camera::WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera(const glm::vec3& position, const glm::vec2& size) :
	m_viewMatrix(),
	m_position(position),
	m_right(glm::vec3(1.0f, 0.0f, 0.0f)),
	m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_forward(glm::vec3(0.0f, 0.0f, 1.0f)),
	m_viewFrustum(glm::vec2(0.1f, 1000.0f), size, 45.0f),
	m_viewPlane(size)
{
	updateViewMatrix();
}

const glm::mat4& Camera::getViewMatrix() const
{
	return m_viewMatrix;
}

const glm::vec3& Camera::getPosition() const
{
	return m_position;
}

const glm::vec3& Camera::getRight() const
{
	return m_right;
}

const glm::vec3& Camera::getUp() const
{
	return m_up;
}

const glm::vec3& Camera::getForward() const
{
	return m_forward;
}

void Camera::setPosition(const glm::vec3& position)
{
	m_position = position;
}

void Camera::setRight(const glm::vec3& right)
{
	m_right = right;
}

void Camera::setUp(const glm::vec3& up)
{
	m_up = up;
}

void Camera::setForward(const glm::vec3& forward)
{
	m_forward = forward;
}

const ViewFrustum& Camera::getViewFrustum() const
{
	return m_viewFrustum;
}

ViewFrustum& Camera::getViewFrustum()
{
	return m_viewFrustum;
}

const ViewPlane& Camera::getViewPlane() const
{
	return m_viewPlane;
}

ViewPlane& Camera::getViewPlane()
{
	return m_viewPlane;
}

void Camera::updateViewMatrix()
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
}