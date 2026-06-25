#include "ConfettiInstance.hpp"

#include <Confetti/ForceField/AttractionForceField.hpp>
#include <Confetti/ForceField/DirectionalForceField.hpp>
#include <Confetti/ForceField/DragForceField.hpp>
#include <Confetti/ForceField/TurbulenceForceField.hpp>
#include <Confetti/ForceField/RepulsionForceField.hpp>
#include <Confetti/ForceField/VortexForceField.hpp>
#include <Confetti/ParticleBehavior/ColorShiftParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/FadeInParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/FadeOutParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/FlickerParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/GrowInParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/PulseParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/ShrinkOutParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/SquashStretchParticleBehavior.hpp>
#include <Confetti/ParticleBehavior/SmoothColorShiftParticleBehavior.hpp>
#include <Confetti/MotionBehavior/RandomMotionBehavior.hpp>
#include <Confetti/MotionBehavior/VibrationMotionBehavior.hpp>
#include <Confetti/ParticleSpawner/ParticleSpawner.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Generic/SmoothRandomSetAttributeGenerator.hpp>
#include <Confetti/ParticleSpawner/AttributeGenerator/Specific/NormalVelocityGenerator.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/CircleSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/ConeSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/ConeVolumeSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/CylinderSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/CylinderVolumeSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/DiskSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/SphereSpawnShape.hpp>
#include <Confetti/ParticleSpawner/SpawnShape/SphereVolumeSpawnShape.hpp>
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

void ConfettiInstance::updateSimulation(float elapsedTime, float deltaTime)
{
    m_particleSimulation.update(elapsedTime, deltaTime);
}

ConfettiInstance::ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window) :
    m_renderContext(width, height),
    m_particleRenderer(width, height),
    m_assetRegistry(),
    m_randomNumberGenerator(),
    m_particleSimulation(m_assetRegistry, m_randomNumberGenerator),
    m_elapsedTimeChronometer(false),
    m_deltaTimeChronometer(false),
    m_timeStep(1.0 / 60.0),
    m_timeAccumulator(0.0),
    m_width(width),
    m_height(height)
{
    window.addEventHandler(*this);

    //cft::Image bubbleImage;
    //bubbleImage.loadFromFile("res/images/fire.png");

    cft::Image rockImage;
    rockImage.loadFromFile("res/images/rock_2.jpg");

    cft::Image circleImage;
    circleImage.loadFromFile("res/images/circle.png");

    //m_assetRegistry.addImage(0, std::move(bubbleImage));
    m_assetRegistry.addImage(1, std::move(rockImage));
    m_assetRegistry.addImage(2, std::move(circleImage));

    //m_assetRegistry.addSpriteSheet(0, cft::SpriteSheet{ 0, 64, 8, 512, 512, 18.0f });
    m_assetRegistry.addSpriteSheet(1, cft::SpriteSheet{ 2, 1, 1, 600, 600, 0.0f });

    cft::Model pebbleModel;
    pebbleModel.loadFromFile("res/models/pebble.obj");

    m_assetRegistry.addModel(0, std::move(pebbleModel));

    m_particleRenderer.loadBillboardRendererTextures(m_assetRegistry, { 2 }, 600, 600);
    m_particleRenderer.loadMeshRendererTextures(m_assetRegistry, { 1 });
    m_particleRenderer.loadMeshRendererMeshes(m_assetRegistry, { 0 });

    m_assetRegistry.addForceField(0, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 9.81f));
    m_assetRegistry.addForceField(1, std::make_unique<cft::AttractionForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, cft::Falloff::Constant), 5.0f));
    m_assetRegistry.addForceField(2, std::make_unique<cft::RepulsionForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, cft::Falloff::Constant), 1.0f));
    m_assetRegistry.addForceField(3, std::make_unique<cft::DragForceField>(0.01f));
    m_assetRegistry.addForceField(4, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, 1.0f, 0.0f), 8.0f));
    m_assetRegistry.addForceField(5, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 5.0f));

    m_assetRegistry.addParticleBehavior(1, std::make_unique<cft::FadeOutParticleBehavior>(0.8f));
    m_assetRegistry.addParticleBehavior(2, std::make_unique<cft::ShrinkOutParticleBehavior>(0.8f));
    m_assetRegistry.addParticleBehavior(3, std::make_unique<cft::PulseParticleBehavior>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f), 5.0f));
    m_assetRegistry.addParticleBehavior(4, std::make_unique<cft::FadeInParticleBehavior>(0.1f));
    m_assetRegistry.addParticleBehavior(5, std::make_unique<cft::GrowInParticleBehavior>(0.2f));
    m_assetRegistry.addParticleBehavior(6, std::make_unique<cft::SquashStretchParticleBehavior>(glm::vec2(0.35f), 8.0f));
    m_assetRegistry.addParticleBehavior(7, std::make_unique<cft::ColorShiftParticleBehavior>(std::vector<glm::vec4>{ glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) }, 1.5f, true));
    m_assetRegistry.addParticleBehavior(8, std::make_unique<cft::SmoothColorShiftParticleBehavior>(std::vector<glm::vec4>{ glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) }, 1.5f, true));
    m_assetRegistry.addParticleBehavior(9, std::make_unique<cft::FlickerParticleBehavior>(0.8f, 2.0f, 20.0f));

    m_assetRegistry.addMotionBehavior(0, std::make_unique<cft::RandomMotionBehavior>());
    m_assetRegistry.addMotionBehavior(1, std::make_unique<cft::VibrationMotionBehavior>());

    float strength = 3.0f;

    m_assetRegistry.addParticleSpawner(0, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-6.0f, -12.0f, -6.0f), glm::vec3(6.0f, -10.5f, 6.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Velocity>>(glm::vec3(-2.0f, 0.8f, -2.0f), glm::vec3(2.0f, 1.5f, 2.0f), m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.5f), glm::vec3(0.6f), m_randomNumberGenerator),
        std::make_unique<cft::SmoothRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength* glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(0.0f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(1.3f),
        1.3f
    ));

    m_assetRegistry.addParticleSpawner(1, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-0.25f), glm::vec3(0.25f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Velocity>>(glm::vec3(-2.0f), glm::vec3(2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.1f), glm::vec3(0.2f), m_randomNumberGenerator),
        std::make_unique<cft::SmoothRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength* glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 1.0f, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(0.8f),
        0.8f
    ));

    m_assetRegistry.addParticleSpawner(2, std::make_unique<cft::ParticleSpawner>(
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Position>>(glm::vec3(0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-0.3f), glm::vec3(0.3f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Velocity>>(glm::vec3(-2.0f), glm::vec3(2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.1f), glm::vec3(0.2f), m_randomNumberGenerator),
        std::make_unique<cft::SmoothRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength* glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 10.0f, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Lifetime>>(1.0f, 1.2f, m_randomNumberGenerator),
        1.2f
    ));

    m_assetRegistry.addParticleSpawner(3, std::make_unique<cft::ParticleSpawner>(
        //std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-10.0f), glm::vec3(30.0f) , m_randomNumberGenerator),
        //std::make_unique<cft::CylinderVolumeSpawnShape>(6.0f, 2.0f, glm::vec3(0.0f, 1.0f, 0.0f)),
        std::make_unique<cft::SphereVolumeSpawnShape>(1.0f),
        //std::make_unique<cft::RandomAttributeGenerator<cft::Velocity>>(glm::vec3(-0.8f, -0.4f, -0.1f), glm::vec3(0.8f, 0.4f, 0.1f), m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Velocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::NormalVelocityGenerator>(6.0f),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 2.0f), m_randomNumberGenerator),
        //std::make_unique<cft::NormalBurstVelocityGenerator>(1.0f, 10.0f, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.4f), glm::vec3(0.8f), m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Scale>>(glm::vec3(0.6f)),
        //std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        //std::make_unique<cft::SmoothRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        //std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(0.635f, 0.376f, 0.941f, 1.0f), strength * glm::vec4(0.751f, 0.488f, 0.9f, 1.0f), strength * glm::vec4(0.798f, 0.696f, 0.963f, 1.0f), strength * glm::vec4(0.722f, 0.816f, 0.922f, 0.1f), strength * glm::vec4(0.725f, 0.98f, 0.973f, 0.1f) }, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Color>>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        //std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 5.0f, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 15.0f, m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(0.0f),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(0.0f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(0.4f),
        4.0f
    ));

    m_assetRegistry.addSpawnPolicy(0, std::make_unique<cft::FixedSpawnPolicy>(3, 0, 1));
    m_assetRegistry.addSpawnPolicy(1, std::make_unique<cft::FixedSpawnPolicy>(15, 0, 1));
    m_assetRegistry.addSpawnPolicy(2, std::make_unique<cft::FixedSpawnPolicy>(8, 0, 1));

    m_assetRegistry.addParticleEmitter(0, cft::ParticleEmitter{ 0, 0, 0, cft::SpawnTrigger{ 1, std::nullopt, cft::ParticleEmitterDescriptor{ 2, cft::TimeRange{ 0.0f, 1.0f }, cft::Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {} }, cft::PeriodicSpawnTrigger{ cft::ParticleEmitterDescriptor{ 1, cft::TimeRange{ 0.0f, 1.0f }, cft::Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {} }, 0.1f } }, cft::RenderDescriptor{cft::RenderType::Mesh, cft::MeshRenderDescriptor{ 0, 1 } }, { 4 }, {}, {} });
    m_assetRegistry.addParticleEmitter(1, cft::ParticleEmitter{ 1, 1, 1, std::nullopt, cft::RenderDescriptor{ cft::RenderType::Billboard, cft::BillboardRenderDescriptor{ 1 }}, { 0 }, {}, { 2, 4 } });
    m_assetRegistry.addParticleEmitter(2, cft::ParticleEmitter{ 2, 2, 2, cft::SpawnTrigger{ 4, std::nullopt, cft::ParticleEmitterDescriptor{ 2, cft::TimeRange{ 0.0f, 1.0f }, cft::Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {} }, std::nullopt }, cft::RenderDescriptor{ cft::RenderType::Billboard, cft::BillboardRenderDescriptor{ 1 } }, { 5 }, {}, { 9 } });
    
    m_assetRegistry.addParticleEffect(0, cft::ParticleEffect{ { cft::ParticleEmitterDescriptor{ 0, cft::TimeRange{ 0.0f, 1.0f }, cft::Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {}}}});

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
        m_particleRenderer.update(m_particleSimulation.getParticlePools(), m_particleSimulation.getParticleRegistry(), m_assetRegistry);
        m_timeAccumulator -= m_timeStep;
    }
}

void ConfettiInstance::render()
{
    glm::vec3 position(0.0f, 0.0f, 40.0f);
    glm::vec3 right(0.0f, 0.0f, 0.0f);
    glm::vec3 up(0.0f, 0.0f, 0.0f);
    glm::vec3 forward(0.0f, 0.0f, 0.0f);
    glm::mat4 viewMatrix(glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::mat4 projectionMatrix(glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height), 0.01f, 1000.0f));

    cft::View view{
        position,
        right,
        up,
        forward,
        viewMatrix,
        projectionMatrix
    };

    m_particleRenderer.render(view, static_cast<float>(m_elapsedTime), m_particleSimulation.getParticlePools(), m_particleSimulation.getParticleRegistry(), m_assetRegistry);
    m_renderContext.render(m_particleRenderer.getOutputTextureId());
}