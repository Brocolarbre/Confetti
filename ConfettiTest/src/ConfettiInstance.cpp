#include "ConfettiInstance.hpp"

#include <Confetti/ForceField/LinearForceField.hpp>
#include <Confetti/ForceField/AttractionForceField.hpp>
#include <Confetti/ForceField/RepulsionForceField.hpp>
#include <Confetti/ForceField/AttenuationForceField.hpp>

#include <glm/gtc/matrix_transform.hpp>

void ConfettiInstance::restartSimulation()
{
    m_particleSimulation.clear();
    m_particleSimulation.addParticleSystem(0);

    m_elapsedTimeChronometer.start();
    m_deltaTimeChronometer.start();
}

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_renderContext(width, height),
    m_renderer(width, height),
    m_particleSimulation(),
    m_elapsedTimeChronometer(false),
    m_deltaTimeChronometer(false)
{
    window.addEventHandler(*this);

    cft::ParticleRegistry& particleRegistry = m_particleSimulation.getParticleRegistry();

    particleRegistry.addForceField(0, std::make_unique<cft::LinearForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 10.0f));
    particleRegistry.addForceField(1, std::make_unique<cft::AttractionForceField>(glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, 10.0f));
    particleRegistry.addForceField(2, std::make_unique<cft::RepulsionForceField>(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, 1.0f));
    particleRegistry.addForceField(3, std::make_unique<cft::AttenuationForceField>(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, 0.2f));

    particleRegistry.addParticleEmitter(0, cft::ParticleEmitter{ 0, 0, 0.0f, 4.0f, 20, 0.0f, cft::ParticleBoundaries{ glm::vec4(0.0f), glm::vec4(1.0f), glm::vec3(-10.0f), glm::vec3(10.0f), glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec2(0.01f), glm::vec2(1.0f), 2.0f, 5.0f } });
    particleRegistry.addParticleEmitter(1, cft::ParticleEmitter{ 1, 0, 3.0f, 2.0f, 50, 0.0f, cft::ParticleBoundaries{ glm::vec4(1.0f), glm::vec4(1.0f), glm::vec3(-5.0f), glm::vec3(5.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.5f), glm::vec2(0.2f), glm::vec2(0.5f), 2.0f, 5.0f } });
    particleRegistry.addParticleEmitter(2, cft::ParticleEmitter{ 2, 0, 0.0f, 5.0f, 80, 0.0f, cft::ParticleBoundaries{ glm::vec4(0.6f, 0.4f, 0.8f, 1.0f), glm::vec4(0.6f, 0.4f, 0.8f, 1.0f), glm::vec3(-10.0f), glm::vec3(10.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.1f), glm::vec2(0.3f), 4.0f, 6.0f } });
    particleRegistry.addParticleEmitter(3, cft::ParticleEmitter{ 3, 0, 0.0f, 0.1f, 3000, 0.0f, cft::ParticleBoundaries{ glm::vec4(0.8f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f, 0.5f, 0.0f, 1.0f), glm::vec3(-0.01f), glm::vec3(0.01f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec2(0.1f), glm::vec2(0.1f), 6.0f, 9.0f } });
    particleRegistry.addParticleEffect(0, cft::ParticleEffect{ 0.0f, 10.0f, { 0, 1 } });
    particleRegistry.addParticleEffect(1, cft::ParticleEffect{ 0.0f, 10.0f, { 2 } });
    particleRegistry.addParticleEffect(2, cft::ParticleEffect{ 0.0f, 10.0f, { 3 } });
    particleRegistry.addParticleSystem(0, cft::ParticleSystem{ 0.0f, 10.0f, { 2 } });

    particleRegistry.addParticleSystemEntry(0, 0, {});
    particleRegistry.addParticleEffectEntry(0, 0, { 0, 0, {} });
    particleRegistry.addParticleEmitterEntry(0, 0, { 0, 0, {} });
    particleRegistry.addParticleEmitterEntry(1, 0, { 0, 0, { 0 } });
    particleRegistry.addParticleEmitterEntry(2, 0, { 0, 0, { 1, 3 } });
    particleRegistry.addParticleEmitterEntry(3, 0, { 0, 0, { 2 } });

    restartSimulation();
}

void ConfettiInstance::onKeyPressed(dove::KeyEvent keyEvent)
{
    if (keyEvent.key == dove::Keyboard::Key::R)
        restartSimulation();
}

void ConfettiInstance::onWindowResized(unsigned int width, unsigned int height)
{
    m_renderContext.resize(width, height);
    m_renderer.resize(width, height);
}

void ConfettiInstance::update()
{
    float elapsedTime = static_cast<float>(m_elapsedTimeChronometer.getElapsedTime().seconds);
    float deltaTime = static_cast<float>(m_deltaTimeChronometer.getElapsedTime().seconds);
    m_deltaTimeChronometer.restart();

    m_particleSimulation.update(elapsedTime, deltaTime);
}

void ConfettiInstance::render()
{
    glm::vec3 position(0.0f, 5.0f, 10.0f);
    glm::vec3 right(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 0.0f, 0.0f);
    glm::vec3 forward(0.0f, 0.0f, 0.0f);
    glm::mat4 viewMatrix(glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::mat4 projectionMatrix(glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.01f, 1000.0f));

    cft::View view{
        position,
        right,
        up,
        forward,
        viewMatrix,
        projectionMatrix
    };

    m_renderer.render(view, m_particleSimulation.getParticlePools());
    m_renderContext.render(m_renderer.getOutputTextureId());
}