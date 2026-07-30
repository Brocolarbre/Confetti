#pragma once

#include "JsonFactory.hpp"

#include <Confetti/Rendering/ParticleRenderer.hpp>
#include <Confetti/Behavior/Force/ForceField.hpp>
#include <Confetti/Behavior/Motion/MotionBehavior.hpp>
#include <Confetti/Behavior/Visual/VisualBehavior.hpp>
#include <Confetti/Emission/ParticleSpawner.hpp>
#include <Confetti/Emission/EmissionPattern/EmissionPattern.hpp>
#include <Confetti/Simulation/Link/ParticleLinker/ParticleLinker.hpp>
#include <Confetti/Simulation/Link/RibbonGenerator/RibbonGenerator.hpp>

class JsonLoader
{
private:
	using json = nlohmann::json;

	static JsonFactory<cft::ForceField> m_forceFieldFactory;
	static JsonFactory<cft::MotionBehavior> m_motionBehaviorFactory;
	static JsonFactory<cft::VisualBehavior> m_visualBehaviorFactory;
	static JsonFactory<cft::EmissionPattern> m_emissionPatternFactory;
	static JsonFactory<cft::ParticleLinker> m_particleLinkerFactory;
	static JsonFactory<cft::RibbonGenerator> m_ribbonGeneratorFactory;

	static bool m_initialized;

	static void registerTypes(JsonFactory<cft::ForceField>& factory);
	static void registerTypes(JsonFactory<cft::MotionBehavior>& factory);
	static void registerTypes(JsonFactory<cft::VisualBehavior>& factory);
	static void registerTypes(JsonFactory<cft::EmissionPattern>& factory);
	static void registerTypes(JsonFactory<cft::ParticleLinker>& factory);
	static void registerTypes(JsonFactory<cft::RibbonGenerator>& factory);

	static void loadAssets(const json& data, cft::AssetRegistry& assetRegistry);
	static void loadBillboardRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
	static void loadMeshRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
	static void loadMeshRendererMeshes(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);

public:
	static void initialize();
	static void load(const std::string& path, cft::ParticleSimulation& particleSimulation, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
};