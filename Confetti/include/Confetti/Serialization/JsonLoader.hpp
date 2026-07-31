#pragma once

#include "Factory/JsonFactory.hpp"
#include "ProviderRegistry.hpp"

#include "Confetti/Rendering/ParticleRenderer.hpp"
#include "Confetti/Behavior/Force/ForceField.hpp"
#include "Confetti/Behavior/Motion/MotionBehavior.hpp"
#include "Confetti/Behavior/Visual/VisualBehavior.hpp"
#include "Confetti/Emission/ParticleSpawner.hpp"
#include "Confetti/Emission/EmissionPattern/EmissionPattern.hpp"
#include "Confetti/Simulation/Link/ParticleLinker/ParticleLinker.hpp"
#include "Confetti/Simulation/Link/RibbonGenerator/RibbonGenerator.hpp"

#include <LineWeaver/Interpolation/Interpolator.hpp>
#include <LineWeaver/Easing/Easing.hpp>

namespace cft
{
	class CONFETTI_API JsonLoader
	{
	private:
		using json = nlohmann::json;

		static JsonFactory<cft::ForceField> m_forceFieldFactory;
		static JsonFactory<cft::MotionBehavior> m_motionBehaviorFactory;
		static JsonFactory<cft::VisualBehavior> m_visualBehaviorFactory;
		static JsonFactory<cft::EmissionPattern> m_emissionPatternFactory;
		static JsonFactory<cft::ParticleLinker> m_particleLinkerFactory;
		static JsonFactory<cft::RibbonGenerator> m_ribbonGeneratorFactory;
		static JsonFactory<cft::SpawnShape> m_spawnShapeFactory;
		static JsonFactory<cft::LinkRule> m_linkRuleFactory;
		static JsonFactory<lw::Interpolator> m_interpolatorFactory;
		static JsonFactory<lw::Easing> m_easingFactory;

		static ProviderRegistry m_providerRegistry;

		static bool m_initialized;

		static void registerTypes(JsonFactory<cft::ForceField>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::MotionBehavior>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::VisualBehavior>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::EmissionPattern>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::ParticleLinker>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::RibbonGenerator>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::SpawnShape>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<cft::LinkRule>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<lw::Interpolator>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<lw::Easing>& factory, const ProviderRegistry& providerRegistry);

		static void loadAssets(const json& data, cft::AssetRegistry& assetRegistry);
		static void loadBillboardRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
		static void loadMeshRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
		static void loadMeshRendererMeshes(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);

	public:
		static void initialize();
		static void load(const std::string& path, cft::ParticleSimulation& particleSimulation, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);

		static JsonFactory<cft::ForceField>& getForceFieldFactory();
		static JsonFactory<cft::MotionBehavior>& getMotionBehaviorFactory();
		static JsonFactory<cft::VisualBehavior>& getVisualBehaviorFactory();
		static JsonFactory<cft::EmissionPattern>& getEmissionPatternFactory();
		static JsonFactory<cft::ParticleLinker>& getParticleLinkerFactory();
		static JsonFactory<cft::RibbonGenerator>& getRibbonGeneratorFactory();
		static JsonFactory<cft::SpawnShape>& getSpawnShapeFactory();
		static JsonFactory<cft::LinkRule>& getLinkRuleFactory();
		static JsonFactory<lw::Interpolator>& getInterpolatorFactory();
		static JsonFactory<lw::Easing>& getEasingFactory();

		static ProviderRegistry& getProviderRegistry();
	};
}