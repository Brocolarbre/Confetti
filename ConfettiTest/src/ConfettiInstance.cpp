#include "ConfettiInstance.hpp"
#include "JsonLoader/JsonLoader.hpp"

void ConfettiInstance::restartSimulation()
{
    cft::ParticleSpawner::resetNextId();

    m_particleSimulation.clear();
    m_particleSimulation.addParticleEffect(0.0f, 0);

    m_elapsedTimeChronometer.start();
    m_deltaTimeChronometer.start();
}

void ConfettiInstance::updateSimulation(float elapsedTime, float deltaTime)
{
    float speedMultiplier = 1.0f;
    m_particleSimulation.update(elapsedTime * speedMultiplier, deltaTime * speedMultiplier);
}

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, unsigned int samples, dove::Window& window) :
    m_renderContext(width, height),
    m_camera(width, height),
    m_particleRenderer(width, height, samples),
    m_assetRegistry(),
    m_particleSimulation(m_assetRegistry),
    m_elapsedTimeChronometer(false),
    m_deltaTimeChronometer(false),
    m_timeStep(1.0 / 60.0),
    m_timeAccumulator(0.0),
    m_width(width),
    m_height(height)
{
    window.addEventHandler(*this);

    JsonLoader::load("res/systems/fireworks.json", m_particleSimulation, m_particleRenderer, m_assetRegistry);

    restartSimulation();
}

void ConfettiInstance::onKeyPressed(dove::KeyEvent keyEvent)
{
    if (keyEvent.key == dove::Keyboard::Key::R)
        restartSimulation();
}

void ConfettiInstance::onWindowResized(unsigned int width, unsigned int height)
{
    m_width = width;
    m_height = height;

    m_camera = Camera(width, height);
    m_renderContext.resize(width, height);
    m_particleRenderer.resize(width, height);
}

void ConfettiInstance::update()
{
    m_elapsedTime = static_cast<float>(m_elapsedTimeChronometer.getElapsedTime().seconds);
    float deltaTime = static_cast<float>(m_deltaTimeChronometer.getElapsedTime().seconds);
    m_deltaTimeChronometer.restart();

    m_timeAccumulator += deltaTime;
    while (m_timeAccumulator > m_timeStep)
    {
        updateSimulation(static_cast<float>(m_elapsedTime), static_cast<float>(m_timeStep));
        m_particleRenderer.update(m_particleSimulation, m_assetRegistry, m_camera.getView());
        m_timeAccumulator -= m_timeStep;
    }
}

void ConfettiInstance::render()
{
    m_particleRenderer.render(m_camera.getView(), static_cast<float>(m_elapsedTime), m_particleSimulation.getParticlePools(), m_particleSimulation.getParticleRegistry(), m_assetRegistry);
    m_renderContext.render(m_particleRenderer.getOutputTextureId());
}