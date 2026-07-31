#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(unsigned int width, unsigned int height) :
    m_position(0.0f, 0.0f, 40.0f),
    m_right(0.0f, 0.0f, 0.0f),
    m_up(0.0f, 0.0f, 0.0f),
    m_forward(0.0f, 0.0f, 0.0f),
    m_viewMatrix(glm::lookAt(m_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
    m_projectionMatrix(glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(glm::max(height, 1u)), 0.01f, 1000.0f))
{

}

glm::vec3 Camera::screenToWorld(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const
{
    float ndcX = (2.0f * x) / static_cast<float>(width) - 1.0f;
    float ndcY = 1.0f - (2.0f * y) / static_cast<float>(height);

    glm::vec4 nearClip(ndcX, ndcY, -1.0f, 1.0f);
    glm::vec4 farClip(ndcX, ndcY, 1.0f, 1.0f);

    glm::mat4 inverseViewProjection = glm::inverse(m_projectionMatrix * m_viewMatrix);

    glm::vec4 nearWorld = inverseViewProjection * nearClip;
    glm::vec4 farWorld = inverseViewProjection * farClip;

    nearWorld /= nearWorld.w;
    farWorld /= farWorld.w;

    glm::vec3 rayOrigin = glm::vec3(nearWorld);
    glm::vec3 rayDirection = glm::normalize(glm::vec3(farWorld - nearWorld));

    float t = -rayOrigin.z / rayDirection.z;

    return rayOrigin + t * rayDirection;
}

cft::View Camera::getView() const
{
    return cft::View{
        m_position,
        m_right,
        m_up,
        m_forward,
        m_viewMatrix,
        m_projectionMatrix
    };
}
