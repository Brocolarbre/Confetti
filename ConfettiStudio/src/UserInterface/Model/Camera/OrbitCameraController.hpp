#pragma once

#include "CameraController.hpp"

class OrbitCameraController : public CameraController
{
private:
	glm::vec2 m_rotation;
	glm::vec3 m_target;
	glm::vec2 m_distanceLimit;
	glm::uvec2 m_mousePosition;

	bool m_isMoving;
	bool m_isSliding;

	float m_translationSpeed;
	float m_rotationSpeed;

	void updateCameraBasis() const;

public:
	OrbitCameraController(Camera& camera, dove::Window& window, const glm::vec3& position, const glm::vec3& target);

	const glm::vec2& getRotation() const;
	const glm::vec3& getTarget() const;
	const glm::vec2& getDistanceLimits() const;
	float getTranslationSpeed() const;
	float getRotationSpeed() const;

	void setTarget(const glm::vec3& target);
	void setDistanceLimits(const glm::vec2& distanceLimits);
	void setTranslationSpeed(float translationSpeed);
	void setRotationSpeed(float rotationSpeed);

	void onMouseMoved(unsigned int x, unsigned int y) override;
	void onMousePressed(dove::MouseEvent mouseEvent) override;
	void onMouseReleased(dove::MouseEvent mouseEvent) override;
	void onMouseScrolled(int horizontalScroll, int verticalScroll) override;

	void update() override;
};