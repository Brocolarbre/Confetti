#include "JsonSerialization.hpp"
#include "JsonLoaderAttributeGenerator.hpp"

namespace nlohmann
{
	void adl_serializer<std::unique_ptr<cft::ParticleSpawner>>::from_json(const json& data, std::unique_ptr<cft::ParticleSpawner>& value)
	{
		if (data.contains("spawnShape"))
		{
			value = std::make_unique<cft::ParticleSpawner>(
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, Color>(data.at("colorAttributeGenerator")),
				data.at("spawnShape").get<std::unique_ptr<cft::SpawnShape>>(),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, Vec3>(data.at("rotationAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, Vec3>(data.at("scaleAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, Vec3>(data.at("linearVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, Vec3>(data.at("angularVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data.at("phaseAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data.at("lifetimeAttributeGenerator")),
				data.at("maximumParticleLifetime")
			);
		}
		else
		{
			value = std::make_unique<cft::ParticleSpawner>(
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, Color>(data.at("colorAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Position, Vec3>(data.at("positionAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, Vec3>(data.at("rotationAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, Vec3>(data.at("scaleAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, Vec3>(data.at("linearVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, Vec3>(data.at("angularVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data.at("phaseAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data.at("lifetimeAttributeGenerator")),
				data.at("maximumParticleLifetime")
			);
		}
	}
}