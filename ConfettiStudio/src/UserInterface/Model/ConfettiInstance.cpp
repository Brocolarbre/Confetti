#include "ConfettiInstance.hpp"

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_renderer(width, height),
    m_particleSimulation(),
    m_camera(glm::vec3(0.0f), glm::vec2(width, height)),
    m_cameraController(m_camera, window, glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f))
{
    m_cameraController.setSlideSpeed(0.1f);
}

cft::Renderer& ConfettiInstance::getRenderer()
{
    return m_renderer;
}

void ConfettiInstance::update()
{
    m_cameraController.update();
    m_particleSimulation.update();
}

void ConfettiInstance::render()
{
    const glm::mat4& viewMatrix = m_camera.getViewMatrix();
    const glm::mat4& projectionMatrix = m_camera.getViewFrustum().getProjectionMatrix();

    cft::View view{
        m_camera.getPosition(),
        m_camera.getRight(),
        m_camera.getUp(),
        m_camera.getForward(),
        viewMatrix,
        projectionMatrix
    };

    m_renderer.render(view, m_particleSimulation.getParticleSystem().getParticleData(), m_particleSimulation.getParticleSystem().getParticleCount());
}