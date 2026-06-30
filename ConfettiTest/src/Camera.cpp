#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(unsigned int width, unsigned int height) :
    m_position(0.0f, 0.0f, 40.0f),
    m_right(0.0f, 0.0f, 0.0f),
    m_up(0.0f, 0.0f, 0.0f),
    m_forward(0.0f, 0.0f, 0.0f),
    m_viewMatrix(glm::lookAt(m_position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))),
    m_projectionMatrix(glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.01f, 1000.0f))
{

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
