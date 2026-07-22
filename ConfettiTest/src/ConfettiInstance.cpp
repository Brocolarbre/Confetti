#include "ConfettiInstance.hpp"

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

    m_particleSimulation.clear();
    //m_particleSimulation.addParticleEffect(0.0f, 0);
    //m_particleSimulation.addParticleEffect(0.0f, 2);
    m_particleSimulation.addParticleEffect(0.0f, 20);

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

    //cft::Image bubbleImage;
    //bubbleImage.loadFromFile("res/images/fire.png");

    cft::Image rockImage;
    rockImage.loadFromFile("res/images/rock_2.jpg");

    cft::Image circleImage;
    circleImage.loadFromFile("res/images/circle.png");

    cft::Image diamondImage;
    diamondImage.loadFromFile("res/images/diamond.png");

    cft::Image roundedDiamondImage;
    roundedDiamondImage.loadFromFile("res/images/rounded_diamond.png");

    cft::Image triangleImage;
    triangleImage.loadFromFile("res/images/triangle.png");

    cft::Image stripesImage;
    stripesImage.loadFromFile("res/images/stripes.png");

    //m_assetRegistry.addImage(0, std::move(bubbleImage));
    m_assetRegistry.addImage(1, std::move(rockImage));
    m_assetRegistry.addImage(2, std::move(circleImage));
    m_assetRegistry.addImage(3, std::move(diamondImage));
    m_assetRegistry.addImage(4, std::move(triangleImage));
    m_assetRegistry.addImage(5, std::move(stripesImage));
    m_assetRegistry.addImage(20, std::move(roundedDiamondImage));

    //m_assetRegistry.addSpriteSheet(0, cft::SpriteSheet{ 0, 64, 8, 512, 512, 18.0f });
    //m_assetRegistry.addSpriteSheet(1, cft::SpriteSheet{ 2, 1, 1, 600, 600, 0.0f });
    //m_assetRegistry.addSpriteSheet(2, cft::SpriteSheet{ 3, 1, 1, 626, 626, 0.0f });
    m_assetRegistry.addSpriteSheetDescriptor(20, cft::SpriteSheetDescriptor{ 20, 1, 1, 200, 200, 0.0f });

    cft::Model pebbleModel;
    pebbleModel.loadFromFile("res/models/pebble.obj");

    m_assetRegistry.addModel(0, std::move(pebbleModel));

    //m_particleRenderer.loadBillboardRendererTextures(m_assetRegistry, { 2 }, 600, 600);
    m_particleRenderer.loadBillboardRendererTextures(m_assetRegistry, { 20 }, 200, 200);
    //m_particleRenderer.loadBillboardRendererTextures(m_assetRegistry, { 3 }, 626, 626);
    //m_particleRenderer.loadMeshRendererTextures(m_assetRegistry, { 1 });
    m_particleRenderer.loadMeshRendererMeshes(m_assetRegistry, { 0 });
    m_particleRenderer.loadTrailRendererTextures(m_assetRegistry, { 5 }, 880, 880);

    m_assetRegistry.addForceField(0, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 9.81f));
    m_assetRegistry.addForceField(1, std::make_unique<cft::AttractionForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, cft::Falloff::Constant), 5.0f));
    m_assetRegistry.addForceField(2, std::make_unique<cft::RepulsionForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f, cft::Falloff::Constant), 1.0f));
    m_assetRegistry.addForceField(3, std::make_unique<cft::LinearDragForceField>(0.01f));
    m_assetRegistry.addForceField(4, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, 1.0f, 0.0f), 8.0f));
    m_assetRegistry.addForceField(5, std::make_unique<cft::DirectionalForceField>(glm::vec3(0.0f, -1.0f, 0.0f), 5.0f));
    //m_assetRegistry.addForceField(6, std::make_unique<cft::OrbitForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, cft::Falloff::Constant), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, 10.0f, 0.5f));
    m_assetRegistry.addForceField(6, std::make_unique<cft::VortexForceField>(cft::SpatialInfluence(glm::vec3(0.0f, 0.0f, 0.0f), 100.0f, cft::Falloff::Constant), glm::vec3(0.0f, 1.0f, 0.0f), 20.0f, 3.0f));
    m_assetRegistry.addForceField(7, std::make_unique<cft::TurbulenceForceField>(10.0f, m_randomNumberGenerator));

    m_assetRegistry.addVisualBehavior(1, std::make_unique<cft::FadeOutVisualBehavior>(cft::ParticleTime::absolute(0.8f)));
    m_assetRegistry.addVisualBehavior(2, std::make_unique<cft::ShrinkOutVisualBehavior>(cft::ParticleTime::absolute(0.8f)));
    m_assetRegistry.addVisualBehavior(3, std::make_unique<cft::PulseVisualBehavior>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f), 5.0f));
    m_assetRegistry.addVisualBehavior(4, std::make_unique<cft::FadeInVisualBehavior>(cft::ParticleTime::absolute(0.1f)));
    m_assetRegistry.addVisualBehavior(5, std::make_unique<cft::GrowInVisualBehavior>(cft::ParticleTime::absolute(0.2f)));
    m_assetRegistry.addVisualBehavior(6, std::make_unique<cft::SquashStretchVisualBehavior>(glm::vec2(0.35f), 8.0f));
    m_assetRegistry.addVisualBehavior(7, std::make_unique<cft::ColorShiftVisualBehavior>(std::vector<glm::vec4>{ glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) }, 1.5f, true));
    m_assetRegistry.addVisualBehavior(8, std::make_unique<cft::SmoothColorShiftVisualBehavior>(std::vector<glm::vec4>{ glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) }, 1.5f, true));
    m_assetRegistry.addVisualBehavior(9, std::make_unique<cft::FlickerVisualBehavior>(0.1f, 4.0f, 10.0f));

    m_assetRegistry.addMotionBehavior(0, std::make_unique<cft::CircleMotionBehavior>(glm::vec3(0.0f, 0.0f, 1.0f), 2.0f, 4.0f));
    m_assetRegistry.addMotionBehavior(1, std::make_unique<cft::FigureEightMotionBehavior>(glm::vec3(0.0f, 0.0f, 1.0f), 5.0f, 2.0f));
    m_assetRegistry.addMotionBehavior(2, std::make_unique<cft::PathMotionBehavior>(
        lw::Curve{ lw::Point(-10.0f, 0.0f, 0.0f), lw::Point(10.0f, 0.0f, 0.0f), lw::Point(0.0f, 10.0f, 0.0f), lw::Point(0.0f, -10.0f, 0.0f) }
        /*lw::Curve{
            lw::Point(-8.0f,  0.0f,  0.0f),
            lw::Point(-5.0f,  4.0f,  2.0f),
            lw::Point(-2.0f, -3.0f, -1.0f),
            lw::Point(1.0f,  7.0f,  5.0f),
            lw::Point(4.0f, -6.0f, -3.0f),
            lw::Point(7.0f,  2.0f,  4.0f),
            lw::Point(10.0f, -1.0f,  0.0f),
            lw::Point(6.0f,  8.0f, -2.0f),
            lw::Point(0.0f,  4.0f,  6.0f),
            lw::Point(-6.0f, -4.0f,  3.0f),
            lw::Point(-8.0f,  0.0f,  0.0f)
        }*/, std::make_unique<lw::BSplineInterpolator>(std::make_unique<lw::CatmullRomInterpolator>()), nullptr, 5.0f));

    float strength = 3.0f;

    m_assetRegistry.addParticleSpawner(0, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-6.0f, -12.0f, -6.0f), glm::vec3(6.0f, -10.5f, 6.0f), m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.5f), glm::vec3(0.6f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(glm::vec3(-1.0f, 0.8f, -1.0f), glm::vec3(1.0f, 1.5f, 1.0f), m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(0.0f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(1.3f),
        1.3f
    ));

    m_assetRegistry.addParticleSpawner(1, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-0.25f), glm::vec3(0.25f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.1f), glm::vec3(0.2f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(glm::vec3(-2.0f), glm::vec3(2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 1.0f, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(0.8f),
        0.8f
    ));

    m_assetRegistry.addParticleSpawner(2, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength* glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Position>>(glm::vec3(0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-0.3f), glm::vec3(0.3f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(/*0.1f*/0.3f), glm::vec3(/*0.3f*/0.5f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(glm::vec3(-2.0f), glm::vec3(2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 2.0f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 10.0f, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Lifetime>>(1.0f, 1.2f, m_randomNumberGenerator),
        1.2f
    ));

    m_assetRegistry.addParticleSpawner(3, std::make_unique<cft::ParticleSpawner>(
        //std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        //std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        //std::make_unique<cft::RandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(0.635f, 0.376f, 0.941f, 1.0f), strength * glm::vec4(0.751f, 0.488f, 0.9f, 1.0f), strength * glm::vec4(0.798f, 0.696f, 0.963f, 1.0f), strength * glm::vec4(0.722f, 0.816f, 0.922f, 0.1f), strength * glm::vec4(0.725f, 0.98f, 0.973f, 0.1f) }, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Color>>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
        //std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-10.0f), glm::vec3(30.0f) , m_randomNumberGenerator),
        //std::make_unique<cft::CylinderVolumeSpawnShape>(6.0f, 2.0f, glm::vec3(0.0f, 1.0f, 0.0f)),
        std::make_unique<cft::SphereVolumeSpawnShape>(1.0f),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Rotation>>(glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, 1.0f)), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.4f), glm::vec3(0.8f), m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Scale>>(glm::vec3(0.6f)),
        //std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(glm::vec3(-0.8f, -0.4f, -0.1f), glm::vec3(0.8f, 0.4f, 0.1f), m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::LinearVelocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::NormalLinearVelocityGenerator>(6.0f),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 2.0f), m_randomNumberGenerator),
        //std::make_unique<cft::NormalBurstVelocityGenerator>(1.0f, 10.0f, m_randomNumberGenerator),
        //std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 5.0f, m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 15.0f, m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(0.0f),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(0.0f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(0.4f),
        4.0f
    ));

    m_assetRegistry.addEmissionPattern(0, std::make_unique<cft::SingleBurstEmissionPattern>(1));
    m_assetRegistry.addEmissionPattern(1, std::make_unique<cft::SingleBurstEmissionPattern>(15));
    m_assetRegistry.addEmissionPattern(2, std::make_unique<cft::SingleBurstEmissionPattern>(8));

    std::vector<std::unique_ptr<cft::LinkRule>> connectionRules;
    connectionRules.push_back(std::make_unique<cft::ConnectionLinkRule>(3));
    connectionRules.push_back(std::make_unique<cft::DistanceLinkRule>(0.0f, 8.0f));
    //connectionRules.push_back(std::make_unique<cft::PhaseSimilarityLinkRule>(3.0f));

    std::vector<std::unique_ptr<cft::LinkRule>> validationRules;
    validationRules.push_back(std::make_unique<cft::DistanceLinkRule>(0.0f, 9.0f));

    //m_assetRegistry.addParticleLinker(0, std::make_unique<cft::RandomParticleLinker>(std::move(connectionRules), std::move(validationRules), 7, m_randomNumberGenerator));
    m_assetRegistry.addParticleLinker(0, std::make_unique<cft::NearestNeighborParticleLinker>(std::move(connectionRules), std::move(validationRules)));
    //m_assetRegistry.addParticleLinker(0, std::make_unique<cft::ChainParticleLinker>(std::move(connectionRules), std::move(validationRules)));
    //m_assetRegistry.addParticleLinker(0, std::make_unique<cft::TargetParticleLinker>(std::move(connectionRules), std::move(validationRules), 0));
    //m_assetRegistry.addParticleLinker(0, std::make_unique<cft::OriginParticleLinker>(std::move(connectionRules), std::move(validationRules), glm::vec3(0.0f)));

    m_assetRegistry.addRibbonGenerator(0, std::make_unique<cft::SegmentRibbonGenerator>());
    m_assetRegistry.addRibbonGenerator(1, std::make_unique<cft::SpiralRibbonGenerator>(100.0f, 0.2f, 2.0f));
    m_assetRegistry.addRibbonGenerator(2, std::make_unique<cft::WaveRibbonGenerator>(100.0f, 0.2f, 2.0f));
    m_assetRegistry.addRibbonGenerator(3, std::make_unique<cft::PathRibbonGenerator>(lw::Curve{
            lw::Point(-8.0f,  0.0f,  0.0f),
            lw::Point(-5.5f,  2.5f,  0.5f),
            lw::Point(-2.5f, -2.5f, -0.5f),
            lw::Point(1.0f,  2.0f,  0.8f),
            lw::Point(4.0f, -1.5f,  0.0f),
            lw::Point(7.0f,  0.0f,  0.0f)
        }, std::make_unique<lw::BSplineInterpolator>(std::make_unique<lw::CatmullRomInterpolator>()), nullptr));

    m_assetRegistry.addParticleEmitterDescriptor(0, cft::ParticleEmitterDescriptor{ 0, 0, 0, std::nullopt, std::nullopt, cft::SpawnTriggerDescriptor{ 1, std::nullopt, cft::ParticleEmitterSpawnContext{ 2, cft::TimeRange{ 0.0f, 1.0f }, cft::MotionState{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {} }, cft::PeriodicSpawnTriggerContext{ cft::ParticleEmitterSpawnContext{ 1, cft::TimeRange{ 0.0f, 1.0f }, cft::MotionState{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {} }, 0.1f } }, cft::RenderConfiguration{cft::RenderType::Mesh, cft::MeshRenderConfiguration{ 0, 1 } }, { 4 }, {}, {} });
    m_assetRegistry.addParticleEmitterDescriptor(1, cft::ParticleEmitterDescriptor{ 1, 1, 1, std::nullopt, std::nullopt, std::nullopt, cft::RenderConfiguration{ cft::RenderType::Billboard, cft::BillboardRenderConfiguration{ 1 }}, { 0 }, {}, { 2, 4 } });
    //m_assetRegistry.addParticleEmitterDescriptor(1, cft::ParticleEmitterDescriptor{ 1, 1, 1, cft::TrailConfiguration{ 1.0f, 0.08f, 0.05f, std::nullopt, 1.5f, std::nullopt, 15, false, { glm::vec4(1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.1f, 0.2f, 0.9f, 1.0f) }, std::nullopt, cft::TrailColorInterpolation::Linear, cft::TrailThicknessEvolution::Constant, std::nullopt, std::nullopt }, std::nullopt, cft::RenderConfiguration{cft::RenderType::Billboard, cft::BillboardRenderConfiguration{1}}, {0}, {}, {2, 4}});
    m_assetRegistry.addParticleEmitterDescriptor(2, cft::ParticleEmitterDescriptor{ 2, 2, 2, std::nullopt, std::nullopt, cft::SpawnTriggerDescriptor{ 4, std::nullopt, cft::ParticleEmitterSpawnContext{ 2, cft::TimeRange{ 0.0f, 1.0f }, cft::MotionState{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {} }, std::nullopt }, cft::RenderConfiguration{ cft::RenderType::Billboard, cft::BillboardRenderConfiguration{ /*1*/ std::nullopt}}, {5}, {}, {9}});
    
    m_assetRegistry.addParticleEffectDescriptor(0, cft::ParticleEffectDescriptor{ { cft::ParticleEmitterSpawnContext{ 0, cft::TimeRange{ 0.0f, 1.0f }, cft::MotionState{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {}}}});
    
    /*m_assetRegistry.addEmissionPattern(3, std::make_unique<cft::SingleBurstEmissionPattern>(1000));
    m_assetRegistry.addParticleSpawner(4, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::ConstantAttributeGenerator<cft::Color>>(glm::vec4(1.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Position>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Scale>>(glm::vec3(2.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::LinearVelocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(0.0f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(100.0f),
        100.0f
    ));
    m_assetRegistry.addParticleEmitter(3, cft::ParticleEmitterDescriptor{ 3, 4, 3, std::nullopt, std::nullopt, cft::RenderConfiguration{ cft::RenderType::Billboard, cft::BillboardRenderConfiguration{ std::nullopt } }, {}, {}, {} });
    m_assetRegistry.addParticleEffect(1, cft::ParticleEffect{ { cft::ParticleEmitterDescriptor{ 3, cft::TimeRange{ 0.0f, 100.0f }, cft::Transform{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {}}}});*/

    m_assetRegistry.addEmissionPattern(4, std::make_unique<cft::SingleBurstEmissionPattern>(100));
    m_assetRegistry.addParticleSpawner(5, std::make_unique<cft::ParticleSpawner>(
        std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{
            strength * glm::vec4(1.00f, 0.00f, 0.00f, 1.0f),
            strength * glm::vec4(1.00f, 0.25f, 0.00f, 1.0f),
            strength * glm::vec4(1.00f, 0.50f, 0.00f, 1.0f),
            strength * glm::vec4(1.00f, 0.75f, 0.00f, 1.0f),
            strength * glm::vec4(1.00f, 1.00f, 0.00f, 1.0f),
            strength * glm::vec4(0.75f, 1.00f, 0.00f, 1.0f),
            strength * glm::vec4(0.50f, 1.00f, 0.00f, 1.0f),
            strength * glm::vec4(0.25f, 1.00f, 0.00f, 1.0f),
            strength * glm::vec4(0.00f, 1.00f, 0.00f, 1.0f),
            strength * glm::vec4(0.00f, 1.00f, 0.25f, 1.0f),
            strength * glm::vec4(0.00f, 1.00f, 0.50f, 1.0f),
            strength * glm::vec4(0.00f, 1.00f, 0.75f, 1.0f),
            strength * glm::vec4(0.00f, 1.00f, 1.00f, 1.0f),
            strength * glm::vec4(0.00f, 0.75f, 1.00f, 1.0f),
            strength * glm::vec4(0.00f, 0.50f, 1.00f, 1.0f),
            strength * glm::vec4(0.00f, 0.25f, 1.00f, 1.0f),
            strength * glm::vec4(0.00f, 0.00f, 1.00f, 1.0f),
            strength * glm::vec4(0.25f, 0.00f, 1.00f, 1.0f),
            strength * glm::vec4(0.50f, 0.00f, 1.00f, 1.0f),
            strength * glm::vec4(0.75f, 0.00f, 1.00f, 1.0f),
            strength * glm::vec4(1.00f, 0.00f, 1.00f, 1.0f),
            strength * glm::vec4(1.00f, 0.00f, 0.75f, 1.0f),
            strength * glm::vec4(1.00f, 0.00f, 0.50f, 1.0f),
            strength * glm::vec4(1.00f, 0.00f, 0.25f, 1.0f),
            strength * glm::vec4(1.00f, 0.00f, 0.00f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::SphereSpawnShape>(0.1f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::vec3(0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.3f), glm::vec3(0.4f), m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::LinearVelocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Phase>>(0.0f),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(15.0f),
        15.0f
    ));
    //m_assetRegistry.addParticleEmitter(4, cft::ParticleEmitterDescriptor{ 4, 5, 4, cft::TrailConfiguration{ 0.0f, 0.12f, 0.05f, std::nullopt, 2.0f, std::nullopt, std::nullopt, true, { strength * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), strength * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), strength * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f) }, std::vector<float>{ 1.5f, 2.0f, 2.8f, 5.0f }, cft::ColorInterpolation::Linear, cft::ThicknessDistribution::LinearDecreasing, std::nullopt, std::nullopt }, std::nullopt, std::nullopt, cft::RenderConfiguration{cft::RenderType::Billboard, cft::BillboardRenderConfiguration{2}}, {6, 7}, {}, {} });
    //m_assetRegistry.addParticleEffect(2, cft::ParticleEffect{ { cft::ParticleEmitterDescriptor{ 4, cft::TimeRange{ 0.0f, 100.0f }, cft::MotionState{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {}}} });

    // Flare showcase
    //m_assetRegistry.addForceField(20, std::make_unique<cft::OrbitForceField>(cft::SpatialInfluence(glm::vec3(0.0f), 50.0f, cft::Falloff::Constant), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f, 10.0f, 0.1f));
    //m_assetRegistry.addForceField(20, std::make_unique<cft::OrbitForceField>(cft::SpatialInfluence(glm::vec3(0.0f), 50.0f, cft::Falloff::Constant), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f, 10.0f, 0.1f));
    m_assetRegistry.addVisualBehavior(20, std::make_unique<cft::FlickerVisualBehavior>(1.2f, 3.0f, 15.0f));
    m_assetRegistry.addVisualBehavior(21, std::make_unique<cft::GrowInVisualBehavior>(cft::ParticleTime::absolute(0.5f)));
    m_assetRegistry.addVisualBehavior(22, std::make_unique<cft::ShrinkOutVisualBehavior>(cft::ParticleTime::absolute(0.9f)));
    m_assetRegistry.addVisualBehavior(23, std::make_unique<cft::DimOutVisualBehavior>(cft::ParticleTime::absolute(0.5f)));
    m_assetRegistry.addParticleSpawner(20, std::make_unique<cft::ParticleSpawner>(
        //std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ strength * glm::vec4(0.0f, 0.1f, 0.4f, 1.0f), strength * glm::vec4(0.0f, 0.4f, 0.8f, 1.0f), strength * glm::vec4(0.4f, 0.8f, 1.0f, 1.0f) }, m_randomNumberGenerator),
        std::make_unique<cft::BinaryAttributeGenerator<cft::Color, float>>(std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<cft::Color>>(std::vector<glm::vec4>{ glm::vec4(0.0f, 0.1f, 0.4f, 1.0f), glm::vec4(0.0f, 0.4f, 0.8f, 1.0f), glm::vec4(0.4f, 0.8f, 1.0f, 1.0f) }, m_randomNumberGenerator), std::make_unique<cft::WeightedRandomSetAttributeGenerator<float>>(std::vector<cft::WeightedRandomSetAttributeGenerator<float>::WeightedValue>{ { 1.0f, 2 }, { 3.0f, 1 } }, m_randomNumberGenerator), [](const cft::Color& color, float intensity) { glm::vec4 c(glm::normalize(color) * intensity); c.a = color.a; return c; }),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::Color>>(glm::vec4(1.0f)),
        //std::make_unique<cft::SphereSpawnShape>(15.0f),
        //std::make_unique<cft::CircleSpawnShape>(15.0f, glm::vec3(0.2f, 2.0f, 1.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Position>>(glm::vec3(-15.0f), glm::vec3(15.0f), m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Rotation>>(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Scale>>(glm::vec3(0.6f), glm::vec3(0.8f), m_randomNumberGenerator),
        std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(glm::vec3(-2.0f), glm::vec3(2.0f), m_randomNumberGenerator),
        //std::make_unique<cft::RandomAttributeGenerator<cft::LinearVelocity>>(glm::vec3(-5.0f, -5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 0.0f), m_randomNumberGenerator),
        //std::make_unique<cft::ConstantAttributeGenerator<cft::LinearVelocity>>(glm::vec3(0.0f)),
        std::make_unique<cft::ConstantAttributeGenerator<cft::AngularVelocity>>(glm::vec3(0.0f, 0.0f, 0.0f)),
        std::make_unique<cft::RandomAttributeGenerator<cft::Phase>>(0.0f, 10.0f, m_randomNumberGenerator),
        std::make_unique<cft::ConstantAttributeGenerator<cft::Lifetime>>(10.0f),
        10.0f
    ));
    //m_assetRegistry.addEmissionPattern(20, std::make_unique<cft::ConstantRateEmissionPattern>(6.0f));
    //m_assetRegistry.addEmissionPattern(20, std::make_unique<cft::PeriodicBurstEmissionPattern>(4, 1.0f));
    m_assetRegistry.addEmissionPattern(20, std::make_unique<cft::SingleBurstEmissionPattern>(50));
    //m_assetRegistry.addEmissionPattern(20, std::make_unique<cft::LinearRateEmissionPattern>(1000.0f, 10.0f, 5.0f));
    //m_assetRegistry.addParticleEmitter(20, cft::ParticleEmitterDescriptor{ 20, 20, 20, std::nullopt, std::nullopt, std::nullopt, cft::RenderConfiguration{cft::RenderType::Billboard, cft::BillboardRenderConfiguration{ 20 } }, { 20 }, {}, { 20, 21, 22, 23 } });
    m_assetRegistry.addParticleEmitterDescriptor(20, cft::ParticleEmitterDescriptor{ 20, 20, 20, std::nullopt/*cft::TrailConfiguration{ 0.0f, 0.05f, std::nullopt, std::nullopt, cft::PathConfiguration{ 1.0f, 1.0f, 5.0f, std::nullopt, false, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, std::nullopt, cft::ColorInterpolation::Linear, cft::ThicknessDistribution::Linear, std::nullopt, cft::PathImage{5, 1.0f}}}*/, cft::RibbonConfiguration{cft::PathConfiguration{0.1f, 0.1f, std::nullopt, std::nullopt, true, {}, std::nullopt, cft::ColorInterpolation::Linear, cft::ThicknessDistribution::Linear, std::nullopt, std::nullopt}, 0, 3, 100 }, std::nullopt, cft::RenderConfiguration{cft::RenderType::Billboard, cft::BillboardRenderConfiguration{20}}, {/*20*/}, {}, {20, 21, 22, 23}});
    //m_assetRegistry.addParticleEmitterDescriptor(20, cft::ParticleEmitterDescriptor{ 20, 20, 20, cft::TrailConfiguration{ 0.0f, 0.05f, std::nullopt, std::nullopt, cft::PathConfiguration{ 1.0f, 5.0f, std::nullopt, false, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, std::nullopt, cft::ColorInterpolation::Linear, cft::ThicknessDistribution::Constant, std::nullopt, cft::PathImage{ 5, 1.0f } } }, std::nullopt, std::nullopt, cft::RenderConfiguration{cft::RenderType::Billboard, cft::BillboardRenderConfiguration{20}}, { 20 }, {2}, {20, 21, 22, 23} });
    m_assetRegistry.addParticleEffectDescriptor(20, cft::ParticleEffectDescriptor{ { cft::ParticleEmitterSpawnContext{ 20, cft::TimeRange{ 0.0f, 60.0f }, cft::MotionState{ glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f) }, {}, {}}} });

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