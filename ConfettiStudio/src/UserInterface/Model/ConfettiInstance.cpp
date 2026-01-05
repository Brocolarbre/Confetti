#include "ConfettiInstance.hpp"

#include <ConfettiEngine/Particle/LinearForceField.hpp>

void ConfettiInstance::restartSimulation()
{
    m_particleSimulation.clear();
    m_particleSimulation.addParticleSystem(0);

    m_elapsedTimeChronometer.start();
    m_deltaTimeChronometer.start();
}

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_camera(glm::vec3(0.0f), glm::vec2(width, height)),
    m_cameraController(m_camera, window, glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f)),
    m_idGenerators(),
    m_assetDictionary(),
    m_userInterfaceState(),
    m_particleSimulation(),
    m_renderer(width, height),
    m_elapsedTimeChronometer(false),
    m_deltaTimeChronometer(false)
{
    m_cameraController.setSlideSpeed(0.1f);

    cft::ParticleRegistry& particleRegistry = m_particleSimulation.getParticleRegistry();

    // Builder ?
    particleRegistry.addForceField(0, std::make_unique<cft::LinearForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 10.0f));

    particleRegistry.addParticleEmitter(0, cft::ParticleEmitter{ 0, 0, 0.0f, 4.0f, 20, 0.0f, cft::ParticleBoundaries{ glm::vec4(0.0f), glm::vec4(1.0f), glm::vec3(-10.0f), glm::vec3(10.0f), glm::vec3(-1.0f), glm::vec3(1.0f), glm::vec2(0.01f), glm::vec2(1.0f), 2.0f, 5.0f } });
    particleRegistry.addParticleEmitter(1, cft::ParticleEmitter{ 1, 0, 3.0f, 2.0f, 50, 0.0f, cft::ParticleBoundaries{ glm::vec4(1.0f), glm::vec4(1.0f), glm::vec3(-5.0f), glm::vec3(5.0f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.5f), glm::vec2(0.2f), glm::vec2(0.5f), 2.0f, 5.0f } });
    particleRegistry.addParticleEffect(0, cft::ParticleEffect{ 0.0f, 10.0f, { 0, 1 } });
    particleRegistry.addParticleSystem(0, cft::ParticleSystem{ 0.0f, 10.0f, { 0 } });

    particleRegistry.addParticleSystemEntry(0, 0, {});
    particleRegistry.addParticleEffectEntry(0, 0, { 0, 0, {} });
    particleRegistry.addParticleEmitterEntry(0, 0, { 0, 0, {} });
    particleRegistry.addParticleEmitterEntry(1, 0, { 0, 0, { 0 } });

    restartSimulation();
}

Camera& ConfettiInstance::getCamera()
{
    return m_camera;
}

IdGenerators& ConfettiInstance::getIdGenerators()
{
    return m_idGenerators;
}

AssetDictionary& ConfettiInstance::getAssetDictionary()
{
    return m_assetDictionary;
}

UserInterfaceState& ConfettiInstance::getUserInterfaceState()
{
    return m_userInterfaceState;
}

cft::ParticleSimulation& ConfettiInstance::getParticleSimulation()
{
    return m_particleSimulation;
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

    m_particleSimulation.update(elapsedTime, deltaTime);
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

    m_renderer.render(view, m_particleSimulation.getParticlePools());
}