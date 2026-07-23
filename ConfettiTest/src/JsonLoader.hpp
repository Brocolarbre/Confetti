#pragma once

#include <string>

#include <Confetti/Simulation/Registry/AssetRegistry.hpp>
#include <Confetti/Behavior/Force/SpatialInfluence.hpp>
#include <Confetti/Behavior/Visual/ParticleTime.hpp>
#include <Confetti/Tool/RandomNumberGenerator.hpp>
#include <LineWeaver/Interpolation/Interpolator.hpp>
#include <LineWeaver/Easing/Easing.hpp>

#include <nlohmann/json.hpp>

class JsonLoader
{
private:
	using json = nlohmann::json;

	template <typename T>
	static T parseValue(const json& data);

	template <typename T>
	static std::vector<T> parseArray(const json& data, const std::function<T(const json& data)>& parsingFunction);

	template <typename T>
	std::unique_ptr<cft::AttributeGenerator<T>> parseAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);

	static glm::vec4 parseColor(const json& data);
	static glm::vec3 parseVec3(const json& data);
	static glm::vec2 parseVec2(const json& data);
	static lw::Point parsePoint(const json& data);

	static std::unique_ptr<cft::SpawnShape> parseSpawnShape(const json& data);

	static cft::Falloff parseFalloff(const json& data);
	static cft::SpatialInfluence parseSpatialInfluence(const json& data);
	static std::unique_ptr<lw::Interpolator> parseInterpolator(const json& data);
	static std::unique_ptr<lw::Easing> parseEasing(const json& data);
	static cft::ParticleTime::Space parseParticleTimeSpace(const json& data);
	static cft::ParticleTime parseParticleTime(const json& data);
	static std::unique_ptr<cft::LinkRule> parseLinkRule(const json& data);
	static cft::ThicknessEvolutionDistribution parseThicknessEvolutionDistribution(const json& data);
	static cft::LifetimeFade parseLifetimeFade(const json& data);
	static cft::ColorInterpolation parseColorInterpolation(const json& data);
	static cft::ThicknessDistribution parseThicknessDistribution(const json& data);
	static cft::ThicknessEvolution parseThicknessEvolution(const json& data);
	static cft::PathImage parsePathImage(const json& data);
	static cft::PeriodicSpawnTriggerContext parsePeriodicTriggerSpawnContext(const json& data);
	static cft::ParticleEmitterSpawnContext parseParticleEmitterSpawnContext(const json& data);
	static cft::PathConfiguration parsePathConfiguration(const json& data);
	static cft::TrailConfiguration parseTrailConfiguration(const json& data);
	static cft::RibbonConfiguration parseRibbonConfiguration(const json& data);
	static cft::TimeRange parseTimeRange(const json& data);
	static cft::MotionState parseMotionState(const json& data);
	static cft::SpawnTriggerDescriptor parseSpawnTriggerDescriptor(const json& data);
	static cft::RenderType parseRenderType(const json& data);
	static cft::RenderConfiguration parseRenderConfiguration(const json& data);
	static cft::BillboardRenderConfiguration parseBillboardRenderConfiguration(const json& data);
	static cft::MeshRenderConfiguration parseMeshRenderConfiguration(const json& data);

	static std::unique_ptr<cft::ForceField> parseForceField(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::MotionBehavior> parseMotionBehavior(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::VisualBehavior> parseVisualBehavior(const json& data);
	static std::unique_ptr<cft::ParticleSpawner> parseParticleSpawner(const json& data);
	static std::unique_ptr<cft::EmissionPattern> parseEmissionPattern(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::ParticleLinker> parseParticleLinker(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::RibbonGenerator> parseRibbonGenerator(const json& data);
	static cft::Image parseImage(const json& data);
	static cft::Model parseModel(const json& data);
	static cft::SpriteSheetDescriptor parseSpriteSheetDescriptor(const json& data);
	static cft::ParticleEffectDescriptor parseParticleEffectDescriptor(const json& data);
	static cft::ParticleEmitterDescriptor parseParticleEmitterDescriptor(const json& data);

public:
	void load(const std::string& path, cft::AssetRegistry& assetRegistry, cft::RandomNumberGenerator& randomNumberGenerator);
};

template<typename T>
inline T JsonLoader::parseValue(const json& data)
{
	return data;
}

template<typename T>
inline std::vector<T> JsonLoader::parseArray(const json& data, const std::function<T(const json& data)>& parsingFunction)
{
	std::vector<T> array;
	array.reserve(data.size());

	for (const json& value : data)
		array.push_back(parsingFunction(value));

	return array;
}

template <typename T>
std::unique_ptr<cft::AttributeGenerator<T>> JsonLoader::parseAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator)
{
	std::string type = data["type"];

	if (type == "Constant")
		return std::make_unique<cft::ConstantAttributeGenerator<T>>(data["value"]);
	if (type == "InterpolatedRandomSet")
		return std::make_unique<cft::InterpolatedRandomSetAttributeGenerator<T>>(parseArray<T>(data["values"], /* I need to put the correct parsing function here */), randomNumberGenerator);
	if (type == "Linear")
		return std::make_unique<cft::LinearAttributeGenerator<T>>();
	if (type == "Random")
		return std::make_unique<cft::RandomAttributeGenerator<T>>();
	if (type == "RandomSet")
		return std::make_unique<cft::RandomSetAttributeGenerator<T>>();
	if (type == "WeightedRandomSet")
		return std::make_unique<cft::AttributeGenerator<T>>();
	if (type == "NormalBurstLinear")
		return std::make_unique<cft::AttributeGenerator<T>>();
	if (type == "NormalLinear")
		return std::make_unique<cft::NormalLinearVelocityGenerator>();
	if (type == "RandomNormalOffset")
		return std::make_unique<cft::RandomNormalOffsetPositionGenerator>();
}