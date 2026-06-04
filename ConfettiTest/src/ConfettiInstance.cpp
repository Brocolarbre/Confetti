#include "ConfettiInstance.hpp"

#include <Confetti/ForceField/AttractionForceField.hpp>
#include <Confetti/ForceField/DirectionalForceField.hpp>
#include <Confetti/ForceField/DragForceField.hpp>
#include <Confetti/ForceField/JitterForceField.hpp>
#include <Confetti/ForceField/RepulsionForceField.hpp>
#include <Confetti/ForceField/VortexForceField.hpp>
#include <Confetti/ParticleBehavior/FadeOutParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/FlickerParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/ShrinkOutParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/RandomParticleBehavior.hpp>
#include <Confetti/MotionBehavior/RandomMotionBehavior.hpp>
#include <Confetti/MotionBehavior/VibrationMotionBehavior.hpp>
#include <Confetti/ParticleSpawner/ParticleSpawner.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Velocity/NormalBurstVelocityGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Velocity/NormalVelocityGenerator.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/SphereSpawnShape.hpp>
#include <Confetti/SpawnPolicy/ConstantSpawnPolicy.hpp>
#include <Confetti/SpawnPolicy/FixedSpawnPolicy.hpp>

#include <glm/gtc/matrix_transform.hpp>

void ConfettiInstance::restartSimulation()
{
    m_particleSimulation.clear();
    m_particleSimulation.addParticleEffect(0.0f, 0);

    m_elapsedTimeChronometer.start();
    m_deltaTimeChronometer.start();
}

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_renderContext(width, height),
    m_renderer(width, height),
    m_assetRegistry(),
    m_randomNumberGenerator(),
    m_particleSimulation(m_assetRegistry, m_randomNumberGenerator),
    m_elapsedTimeChronometer(false),
    m_deltaTimeChronometer(false)
{
    window.addEventHandler(*this);

    m_assetRegistry.addForceField(0, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 10.0f));
    m_assetRegistry.addForceField(1, std::make_unique<cft::AttractionForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, cft::Falloff::Constant), 5.0f));
    m_assetRegistry.addForceField(2, std::make_unique<cft::RepulsionForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, cft::Falloff::Constant), 1.0f));
    m_assetRegistry.addForceField(3, std::make_unique<cft::DragForceField>(0.01f));

    m_assetRegistry.addParticleBehavior(0, std::make_unique<cft::RandomParticleBehavior>(0.1f, m_randomNumberGenerator));
    m_assetRegistry.addParticleBehavior(1, std::make_unique<cft::FadeOutParticleBehavior>(0.8f));
    m_assetRegistry.addParticleBehavior(2, std::make_unique<cft::ShrinkOutParticleBehavior>(0.7f));
    m_assetRegistry.addParticleBehavior(3, std::make_unique<cft::FlickerParticleBehavior>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f), 5.0f));

    m_assetRegistry.addMotionBehavior(0, std::make_unique<cft::RandomMotionBehavior>());
    m_assetRegistry.addMotionBehavior(1, std::make_unique<cft::VibrationMotionBehavior>());

    m_assetRegistry.addParticleSpawner(0, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-10.0f), glm::vec3(10.0f), m_randomNumberGenerator),
        //std::make_unique<cft::SphereSpawnShape>(1.0f),
        //std::make_unique<cft::RandomAttributeGenerator<cft::Velocity>>(glm::vec3(-2.0f), glm::vec3(2.0f), m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Velocity>>(glm::vec3(0.0f)),
        //std::make_unique<cft::NormalVelocityGenerator>(1.0f),
        //std::make_unique<cft::NormalBurstVelocityGenerator>(1.0f, 10.0f, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec2(0.1f), glm::vec2(0.2f), m_randomNumberGenerator),
        //std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ glm::vec4(0.635f, 0.376f, 0.941f, 1.0f), glm::vec4(0.751f, 0.488f, 0.9f, 1.0f), glm::vec4(0.798f, 0.696f, 0.963f, 1.0f), glm::vec4(0.722f, 0.816f, 0.922f, 0.1f), glm::vec4(0.725f, 0.98f, 0.973f, 0.1f) }, m_randomNumberGenerator),
        //std::make_unique<cft::RandomAttributeGenerator<cft::Lifetime>>(0.4f, 0.8f, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(2.0f),
        2.0f
    ));

    m_assetRegistry.addSpawnPolicy(0, std::make_unique<cft::ConstantSpawnPolicy>(50, 10));
    m_assetRegistry.addSpawnPolicy(1, std::make_unique<cft::FixedSpawnPolicy>(50, 350, 10));

    m_assetRegistry.addParticleEmitter(0, cft::ParticleEmitter{ 0, 0, 1, { }, { }, { 3 } });
    
    m_assetRegistry.addParticleEffect(0, cft::ParticleEffect{ { cft::ParticleEmitterDescriptor{ 0, cft::TimeRange{ 0.0f, 10.0f }, cft::Transform{ glm::vec3(0.0f), glm::vec3(0.0f) }, { }, { /*0*/ } } } });

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
    glm::vec3 position(0.0f, 0.0f, 20.0f);
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