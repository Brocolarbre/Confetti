#include "Confetti/Serialization/JsonSerialization.hpp"
#include "Confetti/Serialization/JsonLoaderAttributeGenerator.hpp"

namespace nlohmann
{
	void adl_serializer<cft::JsonTypes::Color>::from_json(const json& data, cft::JsonTypes::Color& value)
	{
		value.value = glm::vec4(data.at("r"), data.at("g"), data.at("b"), data.at("a"));
	}

	void adl_serializer<cft::JsonTypes::Vec3>::from_json(const json& data, cft::JsonTypes::Vec3& value)
	{
		value.value = glm::vec3(data.at("x"), data.at("y"), data.at("z"));
	}

	void adl_serializer<cft::JsonTypes::Vec2>::from_json(const json& data, cft::JsonTypes::Vec2& value)
	{
		value.value = glm::vec2(data.at("x"), data.at("y"));
	}

	void adl_serializer<lw::Point>::from_json(const json& data, lw::Point& value)
	{
		value = lw::Point(data.at("x"), data.at("y"), data.at("z"));
	}

	void adl_serializer<glm::vec4>::from_json(const json& data, glm::vec4& value)
	{
		value = glm::vec4(data.at("x"), data.at("y"), data.at("z"), data.at("w"));
	}

	void adl_serializer<cft::Falloff>::from_json(const json& data, cft::Falloff& value)
	{
		if (data == "Constant")
			value = cft::Falloff::Constant;
		else if (data == "Linear")
			value = cft::Falloff::Linear;
		else if (data == "Quadratic")
			value = cft::Falloff::Quadratic;
		else if (data == "Cubic")
			value = cft::Falloff::Cubic;
		else
			throw std::runtime_error("Invalid falloff type : '" + std::string(data) + "'");
	}

	cft::SpatialInfluence adl_serializer<cft::SpatialInfluence>::from_json(const json& data)
	{
		return cft::SpatialInfluence{
			data.at("origin").get<cft::JsonTypes::Vec3>().value,
			data.at("radius"),
			data.at("falloff").get<cft::Falloff>()
		};
	}

	void adl_serializer<std::unique_ptr<lw::Interpolator>>::from_json(const json& data, std::unique_ptr<lw::Interpolator>& value)
	{
		value = cft::JsonLoader::getInterpolatorFactory().instantiate(data);
	}

	void adl_serializer<std::unique_ptr<lw::Easing>>::from_json(const json& data, std::unique_ptr<lw::Easing>& value)
	{
		value = cft::JsonLoader::getEasingFactory().instantiate(data);
	}

	void adl_serializer<cft::ParticleTime::Space>::from_json(const json& data, cft::ParticleTime::Space& value)
	{
		if (data == "Absolute")
			value = cft::ParticleTime::Space::Absolute;
		else if (data == "Normalized")
			value = cft::ParticleTime::Space::Normalized;
		else
			throw std::runtime_error("Invalid particle time space type : '" + std::string(data) + "'");
	}

	void adl_serializer<cft::ParticleTime>::from_json(const json& data, cft::ParticleTime& value)
	{
		value = cft::ParticleTime{
			data.at("value"),
			data.at("space").get<cft::ParticleTime::Space>()
		};
	}

	void adl_serializer<std::unique_ptr<cft::LinkRule>>::from_json(const json& data, std::unique_ptr<cft::LinkRule>& value)
	{
		value = cft::JsonLoader::getLinkRuleFactory().instantiate(data);
	}

	void adl_serializer<cft::ThicknessEvolutionDistribution>::from_json(const json& data, cft::ThicknessEvolutionDistribution& value)
	{
		if (data == "Constant")
			value = cft::ThicknessEvolutionDistribution::Constant;
		else if (data == "Linear")
			value = cft::ThicknessEvolutionDistribution::Linear;
		else if (data == "Quadratic")
			value = cft::ThicknessEvolutionDistribution::Quadratic;
		else
			throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
	}

	void adl_serializer<cft::LifetimeFade>::from_json(const json& data, cft::LifetimeFade& value)
	{
		value = cft::LifetimeFade{
			data.at("start"),
			data.at("end")
		};
	}

	void adl_serializer<cft::ColorInterpolation>::from_json(const json& data, cft::ColorInterpolation& value)
	{
		if (data == "Constant")
			value = cft::ColorInterpolation::Constant;
		else if (data == "Linear")
			value = cft::ColorInterpolation::Linear;
		else
			throw std::runtime_error("Invalid color interpolation type : '" + std::string(data) + "'");
	}

	void adl_serializer<cft::ThicknessDistribution>::from_json(const json& data, cft::ThicknessDistribution& value)
	{
		if (data == "Linear")
			value = cft::ThicknessDistribution::Linear;
		else if (data == "Quadratic")
			value = cft::ThicknessDistribution::Quadratic;
		else
			throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
	}

	void adl_serializer<cft::ThicknessEvolution>::from_json(const json& data, cft::ThicknessEvolution& value)
	{
		value = cft::ThicknessEvolution{
			data.at("distribution").get<cft::ThicknessEvolutionDistribution>(),
			data.at("speed")
		};
	}

	void adl_serializer<cft::PathImage>::from_json(const json& data, cft::PathImage& value)
	{
		value = cft::PathImage{
			data.at("imageId"),
			cft::JsonTools::parseOptional<float>(data.at("repeatStretch"))
		};
	}

	void adl_serializer<cft::TimeRange>::from_json(const json& data, cft::TimeRange& value)
	{
		value = cft::TimeRange{
			data.at("spawnTime"),
			data.at("duration")
		};
	}

	void adl_serializer<cft::MotionState>::from_json(const json& data, cft::MotionState& value)
	{
		glm::vec3 eulerAngles = data.at("rotation").get<cft::JsonTypes::Vec3>().value;
		glm::quat rotation = cft::JsonTools::eulerAnglesToQuaternion(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));

		value = cft::MotionState{
			data.at("position").get<cft::JsonTypes::Vec3>().value,
			data.at("linearVelocity").get<cft::JsonTypes::Vec3>().value,
			rotation,
			data.at("angularVelocity").get<cft::JsonTypes::Vec3>().value
		};
	}

	void adl_serializer<cft::ParticleEmitterSpawnContext>::from_json(const json& data, cft::ParticleEmitterSpawnContext& value)
	{
		value = cft::ParticleEmitterSpawnContext{
			data.at("emitterDescriptorId"),
			data.at("timeRange").get<cft::TimeRange>(),
			data.at("initialMotionState").get<cft::MotionState>(),
			data.at("forceFieldIds").get<std::vector<unsigned int>>(),
			data.at("motionBehaviorIds").get<std::vector<unsigned int>>()
		};
	}

	void adl_serializer<cft::PeriodicSpawnTriggerContext>::from_json(const json& data, cft::PeriodicSpawnTriggerContext& value)
	{
		value = cft::PeriodicSpawnTriggerContext{
			data.at("emitterSpawnContext").get<cft::ParticleEmitterSpawnContext>(),
			data.at("interval")
		};
	}

	void adl_serializer<cft::PathConfiguration>::from_json(const json& data, cft::PathConfiguration& value)
	{
		value = cft::PathConfiguration{
			data.at("startThickness"),
			data.at("endThickness"),
			cft::JsonTools::parseOptional<float>(data.at("lifetime")),
			cft::JsonTools::parseOptional<cft::LifetimeFade>(data.at("lifetimeFade")),
			data.at("appendParticleColor"),
			cft::JsonTools::wrapperToType<cft::Color>(data.at("colorGradient").get<std::vector<cft::JsonTypes::Color>>()),
			cft::JsonTools::parseOptional<std::vector<float>>(data.at("colorStart")),
			data.at("colorInterpolation").get<cft::ColorInterpolation>(),
			data.at("thicknessDistribution").get<cft::ThicknessDistribution>(),
			cft::JsonTools::parseOptional<cft::ThicknessEvolution>(data.at("thicknessEvolution")),
			cft::JsonTools::parseOptional<cft::PathImage>(data.at("pathImage"))
		};
	}

	void adl_serializer<cft::TrailConfiguration>::from_json(const json& data, cft::TrailConfiguration& value)
	{
		value = cft::TrailConfiguration{
			data.at("persistenceLifetime"),
			data.at("minimumSpawnDistance"),
			cft::JsonTools::parseOptional<float>(data.at("maximumSpawnTime")),
			cft::JsonTools::parseOptional<unsigned int>(data.at("maximumSegmentCount")),
			data.at("pathConfiguration").get<cft::PathConfiguration>()
		};
	}

	void adl_serializer<cft::RibbonConfiguration>::from_json(const json& data, cft::RibbonConfiguration& value)
	{
		value = cft::RibbonConfiguration{
			data.at("pathConfiguration").get<cft::PathConfiguration>(),
			data.at("particleLinkerId"),
			data.at("ribbonGeneratorId"),
			data.at("ribbonPointCount")
		};
	}

	void adl_serializer<cft::SpawnTriggerDescriptor>::from_json(const json& data, cft::SpawnTriggerDescriptor& value)
	{
		value = cft::SpawnTriggerDescriptor{
			data.at("maximumRecursionDepth"),
			cft::JsonTools::parseOptional<cft::ParticleEmitterSpawnContext>(data.at("spawnEmitterSpawnContext")),
			cft::JsonTools::parseOptional<cft::ParticleEmitterSpawnContext>(data.at("deathEmitterSpawnContext")),
			cft::JsonTools::parseOptional<cft::PeriodicSpawnTriggerContext>(data.at("periodicEmitterSpawnContext"))
		};
	}

	void adl_serializer<cft::RenderType>::from_json(const json& data, cft::RenderType& value)
	{
		if (data == "Billboard")
			value = cft::RenderType::Billboard;
		else if (data == "Mesh")
			value = cft::RenderType::Mesh;
		else
			throw std::runtime_error("Invalid render type : '" + std::string(data) + "'");
	}

	void adl_serializer<cft::BillboardRenderConfiguration>::from_json(const json& data, cft::BillboardRenderConfiguration& value)
	{
		value = cft::BillboardRenderConfiguration{
			cft::JsonTools::parseOptional<unsigned int>(data.at("spriteSheetId"))
		};
	}

	void adl_serializer<cft::MeshRenderConfiguration>::from_json(const json& data, cft::MeshRenderConfiguration& value)
	{
		value = cft::MeshRenderConfiguration{
			data.at("modelId"),
			cft::JsonTools::parseOptional<unsigned int>(data.at("imageId"))
		};
	}

	void adl_serializer<cft::RenderConfiguration>::from_json(const json& data, cft::RenderConfiguration& value)
	{
		cft::RenderType renderType = data.at("renderType").get<cft::RenderType>();
		std::variant<cft::BillboardRenderConfiguration, cft::MeshRenderConfiguration> configurationData;

		switch (renderType)
		{
		case cft::RenderType::Billboard:
			configurationData = data.at("configurationData").get<cft::BillboardRenderConfiguration>();
			break;
		case cft::RenderType::Mesh:
			configurationData = data.at("configurationData").get<cft::MeshRenderConfiguration>();
			break;
		}

		value = cft::RenderConfiguration{
			renderType,
			configurationData
		};
	}

	void adl_serializer<std::unique_ptr<cft::SpawnShape>>::from_json(const json& data, std::unique_ptr<cft::SpawnShape>& value)
	{
		value = cft::JsonLoader::getSpawnShapeFactory().instantiate(data);
	}

	void adl_serializer<std::unique_ptr<cft::ParticleSpawner>>::from_json(const json& data, std::unique_ptr<cft::ParticleSpawner>& value)
	{
		if (data.contains("spawnShape"))
		{
			value = std::make_unique<cft::ParticleSpawner>(
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, cft::JsonTypes::Color>(data.at("colorAttributeGenerator")),
				data.at("spawnShape").get<std::unique_ptr<cft::SpawnShape>>(),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, cft::JsonTypes::Vec3>(data.at("rotationAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, cft::JsonTypes::Vec3>(data.at("scaleAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, cft::JsonTypes::Vec3>(data.at("linearVelocityAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, cft::JsonTypes::Vec3>(data.at("angularVelocityAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data.at("phaseAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data.at("lifetimeAttributeGenerator")),
				data.at("maximumParticleLifetime")
			);
		}
		else
		{
			value = std::make_unique<cft::ParticleSpawner>(
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Color, cft::JsonTypes::Color>(data.at("colorAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Position, cft::JsonTypes::Vec3>(data.at("positionAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Rotation, cft::JsonTypes::Vec3>(data.at("rotationAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Scale, cft::JsonTypes::Vec3>(data.at("scaleAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::LinearVelocity, cft::JsonTypes::Vec3>(data.at("linearVelocityAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::AngularVelocity, cft::JsonTypes::Vec3>(data.at("angularVelocityAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Phase, float>(data.at("phaseAttributeGenerator")),
				cft::JsonLoaderAttributeGenerator::parseAttributeGenerator<cft::Lifetime, float>(data.at("lifetimeAttributeGenerator")),
				data.at("maximumParticleLifetime")
			);
		}
	}

	void adl_serializer<cft::Image>::from_json(const json& data, cft::Image& value)
	{
		cft::Image image;
		image.loadFromFile(data.at("path"));

		value = image;
	}

	void adl_serializer<cft::Model>::from_json(const json& data, cft::Model& value)
	{
		cft::Model model;
		model.loadFromFile(data.at("path"));

		value = model;
	}

	void adl_serializer<cft::SpriteSheetDescriptor>::from_json(const json& data, cft::SpriteSheetDescriptor& value)
	{
		value = cft::SpriteSheetDescriptor{
			data.at("imageId"),
			data.at("frameCount"),
			data.at("rowFrameCount"),
			data.at("frameWidth"),
			data.at("frameHeight"),
			data.at("animationSpeed")
		};
	}

	void adl_serializer<cft::ParticleEffectDescriptor>::from_json(const json& data, cft::ParticleEffectDescriptor& value)
	{
		value = cft::ParticleEffectDescriptor{
			data.at("emitterSpawnContexts").get<std::vector<cft::ParticleEmitterSpawnContext>>()
		};
	}

	void adl_serializer<cft::ParticleEmitterDescriptor>::from_json(const json& data, cft::ParticleEmitterDescriptor& value)
	{
		value = cft::ParticleEmitterDescriptor{
			data.at("poolId"),
			data.at("particleSpawnerId"),
			data.at("emissionPatternId"),
			cft::JsonTools::parseOptional<cft::TrailConfiguration>(data.at("trailConfiguration")),
			cft::JsonTools::parseOptional<cft::RibbonConfiguration>(data.at("ribbonConfiguration")),
			cft::JsonTools::parseOptional<cft::SpawnTriggerDescriptor>(data.at("spawnTriggerDescriptor")),
			data.at("renderConfiguration").get<cft::RenderConfiguration>(),
			data.at("forceFieldIds").get<std::vector<unsigned int>>(),
			data.at("motionBehaviorIds").get<std::vector<unsigned int>>(),
			data.at("visualBehaviorIds").get<std::vector<unsigned int>>()
		};
	}
}