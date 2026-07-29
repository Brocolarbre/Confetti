#pragma once

#include <nlohmann/json.hpp>
#include <Confetti/Rendering/ParticleRenderer.hpp>

class JsonLoader
{
private:
	using json = nlohmann::json;

	static std::unique_ptr<cft::ForceField> parseForceField(const json& data);
	static std::unique_ptr<cft::MotionBehavior> parseMotionBehavior(const json& data);
	static std::unique_ptr<cft::VisualBehavior> parseVisualBehavior(const json& data);
	static std::unique_ptr<cft::ParticleSpawner> parseParticleSpawner(const json& data);
	static std::unique_ptr<cft::EmissionPattern> parseEmissionPattern(const json& data);
	static std::unique_ptr<cft::ParticleLinker> parseParticleLinker(const json& data);
	static std::unique_ptr<cft::RibbonGenerator> parseRibbonGenerator(const json& data);
	static cft::Image parseImage(const json& data);
	static cft::Model parseModel(const json& data);
	static cft::SpriteSheetDescriptor parseSpriteSheetDescriptor(const json& data);
	static cft::ParticleEffectDescriptor parseParticleEffectDescriptor(const json& data);
	static cft::ParticleEmitterDescriptor parseParticleEmitterDescriptor(const json& data);

	static void loadAssets(const json& data, cft::AssetRegistry& assetRegistry);
	static void loadBillboardRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
	static void loadMeshRendererTextures(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
	static void loadMeshRendererMeshes(const json& data, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);

public:
	static void load(const std::string& path, cft::ParticleSimulation& particleSimulation, cft::ParticleRenderer& particleRenderer, cft::AssetRegistry& assetRegistry);
};