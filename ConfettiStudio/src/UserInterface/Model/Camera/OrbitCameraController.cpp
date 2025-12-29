#include "OrbitCameraController.hpp"

void OrbitCameraController::updateCameraBasis() const
{
	float distance = glm::max(glm::distance(m_camera.getPosition(), m_target), 0.001f);
	
	glm::vec3 position(
		glm::cos(glm::radians(m_rotation.y)) * glm::cos(glm::radians(m_rotation.x)),
		-glm::sin(glm::radians(m_rotation.x)),
		glm::sin(glm::radians(m_rotation.y)) * glm::cos(glm::radians(m_rotation.x))
	);

	position *= distance;
	position += m_target;

	glm::vec3 forward = glm::normalize(m_target - position);
	glm::vec3 right = glm::normalize(glm::cross(forward, Camera::WORLD_UP));
	glm::vec3 up = glm::normalize(glm::cross(right, forward));

	m_camera.setPosition(position);
	m_camera.setForward(forward);
	m_camera.setRight(right);
	m_camera.setUp(up);

	m_camera.updateViewMatrix();
}

OrbitCameraController::OrbitCameraController(Camera& camera, dove::Window& window, const glm::vec3& position, const glm::vec3& target) :
	CameraController(camera, window),
	m_rotation(0.0f),
	m_target(target),
	m_distanceLimit(0.1f, 100.0f),
	m_mousePosition(0),
	m_isRotating(false),
	m_isSliding(false),
	m_rotationSpeed(0.1f),
	m_slideSpeed(0.1f),
	m_scrollSpeed(0.1f)
{
	glm::vec3 direction = glm::normalize(position - target);

	m_rotation.x = glm::degrees(glm::asin(-direction.y));
	m_rotation.y = glm::degrees(glm::atan(direction.z, direction.x));

	m_camera.setPosition(position);
	updateCameraBasis();
}

const glm::vec2& OrbitCameraController::getRotation() const
{
	return m_rotation;
}

const glm::vec3& OrbitCameraController::getTarget() const
{
	return m_target;
}

const glm::vec2& OrbitCameraController::getDistanceLimits() const
{
	return m_distanceLimit;
}

float OrbitCameraController::getRotationSpeed() const
{
	return m_rotationSpeed;
}

float OrbitCameraController::getSlideSpeed() const
{
	return m_slideSpeed;
}

float OrbitCameraController::getScrollSpeed() const
{
	return m_scrollSpeed;
}

void OrbitCameraController::setTarget(const glm::vec3& target)
{
	m_target = target;
	updateCameraBasis();
}

void OrbitCameraController::setDistanceLimits(const glm::vec2& distanceLimits)
{
	m_distanceLimit = distanceLimits;
}

void OrbitCameraController::setRotationSpeed(float rotationSpeed)
{
	m_rotationSpeed = rotationSpeed;
}

void OrbitCameraController::setSlideSpeed(float translationSpeed)
{
	m_slideSpeed = translationSpeed;
}

void OrbitCameraController::setScrollSpeed(float scrollSpeed)
{
	m_scrollSpeed = scrollSpeed;
}

void OrbitCameraController::onMouseMoved(unsigned int x, unsigned int y)
{
	if (!m_isRotating && !m_isSliding)
		return;

	float horizontalOffset = static_cast<float>(static_cast<int>(m_mousePosition.x) - static_cast<int>(x));
	float verticalOffset = static_cast<float>(static_cast<int>(m_mousePosition.y) - static_cast<int>(y));

	m_mousePosition.x = x;
	m_mousePosition.y = y;

	if (m_isRotating)
	{
		m_rotation += glm::vec2(verticalOffset * m_rotationSpeed, -horizontalOffset * m_rotationSpeed);

		m_rotation.x = glm::clamp(m_rotation.x, -89.999f, 89.999f);
		if (m_rotation.y > 360.0f)
			m_rotation.y -= 360.0f;
		else if (m_rotation.y < 0.0f)
			m_rotation.y += 360.0f;
	}
	else if (m_isSliding)
	{
		glm::vec3 position = m_camera.getPosition() + m_camera.getRight() * (horizontalOffset * m_slideSpeed) + m_camera.getUp() * (-verticalOffset * m_slideSpeed);
		m_camera.setPosition(position);
		m_target = position + m_camera.getForward() * glm::distance(position, m_target);
	}

	updateCameraBasis();
}

void OrbitCameraController::onMousePressed(dove::MouseEvent mouseEvent)
{
	if (mouseEvent.button == dove::Mouse::Button::Left)
		m_isRotating = true;
	else if (mouseEvent.button == dove::Mouse::Button::Right)
		m_isSliding = true;

	m_mousePosition.x = mouseEvent.x;
	m_mousePosition.y = mouseEvent.y;
}

void OrbitCameraController::onMouseReleased(dove::MouseEvent mouseEvent)
{
	if (mouseEvent.button == dove::Mouse::Button::Left)
		m_isRotating = false;
	else if (mouseEvent.button == dove::Mouse::Button::Right)
		m_isSliding = false;
}

void OrbitCameraController::onMouseScrolled(int horizontalScroll, int verticalScroll)
{
	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::LeftControl))
	{
		ViewFrustum& viewFrustum = m_camera.getViewFrustum();
		viewFrustum.setFov(glm::clamp(viewFrustum.getFov() - verticalScroll, 1.0f, 359.0f));
	}
	else
	{
		glm::vec3 position = m_camera.getPosition() + verticalScroll * m_scrollSpeed * m_camera.getForward();
		float distance = glm::distance(position, m_target);

		if (distance >= m_distanceLimit.x && distance <= m_distanceLimit.y)
		{
			m_camera.setPosition(position);
			m_camera.updateViewMatrix();
		}
	}
}

void OrbitCameraController::update()
{
	const glm::vec3& cameraPosition = m_camera.getPosition();
	const glm::vec3& cameraRight = m_camera.getRight();
	const glm::vec3& cameraForward = m_camera.getForward();

	bool cameraMoved = false;

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::D))
	{
		m_camera.setPosition(cameraPosition + m_slideSpeed * cameraRight);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::A))
	{
		m_camera.setPosition(cameraPosition - m_slideSpeed * cameraRight);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::Space))
	{
		m_camera.setPosition(cameraPosition + m_slideSpeed * Camera::WORLD_UP);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::LeftShift))
	{
		m_camera.setPosition(cameraPosition - m_slideSpeed * Camera::WORLD_UP);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::W))
	{
		m_camera.setPosition(cameraPosition + m_slideSpeed * cameraForward);
		cameraMoved = true;
	}

	if (dove::Keyboard::isKeyPressed(m_window, dove::Keyboard::Key::S))
	{
		m_camera.setPosition(cameraPosition - m_slideSpeed * cameraForward);
		cameraMoved = true;
	}

	if (cameraMoved)
	{
		const glm::vec3& position = m_camera.getPosition();
		m_target = position + m_camera.getForward() * glm::distance(position, m_target);
		updateCameraBasis();
	}
}