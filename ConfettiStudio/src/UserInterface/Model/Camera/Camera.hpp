#pragma once

#include "ViewFrustum.hpp"
#include "ViewPlane.hpp"

class Camera
{
private:
	glm::mat4 m_viewMatrix;

	glm::vec3 m_position;
	glm::vec3 m_right;
	glm::vec3 m_up;
	glm::vec3 m_forward;

	ViewFrustum m_viewFrustum;
	ViewPlane m_viewPlane;

public:
	Camera(const glm::vec3& position, const glm::vec2& size);

	const glm::mat4& getViewMatrix() const;

	const glm::vec3& getPosition() const;
	const glm::vec3& getRight() const;
	const glm::vec3& getUp() const;
	const glm::vec3& getForward() const;

	void setPosition(const glm::vec3& position);
	void setRight(const glm::vec3& right);
	void setUp(const glm::vec3& up);
	void setForward(const glm::vec3& forward);

	const ViewFrustum& getViewFrustum() const;
	ViewFrustum& getViewFrustum();

	const ViewPlane& getViewPlane() const;
	ViewPlane& getViewPlane();

	void updateViewMatrix();

	static glm::vec3 WORLD_UP;
};