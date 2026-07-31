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
	class ParticleSystem;

	class CONFETTI_API JsonLoader
	{
	private:
		using json = nlohmann::json;

		static JsonFactory<ForceField> m_forceFieldFactory;
		static JsonFactory<MotionBehavior> m_motionBehaviorFactory;
		static JsonFactory<VisualBehavior> m_visualBehaviorFactory;
		static JsonFactory<EmissionPattern> m_emissionPatternFactory;
		static JsonFactory<ParticleLinker> m_particleLinkerFactory;
		static JsonFactory<RibbonGenerator> m_ribbonGeneratorFactory;
		static JsonFactory<SpawnShape> m_spawnShapeFactory;
		static JsonFactory<LinkRule> m_linkRuleFactory;
		static JsonFactory<lw::Interpolator> m_interpolatorFactory;
		static JsonFactory<lw::Easing> m_easingFactory;

		static bool m_initialized;

		static void registerTypes(JsonFactory<ForceField>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<MotionBehavior>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<VisualBehavior>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<EmissionPattern>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<ParticleLinker>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<RibbonGenerator>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<SpawnShape>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<LinkRule>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<lw::Interpolator>& factory, const ProviderRegistry& providerRegistry);
		static void registerTypes(JsonFactory<lw::Easing>& factory, const ProviderRegistry& providerRegistry);

		static void loadAssets(const json& data, AssetRegistry& assetRegistry);
		static void loadBillboardRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry);
		static void loadMeshRendererTextures(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry);
		static void loadMeshRendererMeshes(const json& data, ParticleRenderer& particleRenderer, AssetRegistry& assetRegistry);

	public:
		static void initialize(const ProviderRegistry& providerRegistry);
		static void load(const std::string& path, ParticleSystem& particleSystem);
		static void clear();

		static JsonFactory<ForceField>& getForceFieldFactory();
		static JsonFactory<MotionBehavior>& getMotionBehaviorFactory();
		static JsonFactory<VisualBehavior>& getVisualBehaviorFactory();
		static JsonFactory<EmissionPattern>& getEmissionPatternFactory();
		static JsonFactory<ParticleLinker>& getParticleLinkerFactory();
		static JsonFactory<RibbonGenerator>& getRibbonGeneratorFactory();
		static JsonFactory<SpawnShape>& getSpawnShapeFactory();
		static JsonFactory<LinkRule>& getLinkRuleFactory();
		static JsonFactory<lw::Interpolator>& getInterpolatorFactory();
		static JsonFactory<lw::Easing>& getEasingFactory();
	};
}