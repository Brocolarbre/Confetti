#pragma once

#include <glm/glm.hpp>

class ViewPlane
{
private:
	glm::mat4 m_projectionMatrix;
	glm::vec2 m_size;

	void updateProjectionMatrix();

public:
	ViewPlane(const glm::vec2& size);

	const glm::mat4& getProjectionMatrix() const;

	const glm::vec2& getSize() const;
	void setSize(const glm::vec2& size);
};