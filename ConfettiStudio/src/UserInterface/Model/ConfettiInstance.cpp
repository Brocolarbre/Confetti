#include "ConfettiInstance.hpp"

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_renderer(width, height),
    m_generator(),
    m_confetti(),
    m_particleSystem(m_confetti),
    m_elapsedTimeChronometer(),
    m_deltaTimeChronometer(),
    m_camera(glm::vec3(0.0f), glm::vec2(width, height)),
    m_cameraController(m_camera, window, glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f))
{
    m_cameraController.setSlideSpeed(0.1f);

    cft::ParticleBoundaries boundaries{ glm::vec4(0.0f), glm::vec4(1.0f), glm::vec3(-10.0f), glm::vec3(10.0f), glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec2(0.01f), glm::vec2(1.0f), 2.0f, 5.0f };
    cft::ParticleEmitter emitter{ 0, 0.0f, 4.0f, 20, 0.0f, boundaries };
    m_confetti.particleEmitters[0] = emitter;

    cft::ParticleEffect effect{ 4.0f, 5.0f, { 0 } };
    m_confetti.particleEffects[4] = effect;
    m_particleSystem.addParticleEffect(4);
}

cft::Renderer& ConfettiInstance::getRenderer()
{
    return m_renderer;
}

void ConfettiInstance::update()
{
    m_cameraController.update();

    float elapsedTime = static_cast<float>(m_elapsedTimeChronometer.getElapsedTime().seconds);
    float deltaTime = static_cast<float>(m_deltaTimeChronometer.getElapsedTime().seconds);
    m_deltaTimeChronometer.restart();

    m_particleSystem.update(elapsedTime, deltaTime);
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

    for(const auto& [type, pool] : m_particleSystem.getParticleEmitterPools())
        m_renderer.render(view, pool.getParticlePool());
}