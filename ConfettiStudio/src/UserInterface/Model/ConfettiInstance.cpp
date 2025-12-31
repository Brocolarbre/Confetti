#include "ConfettiInstance.hpp"

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_particleSimulation(width, height),
    m_camera(glm::vec3(0.0f), glm::vec2(width, height)),
    m_cameraController(m_camera, window, glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f))
{
    m_cameraController.setSlideSpeed(0.1f);

    m_particleSimulation.addParticleEmitter(0, cft::ParticleEmitter{ 0, 0.0f, 4.0f, 20, 0.0f, cft::ParticleBoundaries{ glm::vec4(0.0f), glm::vec4(1.0f), glm::vec3(-10.0f), glm::vec3(10.0f), glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec2(0.01f), glm::vec2(1.0f), 2.0f, 5.0f } });
    m_particleSimulation.addParticleEmitter(1, cft::ParticleEmitter{ 1, 3.0f, 2.0f, 50, 0.0f, cft::ParticleBoundaries{ glm::vec4(1.0f), glm::vec4(1.0f), glm::vec3(-5.0f), glm::vec3(5.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.5f), glm::vec2(0.2f), glm::vec2(0.5f), 2.0f, 5.0f } });

    m_particleSimulation.addParticleEffect(0, cft::ParticleEffect{ 0.0f, 10.0f, { 0, 1 } });

    m_particleSimulation.addParticleSystem(0, cft::ParticleSystem{ { 0 } });
    m_particleSimulation.start();
}

cft::Renderer& ConfettiInstance::getRenderer()
{
    return m_particleSimulation.getRenderer();
}

void ConfettiInstance::update()
{
    m_cameraController.update();
    m_particleSimulation.update();
}

void ConfettiInstance::render()
{
    cft::View view{
        m_camera.getPosition(),
        m_camera.getRight(),
        m_camera.getUp(),
        m_camera.getForward(),
        m_camera.getViewMatrix(),
        m_camera.getViewFrustum().getProjectionMatrix()
    };

    m_particleSimulation.render(view);
}