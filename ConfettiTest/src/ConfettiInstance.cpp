#include "ConfettiInstance.hpp"

#include "JsonLoader.hpp"

#include <Confetti/Behavior/Force/AttractionForceField.hpp>
#include <Confetti/Behavior/Force/DirectionalForceField.hpp>
#include <Confetti/Behavior/Force/LinearDragForceField.hpp>
#include <Confetti/Behavior/Force/OrbitForceField.hpp>
#include <Confetti/Behavior/Force/RepulsionForceField.hpp>
#include <Confetti/Behavior/Force/TurbulenceForceField.hpp>
#include <Confetti/Behavior/Force/VortexForceField.hpp>
#include <Confetti/Behavior/Motion/CircleMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/FigureEightMotionBehavior.hpp>
#include <Confetti/Behavior/Motion/PathMotionBehavior.hpp>
#include <Confetti/Behavior/Visual/ColorShiftVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/DimOutVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/FadeInVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/FadeOutVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/FlickerVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/GrowInVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/PulseVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/ShrinkOutVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/SmoothColorShiftVisualBehavior.hpp>
#include <Confetti/Behavior/Visual/SquashStretchVisualBehavior.hpp>
#include <Confetti/Emission/AttributeGenerator/BinaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/InterpolatedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/EmissionPattern/ConstantRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/FixedBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/LinearRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/PeriodicBurstEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/RandomRateEmissionPattern.hpp>
#include <Confetti/Emission/EmissionPattern/SingleBurstEmissionPattern.hpp>
#include <Confetti/Emission/ParticleSpawner.hpp>
#include <Confetti/Emission/SpawnShape/CircleSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/DiskSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereVolumeSpawnShape.hpp>
#include <Confetti/Simulation/Link/LinkRule/ConnectionLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/DistanceLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/AgeSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/PhaseSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/VelocitySimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ColorSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/RandomParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/ChainParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/KNearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/NearestNeighborParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/OriginParticleLinker.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/TargetParticleLinker.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/SegmentRibbonGenerator.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/SpiralRibbonGenerator.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/WaveRibbonGenerator.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/PathRibbonGenerator.hpp>
#include <LineWeaver/Easing/EaseInQuadratic.hpp>
#include <LineWeaver/Interpolation/BSplineInterpolator.hpp>
#include <LineWeaver/Interpolation/CatmullRomInterpolator.hpp>

#include <glm/gtc/matrix_transform.hpp>

void ConfettiInstance::restartSimulation()
{
    cft::ParticleSpawner::resetNextId();
    m_randomNumberGenerator.reset();

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

    JsonLoader::load("res/systems/fireworks.json", m_assetRegistry, m_randomNumberGenerator);

    m_particleRenderer.loadBillboardRendererTextures(m_assetRegistry, { 0 }, 100, 100);
    m_particleRenderer.loadMeshRendererTextures(m_assetRegistry, { 1 });
    m_particleRenderer.loadMeshRendererMeshes(m_assetRegistry, { 0 });

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