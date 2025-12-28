#pragma once

#include "CameraController.hpp"

class FirstPersonCameraController : public CameraController
{
private:
	glm::vec2 m_rotation;
	glm::uvec2 m_mousePosition;

	bool m_isMoving;
	bool m_isSliding;

	float m_translationSpeed;
	float m_rotationSpeed;

	void updateCameraBasis() const;

public:
	FirstPersonCameraController(Camera& camera, dove::Window& window);

	const glm::vec2& getRotation() const;

	void onMouseMoved(unsigned int x, unsigned int y) override;
	void onMousePressed(dove::MouseEvent mouseEvent) override;
	void onMouseReleased(dove::MouseEvent mouseEvent) override;
	void onMouseScrolled(int horizontalScroll, int verticalScroll) override;

	void update() override;
};