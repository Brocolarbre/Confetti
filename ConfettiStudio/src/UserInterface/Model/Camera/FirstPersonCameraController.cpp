#include "FirstPersonCameraController.hpp"

#include <algorithm>

void FirstPersonCameraController::updateCameraBasis() const
{
	glm::vec3 forward = glm::normalize(glm::vec3(
		std::cos(glm::radians(m_rotation.y)) * std::cos(glm::radians(m_rotation.x)),
		std::sin(glm::radians(m_rotation.x)),
		std::sin(glm::radians(m_rotation.y)) * std::cos(glm::radians(m_rotation.x))
	));
	glm::vec3 right = glm::normalize(glm::cross(forward, Camera::WORLD_UP));
	glm::vec3 up = glm::normalize(glm::cross(right, forward));

	m_camera.setRight(right);
	m_camera.setUp(up);
	m_camera.setForward(forward);

	m_camera.updateViewMatrix();
}

FirstPersonCameraController::FirstPersonCameraController(Camera& camera, dove::Window& window) :
	CameraController(camera, window),
	m_rotation(0.0f),
	m_mousePosition(0),
	m_isMoving(false),
	m_isSliding(false),
	m_translationSpeed(0.1f),
	m_rotationSpeed(0.1f)
{
	updateCameraBasis();
}

const glm::vec2& FirstPersonCameraController::getRotation() const
{
	return m_rotation;
}

void FirstPersonCameraController::onMouseMoved(unsigned int x, unsigned int y)
{
	if (!m_isMoving && !m_isSliding)
		return;

	float horizontalOffset = static_cast<float>(static_cast<int>(m_mousePosition.x) - static_cast<int>(x));
	float verticalOffset = static_cast<float>(static_cast<int>(m_mousePosition.y) - static_cast<int>(y));

	m_mousePosition.x = x;
	m_mousePosition.y = y;

	if (m_isMoving)
	{
		m_rotation += glm::vec2(verticalOffset * m_rotationSpeed, -horizontalOffset * m_rotationSpeed);
		
		m_rotation.x = std::clamp(m_rotation.x, -89.999f, 89.999f);
		if (m_rotation.y > 360.0f)
			m_rotation.y -= 360.0f;
		else if (m_rotation.y < 0.0f)
			m_rotation.y += 360.0f;
	}
	else if (m_isSliding)
	{
		glm::vec3 origin = m_camera.getPosition() + m_camera.getRight() * (horizontalOffset * m_translationSpeed) + m_camera.getUp() * (-verticalOffset * m_translationSpeed);
		m_camera.setPosition(origin);
	}

	updateCameraBasis();
}

void FirstPersonCameraController::onMousePressed(dove::MouseEvent mouseEvent)
{
	if (mouseEvent.button == dove::Mouse::Button::Left)
		m_isMoving = true;
	else if (mouseEvent.button == dove::Mouse::Button::Right)
		m_isSliding = true;

	m_mousePosition.x = mouseEvent.x;
	m_mousePosition.y = mouseEvent.y;
}

void FirstPersonCameraController::onMouseReleased(dove::MouseEvent mouseEvent)
{
	if (mouseEvent.button == dove::Mouse::Button::Left)
		m_isMoving = false;
	else if (mouseEvent.button == dove::Mouse::Button::Right)
		m_isSliding = false;
}

void FirstPersonCameraController::onMouseScrolled(int horizontalScroll, int verticalScroll)
{
	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::LeftControl))
	{
		ViewFrustum& viewFrustum = m_camera.getViewFrustum();
		viewFrustum.setFov(glm::clamp(viewFrustum.getFov() - verticalScroll, 1.0f, 359.0f));
	}
	else
	{
		m_camera.setPosition(m_camera.getPosition() + verticalScroll * m_translationSpeed * 10.0f * m_camera.getForward());
		m_camera.updateViewMatrix();
	}
}

void FirstPersonCameraController::update()
{
	const glm::vec3& cameraOrigin = m_camera.getPosition();
	const glm::vec3& cameraRight = m_camera.getRight();
	const glm::vec3& cameraForward = m_camera.getForward();

	bool cameraMoved = false;

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::D))
	{
		m_camera.setPosition(cameraOrigin + m_translationSpeed * cameraRight);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::A))
	{
		m_camera.setPosition(cameraOrigin - m_translationSpeed * cameraRight);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::Space))
	{
		m_camera.setPosition(cameraOrigin + m_translationSpeed * Camera::WORLD_UP);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::LeftShift))
	{
		m_camera.setPosition(cameraOrigin - m_translationSpeed * Camera::WORLD_UP);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::W))
	{
		m_camera.setPosition(cameraOrigin + m_translationSpeed * cameraForward);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::S))
	{
		m_camera.setPosition(cameraOrigin - m_translationSpeed * cameraForward);
		cameraMoved = true;
	}

	if (cameraMoved)
		updateCameraBasis();
}