#pragma once

#include <glm/glm.hpp>

class ViewFrustum
{
private:
	glm::mat4 m_projectionMatrix;

	glm::vec2 m_distance;
	glm::vec2 m_size;
	float m_fov;
		
	void updateProjectionMatrix();

public:
	ViewFrustum(const glm::vec2& distance, const glm::vec2& size, float fov);

	const glm::mat4 getProjectionMatrix() const;

	const glm::vec2& getDistance() const;
	const glm::vec2& getSize() const;
	float getFov() const;

	void setDistance(const glm::vec2& distance);
	void setSize(const glm::vec2& size);
	void setFov(float fov);
};