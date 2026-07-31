#include "Confetti/Serialization/JsonSerialization.hpp"
#include "Confetti/Serialization/JsonLoaderAttributeGenerator.hpp"

using namespace cft;

namespace nlohmann
{
	void adl_serializer<JsonTypes::Color>::from_json(const json& data, JsonTypes::Color& value)
	{
		value.value = glm::vec4(data.at("r"), data.at("g"), data.at("b"), data.at("a"));
	}

	void adl_serializer<JsonTypes::Vec3>::from_json(const json& data, JsonTypes::Vec3& value)
	{
		value.value = glm::vec3(data.at("x"), data.at("y"), data.at("z"));
	}

	void adl_serializer<JsonTypes::Vec2>::from_json(const json& data, JsonTypes::Vec2& value)
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

	void adl_serializer<Falloff>::from_json(const json& data, Falloff& value)
	{
		if (data == "Constant")
			value = Falloff::Constant;
		else if (data == "Linear")
			value = Falloff::Linear;
		else if (data == "Quadratic")
			value = Falloff::Quadratic;
		else if (data == "Cubic")
			value = Falloff::Cubic;
		else
			throw std::runtime_error("Invalid falloff type : '" + std::string(data) + "'");
	}

	SpatialInfluence adl_serializer<SpatialInfluence>::from_json(const json& data)
	{
		return SpatialInfluence{
			data.at("origin").get<JsonTypes::Vec3>().value,
			data.at("radius"),
			data.at("falloff").get<Falloff>()
		};
	}

	void adl_serializer<std::unique_ptr<lw::Interpolator>>::from_json(const json& data, std::unique_ptr<lw::Interpolator>& value)
	{
		value = JsonLoader::getInterpolatorFactory().instantiate(data);
	}

	void adl_serializer<std::unique_ptr<lw::Easing>>::from_json(const json& data, std::unique_ptr<lw::Easing>& value)
	{
		value = JsonLoader::getEasingFactory().instantiate(data);
	}

	void adl_serializer<ParticleTime::Space>::from_json(const json& data, ParticleTime::Space& value)
	{
		if (data == "Absolute")
			value = ParticleTime::Space::Absolute;
		else if (data == "Normalized")
			value = ParticleTime::Space::Normalized;
		else
			throw std::runtime_error("Invalid particle time space type : '" + std::string(data) + "'");
	}

	void adl_serializer<ParticleTime>::from_json(const json& data, ParticleTime& value)
	{
		value = ParticleTime{
			data.at("value"),
			data.at("space").get<ParticleTime::Space>()
		};
	}

	void adl_serializer<std::unique_ptr<LinkRule>>::from_json(const json& data, std::unique_ptr<LinkRule>& value)
	{
		value = JsonLoader::getLinkRuleFactory().instantiate(data);
	}

	void adl_serializer<ThicknessEvolutionDistribution>::from_json(const json& data, ThicknessEvolutionDistribution& value)
	{
		if (data == "Constant")
			value = ThicknessEvolutionDistribution::Constant;
		else if (data == "Linear")
			value = ThicknessEvolutionDistribution::Linear;
		else if (data == "Quadratic")
			value = ThicknessEvolutionDistribution::Quadratic;
		else
			throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
	}

	void adl_serializer<LifetimeFade>::from_json(const json& data, LifetimeFade& value)
	{
		value = LifetimeFade{
			data.at("start"),
			data.at("end")
		};
	}

	void adl_serializer<ColorInterpolation>::from_json(const json& data, ColorInterpolation& value)
	{
		if (data == "Constant")
			value = ColorInterpolation::Constant;
		else if (data == "Linear")
			value = ColorInterpolation::Linear;
		else
			throw std::runtime_error("Invalid color interpolation type : '" + std::string(data) + "'");
	}

	void adl_serializer<ThicknessDistribution>::from_json(const json& data, ThicknessDistribution& value)
	{
		if (data == "Linear")
			value = ThicknessDistribution::Linear;
		else if (data == "Quadratic")
			value = ThicknessDistribution::Quadratic;
		else
			throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
	}

	void adl_serializer<ThicknessEvolution>::from_json(const json& data, ThicknessEvolution& value)
	{
		value = ThicknessEvolution{
			data.at("distribution").get<ThicknessEvolutionDistribution>(),
			data.at("speed")
		};
	}

	void adl_serializer<PathImage>::from_json(const json& data, PathImage& value)
	{
		value = PathImage{
			data.at("imageId"),
			JsonTools::parseOptional<float>(data.at("repeatStretch"))
		};
	}

	void adl_serializer<TimeRange>::from_json(const json& data, TimeRange& value)
	{
		value = TimeRange{
			data.at("spawnTime"),
			data.at("duration")
		};
	}

	void adl_serializer<MotionStateInheritance>::from_json(const json& data, MotionStateInheritance& value)
	{
		value = MotionStateInheritance{
			data.at("position"),
			data.at("linearVelocityFactor"),
			data.at("position"),
			data.at("angularVelocityFactor")
		};
	}

	void adl_serializer<MotionState>::from_json(const json& data, MotionState& value)
	{
		glm::vec3 eulerAngles = data.at("rotation").get<JsonTypes::Vec3>().value;
		glm::quat rotation = JsonTools::eulerAnglesToQuaternion(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));

		value = MotionState{
			data.at("position").get<JsonTypes::Vec3>().value,
			data.at("linearVelocity").get<JsonTypes::Vec3>().value,
			rotation,
			data.at("angularVelocity").get<JsonTypes::Vec3>().value
		};
	}

	void adl_serializer<ParticleEmitterSpawnContext>::from_json(const json& data, ParticleEmitterSpawnContext& value)
	{
		value = ParticleEmitterSpawnContext{
			data.at("emitterDescriptorId"),
			data.at("timeRange").get<TimeRange>(),
			data.at("initialMotionState").get<MotionState>(),
			data.at("forceFieldIds").get<std::vector<unsigned int>>(),
			data.at("motionBehaviorIds").get<std::vector<unsigned int>>()
		};
	}

	void adl_serializer<PeriodicSpawnTriggerContext>::from_json(const json& data, PeriodicSpawnTriggerContext& value)
	{
		value = PeriodicSpawnTriggerContext{
			data.at("emitterSpawnContext").get<ParticleEmitterSpawnContext>(),
			data.at("interval")
		};
	}

	void adl_serializer<PathConfiguration>::from_json(const json& data, PathConfiguration& value)
	{
		value = PathConfiguration{
			data.at("startThickness"),
			data.at("endThickness"),
			JsonTools::parseOptional<float>(data.at("lifetime")),
			JsonTools::parseOptional<LifetimeFade>(data.at("lifetimeFade")),
			data.at("appendParticleColor"),
			JsonTools::wrapperToType<Color>(data.at("colorGradient").get<std::vector<JsonTypes::Color>>()),
			JsonTools::parseOptional<std::vector<float>>(data.at("colorStart")),
			data.at("colorInterpolation").get<ColorInterpolation>(),
			data.at("thicknessDistribution").get<ThicknessDistribution>(),
			JsonTools::parseOptional<ThicknessEvolution>(data.at("thicknessEvolution")),
			JsonTools::parseOptional<PathImage>(data.at("image"))
		};
	}

	void adl_serializer<TrailConfiguration>::from_json(const json& data, TrailConfiguration& value)
	{
		value = TrailConfiguration{
			data.at("persistenceLifetime"),
			data.at("minimumSpawnDistance"),
			JsonTools::parseOptional<float>(data.at("maximumSpawnTime")),
			JsonTools::parseOptional<unsigned int>(data.at("maximumSegmentCount")),
			data.at("pathConfiguration").get<PathConfiguration>()
		};
	}

	void adl_serializer<RibbonConfiguration>::from_json(const json& data, RibbonConfiguration& value)
	{
		value = RibbonConfiguration{
			data.at("pathConfiguration").get<PathConfiguration>(),
			data.at("particleLinkerId"),
			data.at("ribbonGeneratorId"),
			data.at("ribbonPointCount")
		};
	}

	void adl_serializer<SpawnTriggerDescriptor>::from_json(const json& data, SpawnTriggerDescriptor& value)
	{
		value = SpawnTriggerDescriptor{
			data.at("maximumRecursionDepth"),
			JsonTools::parseOptional<ParticleEmitterSpawnContext>(data.at("spawnEmitterSpawnContext")),
			JsonTools::parseOptional<ParticleEmitterSpawnContext>(data.at("deathEmitterSpawnContext")),
			JsonTools::parseOptional<PeriodicSpawnTriggerContext>(data.at("periodicEmitterSpawnContext"))
		};
	}

	void adl_serializer<RenderType>::from_json(const json& data, RenderType& value)
	{
		if (data == "Billboard")
			value = RenderType::Billboard;
		else if (data == "Mesh")
			value = RenderType::Mesh;
		else
			throw std::runtime_error("Invalid render type : '" + std::string(data) + "'");
	}

	void adl_serializer<BillboardRenderConfiguration>::from_json(const json& data, BillboardRenderConfiguration& value)
	{
		value = BillboardRenderConfiguration{
			JsonTools::parseOptional<unsigned int>(data.at("spriteSheetId"))
		};
	}

	void adl_serializer<MeshRenderConfiguration>::from_json(const json& data, MeshRenderConfiguration& value)
	{
		value = MeshRenderConfiguration{
			data.at("modelId"),
			JsonTools::parseOptional<unsigned int>(data.at("imageId"))
		};
	}

	void adl_serializer<RenderConfiguration>::from_json(const json& data, RenderConfiguration& value)
	{
		RenderType renderType = data.at("renderType").get<RenderType>();
		std::variant<BillboardRenderConfiguration, MeshRenderConfiguration> configurationData;

		switch (renderType)
		{
		case RenderType::Billboard:
			configurationData = data.at("configurationData").get<BillboardRenderConfiguration>();
			break;
		case RenderType::Mesh:
			configurationData = data.at("configurationData").get<MeshRenderConfiguration>();
			break;
		}

		value = RenderConfiguration{
			renderType,
			configurationData
		};
	}

	void adl_serializer<std::unique_ptr<SpawnShape>>::from_json(const json& data, std::unique_ptr<SpawnShape>& value)
	{
		value = JsonLoader::getSpawnShapeFactory().instantiate(data);
	}

	void adl_serializer<std::unique_ptr<ParticleSpawner>>::from_json(const json& data, std::unique_ptr<ParticleSpawner>& value)
	{
		if (data.contains("spawnShape"))
		{
			value = std::make_unique<ParticleSpawner>(
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Color, JsonTypes::Color>(data.at("colorAttributeGenerator")),
				data.at("spawnShape").get<std::unique_ptr<SpawnShape>>(),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Rotation, JsonTypes::Vec3>(data.at("rotationAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Scale, JsonTypes::Vec3>(data.at("scaleAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<LinearVelocity, JsonTypes::Vec3>(data.at("linearVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<AngularVelocity, JsonTypes::Vec3>(data.at("angularVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Phase, float>(data.at("phaseAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Lifetime, float>(data.at("lifetimeAttributeGenerator")),
				data.at("maximumParticleLifetime")
			);
		}
		else
		{
			value = std::make_unique<ParticleSpawner>(
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Color, JsonTypes::Color>(data.at("colorAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Position, JsonTypes::Vec3>(data.at("positionAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Rotation, JsonTypes::Vec3>(data.at("rotationAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Scale, JsonTypes::Vec3>(data.at("scaleAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<LinearVelocity, JsonTypes::Vec3>(data.at("linearVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<AngularVelocity, JsonTypes::Vec3>(data.at("angularVelocityAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Phase, float>(data.at("phaseAttributeGenerator")),
				JsonLoaderAttributeGenerator::parseAttributeGenerator<Lifetime, float>(data.at("lifetimeAttributeGenerator")),
				data.at("maximumParticleLifetime")
			);
		}
	}

	void adl_serializer<Image>::from_json(const json& data, Image& value)
	{
		Image image;
		image.loadFromFile(data.at("path"));

		value = image;
	}

	void adl_serializer<Model>::from_json(const json& data, Model& value)
	{
		Model model;
		model.loadFromFile(data.at("path"));

		value = model;
	}

	void adl_serializer<SpriteSheetDescriptor>::from_json(const json& data, SpriteSheetDescriptor& value)
	{
		value = SpriteSheetDescriptor{
			data.at("imageId"),
			data.at("frameCount"),
			data.at("rowFrameCount"),
			data.at("frameWidth"),
			data.at("frameHeight"),
			data.at("animationSpeed")
		};
	}

	void adl_serializer<ParticleEffectDescriptor>::from_json(const json& data, ParticleEffectDescriptor& value)
	{
		value = ParticleEffectDescriptor{
			data.at("emitterSpawnContexts").get<std::vector<ParticleEmitterSpawnContext>>()
		};
	}

	void adl_serializer<ParticleEmitterDescriptor>::from_json(const json& data, ParticleEmitterDescriptor& value)
	{
		value = ParticleEmitterDescriptor{
			data.at("poolId"),
			data.at("particleSpawnerId"),
			data.at("emissionPatternId"),
			data.at("motionStateInheritance").get<MotionStateInheritance>(),
			JsonTools::parseOptional<TrailConfiguration>(data.at("trailConfiguration")),
			JsonTools::parseOptional<RibbonConfiguration>(data.at("ribbonConfiguration")),
			JsonTools::parseOptional<SpawnTriggerDescriptor>(data.at("spawnTriggerDescriptor")),
			data.at("renderConfiguration").get<RenderConfiguration>(),
			data.at("forceFieldIds").get<std::vector<unsigned int>>(),
			data.at("motionBehaviorIds").get<std::vector<unsigned int>>(),
			data.at("visualBehaviorIds").get<std::vector<unsigned int>>()
		};
	}
}