#pragma once

#include "JsonSerialization.hpp"

class JsonLoader
{
private:
	using json = nlohmann::json;

	static std::unique_ptr<cft::AttributeGenerator<cft::Color>> parseColorAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::Position>> parsePositionAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::Rotation>> parseRotationAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::Scale>> parseScaleAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::LinearVelocity>> parseLinearVelocityAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::AngularVelocity>> parseAngularVelocityAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::Phase>> parsePhaseAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::AttributeGenerator<cft::Lifetime>> parseLifetimeAttributeGenerator(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);

	static std::unique_ptr<cft::ForceField> parseForceField(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::MotionBehavior> parseMotionBehavior(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
	static std::unique_ptr<cft::VisualBehavior> parseVisualBehavior(const json& data);
	static std::unique_ptr<cft::ParticleSpawner> parseParticleSpawner(const json& data, cft::RandomNumberGenerator& randomNumberGenerator);
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