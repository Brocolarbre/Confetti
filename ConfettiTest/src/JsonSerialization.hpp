#pragma once

#include <Confetti/Simulation/Registry/AssetRegistry.hpp>
#include <Confetti/Behavior/Force/SpatialInfluence.hpp>
#include <Confetti/Behavior/Visual/ParticleTime.hpp>
#include <Confetti/Tool/RandomNumberGenerator.hpp>

#include <Confetti/Emission/ParticleSpawner.hpp>

#include <Confetti/Emission/AttributeGenerator/BinaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/UnaryAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/ConstantAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/InterpolatedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/LinearAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/RandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Generic/WeightedRandomSetAttributeGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/NormalLinearVelocityGenerator.hpp>
#include <Confetti/Emission/AttributeGenerator/Specialized/RandomNormalOffsetPositionGenerator.hpp>

#include <Confetti/Emission/SpawnShape/CircleSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/ConeVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/CylinderVolumeSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/DiskSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereSpawnShape.hpp>
#include <Confetti/Emission/SpawnShape/SphereVolumeSpawnShape.hpp>

#include <Confetti/Simulation/Link/LinkRule/AgeSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ColorSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/ConnectionLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/DistanceLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/PhaseSimilarityLinkRule.hpp>
#include <Confetti/Simulation/Link/LinkRule/VelocitySimilarityLinkRule.hpp>

#include <LineWeaver/Interpolation/BezierInterpolator.hpp>
#include <LineWeaver/Interpolation/BSplineInterpolator.hpp>
#include <LineWeaver/Interpolation/CatmullRomInterpolator.hpp>
#include <LineWeaver/Interpolation/HermiteInterpolator.hpp>
#include <LineWeaver/Interpolation/LinearInterpolator.hpp>

#include <LineWeaver/Easing/EaseCurve.hpp>
#include <LineWeaver/Easing/EaseInBack.hpp>
#include <LineWeaver/Easing/EaseInBounce.hpp>
#include <LineWeaver/Easing/EaseInCircular.hpp>
#include <LineWeaver/Easing/EaseInCubic.hpp>
#include <LineWeaver/Easing/EaseInElastic.hpp>
#include <LineWeaver/Easing/EaseInExponential.hpp>
#include <LineWeaver/Easing/EaseInOutBack.hpp>
#include <LineWeaver/Easing/EaseInOutBounce.hpp>
#include <LineWeaver/Easing/EaseInOutCircular.hpp>
#include <LineWeaver/Easing/EaseInOutCubic.hpp>
#include <LineWeaver/Easing/EaseInOutElastic.hpp>
#include <LineWeaver/Easing/EaseInOutExponential.hpp>
#include <LineWeaver/Easing/EaseInOutQuadratic.hpp>
#include <LineWeaver/Easing/EaseInOutQuartic.hpp>
#include <LineWeaver/Easing/EaseInOutQuintic.hpp>
#include <LineWeaver/Easing/EaseInOutSine.hpp>
#include <LineWeaver/Easing/EaseInQuadratic.hpp>
#include <LineWeaver/Easing/EaseInQuartic.hpp>
#include <LineWeaver/Easing/EaseInQuintic.hpp>
#include <LineWeaver/Easing/EaseInSine.hpp>
#include <LineWeaver/Easing/EaseLinear.hpp>
#include <LineWeaver/Easing/EaseOutBack.hpp>
#include <LineWeaver/Easing/EaseOutBounce.hpp>
#include <LineWeaver/Easing/EaseOutCircular.hpp>
#include <LineWeaver/Easing/EaseOutCubic.hpp>
#include <LineWeaver/Easing/EaseOutElastic.hpp>
#include <LineWeaver/Easing/EaseOutExponential.hpp>
#include <LineWeaver/Easing/EaseOutQuadratic.hpp>
#include <LineWeaver/Easing/EaseOutQuartic.hpp>
#include <LineWeaver/Easing/EaseOutQuintic.hpp>
#include <LineWeaver/Easing/EaseOutSine.hpp>
#include <LineWeaver/Easing/EaseSmootherstep.hpp>
#include <LineWeaver/Easing/EaseSmoothstep.hpp>

#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

struct Color
{
	glm::vec4 value;
};

struct Vec3
{
	glm::vec3 value;
};

struct Vec2
{
	glm::vec2 value;
};

static glm::quat eulerAnglesToQuaternion(const glm::vec3& eulerAngles)
{
	return glm::quat(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));
}

static std::vector<glm::quat> eulerAnglesToQuaternion(const std::vector<glm::vec3>& eulerAngles)
{
	std::vector<glm::quat> rotations;
	rotations.reserve(eulerAngles.size());

	for (const glm::vec3& rotation : eulerAngles)
		rotations.push_back(eulerAnglesToQuaternion(rotation));

	return rotations;
}

static std::vector<cft::WeightedValue<glm::quat>> eulerAnglesToQuaternion(const std::vector<cft::WeightedValue<glm::vec3>>& eulerAngles)
{
	std::vector<cft::WeightedValue<glm::quat>> rotations;
	rotations.reserve(eulerAngles.size());

	for (const cft::WeightedValue<glm::vec3>& rotation : eulerAngles)
		rotations.push_back(cft::WeightedValue<glm::quat>{ eulerAnglesToQuaternion(rotation.value), rotation.weight });

	return rotations;
}

template <typename T, typename WrapperType>
static std::vector<T> wrapperToType(const std::vector<WrapperType>& wrapper);

template <typename T, typename WrapperType>
static std::vector<cft::WeightedValue<T>> wrapperToType(const std::vector<cft::WeightedValue<WrapperType>>& wrapper);

namespace nlohmann
{
	template<>
	struct adl_serializer<Color>
	{
		static void from_json(const json& data, Color& value)
		{
			value.value = glm::vec4(data["r"], data["g"], data["b"], data["a"]);
		}
	};

	template<>
	struct adl_serializer<Vec3>
	{
		static void from_json(const json& data, Vec3& value)
		{
			value.value = glm::vec3(data["x"], data["y"], data["z"]);
		}
	};

	template<>
	struct adl_serializer<Vec2>
	{
		static void from_json(const json& data, Vec2& value)
		{
			value.value = glm::vec2(data["x"], data["y"]);
		}
	};

	template<>
	struct adl_serializer<lw::Point>
	{
		static void from_json(const json& data, lw::Point& value)
		{
			value = lw::Point(data["x"], data["y"], data["z"]);
		}
	};

	template<>
	struct adl_serializer<cft::Falloff>
	{
		static void from_json(const json& data, cft::Falloff& value)
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
	};

	template<>
	struct adl_serializer<cft::SpatialInfluence>
	{
		static cft::SpatialInfluence from_json(const json& data)
		{
			return cft::SpatialInfluence{
				data["origin"].get<Vec3>().value,
				data["radius"],
				data["falloff"].get<cft::Falloff>()
			};
		}
	};

	template<>
	struct adl_serializer<std::unique_ptr<lw::Interpolator>>
	{
		static void from_json(const json& data, std::unique_ptr<lw::Interpolator>& value)
		{
			std::string type = data["type"];

			if (type == "Bezier")
				value = std::make_unique<lw::BezierInterpolator>(data["pointsPerSegment"]);
			else if (type == "BSpline")
				value = std::make_unique<lw::BSplineInterpolator>(data["interpolator"].get<std::unique_ptr<lw::Interpolator>>());
			else if (type == "CatmullRom")
				value = std::make_unique<lw::CatmullRomInterpolator>();
			else if (type == "Hermite")
				value = std::make_unique<lw::HermiteInterpolator>();
			else if (type == "Linear")
				value = std::make_unique<lw::LinearInterpolator>();
			else
				throw std::runtime_error("Invalid interpolator type : '" + type + "'");
		}
	};

	template<>
	struct adl_serializer<std::unique_ptr<lw::Easing>>
	{
		static void from_json(const json& data, std::unique_ptr<lw::Easing>& value)
		{
			std::string type = data["type"];

			if (type == "Curve")
				value = std::make_unique<lw::EaseCurve>(data["interpolator"].get<std::unique_ptr<lw::Interpolator>>(), data["path"].get<std::vector<lw::Point>>());
			else if (type == "InBack")
				value = std::make_unique<lw::EaseInBack>();
			else if (type == "InBounce")
				value = std::make_unique<lw::EaseInBounce>();
			else if (type == "InCircular")
				value = std::make_unique<lw::EaseInCircular>();
			else if (type == "InCubic")
				value = std::make_unique<lw::EaseInCubic>();
			else if (type == "InElastic")
				value = std::make_unique<lw::EaseInElastic>();
			else if (type == "InExponential")
				value = std::make_unique<lw::EaseInExponential>();
			else if (type == "InOutBack")
				value = std::make_unique<lw::EaseInOutBack>();
			else if (type == "InOutBounce")
				value = std::make_unique<lw::EaseInOutBounce>();
			else if (type == "InOutCircular")
				value = std::make_unique<lw::EaseInOutCircular>();
			else if (type == "InOutCubic")
				value = std::make_unique<lw::EaseInOutCubic>();
			else if (type == "InOutElastic")
				value = std::make_unique<lw::EaseInOutElastic>();
			else if (type == "InOutExponential")
				value = std::make_unique<lw::EaseInOutExponential>();
			else if (type == "InOutQuadratic")
				value = std::make_unique<lw::EaseInOutQuadratic>();
			else if (type == "InOutQuartic")
				value = std::make_unique<lw::EaseInOutQuartic>();
			else if (type == "InOutQuintic")
				value = std::make_unique<lw::EaseInOutQuintic>();
			else if (type == "InOutSine")
				value = std::make_unique<lw::EaseInOutSine>();
			else if (type == "InQuadratic")
				value = std::make_unique<lw::EaseInQuadratic>();
			else if (type == "InQuartic")
				value = std::make_unique<lw::EaseInQuartic>();
			else if (type == "InQuintic")
				value = std::make_unique<lw::EaseInQuintic>();
			else if (type == "InSine")
				value = std::make_unique<lw::EaseInSine>();
			else if (type == "Linear")
				value = std::make_unique<lw::EaseLinear>();
			else if (type == "OutBack")
				value = std::make_unique<lw::EaseOutBack>();
			else if (type == "OutBounce")
				value = std::make_unique<lw::EaseOutBounce>();
			else if (type == "OutCircular")
				value = std::make_unique<lw::EaseOutCircular>();
			else if (type == "OutCubic")
				value = std::make_unique<lw::EaseOutCubic>();
			else if (type == "OutElastic")
				value = std::make_unique<lw::EaseOutElastic>();
			else if (type == "OutExponential")
				value = std::make_unique<lw::EaseOutExponential>();
			else if (type == "OutQuadratic")
				value = std::make_unique<lw::EaseOutQuadratic>();
			else if (type == "OutQuartic")
				value = std::make_unique<lw::EaseOutQuartic>();
			else if (type == "OutQuintic")
				value = std::make_unique<lw::EaseOutQuintic>();
			else if (type == "OutSine")
				value = std::make_unique<lw::EaseOutSine>();
			else if (type == "Smootherstep")
				value = std::make_unique<lw::EaseSmootherstep>();
			else if (type == "Smoothstep")
				value = std::make_unique<lw::EaseSmoothstep>();
			else
				throw std::runtime_error("Invalid easing type : '" + type + "'");
		}
	};

	template<>
	struct adl_serializer<cft::ParticleTime::Space>
	{
		static void from_json(const json& data, cft::ParticleTime::Space& value)
		{
			if (data == "Absolute")
				value = cft::ParticleTime::Space::Absolute;
			else if (data == "Normalized")
				value = cft::ParticleTime::Space::Normalized;
			else
				throw std::runtime_error("Invalid particle time space type : '" + std::string(data) + "'");
		}
	};

	template<>
	struct adl_serializer<cft::ParticleTime>
	{
		static void from_json(const json& data, cft::ParticleTime& value)
		{
			value = cft::ParticleTime{
				data["value"],
				data["space"].get<cft::ParticleTime::Space>()
			};
		}
	};

	template<>
	struct adl_serializer<std::unique_ptr<cft::LinkRule>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::LinkRule>& value)
		{
			std::string type = data["type"];

			if (type == "AgeSimilarity")
				value = std::make_unique<cft::AgeSimilarityLinkRule>(data["threshold"]);
			else if (type == "ColorSimilarity")
				value = std::make_unique<cft::ColorSimilarityLinkRule>(data["threshold"]);
			else if (type == "Connection")
				value = std::make_unique<cft::ConnectionLinkRule>(data["maximumConnectionCount"]);
			else if (type == "Distance")
				value = std::make_unique<cft::DistanceLinkRule>(data["minimumDistance"], data["maximumDistance"]);
			else if (type == "PhaseSimilarity")
				value = std::make_unique<cft::PhaseSimilarityLinkRule>(data["threshold"]);
			else if (type == "VelocitySimilarity")
				value = std::make_unique<cft::VelocitySimilarityLinkRule>(data["threshold"]);
			else
				throw std::runtime_error("Invalid link rule type : '" + type + "'");
		}
	};

	template<>
	struct adl_serializer<cft::ThicknessEvolutionDistribution>
	{
		static void from_json(const json& data, cft::ThicknessEvolutionDistribution& value)
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
	};

	template<>
	struct adl_serializer<cft::LifetimeFade>
	{
		static void from_json(const json& data, cft::LifetimeFade& value)
		{
			value = cft::LifetimeFade{
				data["start"],
				data["end"]
			};
		}
	};

	template<>
	struct adl_serializer<cft::ColorInterpolation>
	{
		static void from_json(const json& data, cft::ColorInterpolation& value)
		{
			if (data == "Constant")
				value = cft::ColorInterpolation::Constant;
			else if (data == "Linear")
				value = cft::ColorInterpolation::Linear;
			else
				throw std::runtime_error("Invalid color interpolation type : '" + std::string(data) + "'");
		}
	};

	template<>
	struct adl_serializer<cft::ThicknessDistribution>
	{
		static void from_json(const json& data, cft::ThicknessDistribution& value)
		{
			if (data == "Linear")
				value = cft::ThicknessDistribution::Linear;
			else if (data == "Quadratic")
				value = cft::ThicknessDistribution::Quadratic;
			else
				throw std::runtime_error("Invalid thickness distribution type : '" + std::string(data) + "'");
		}
	};

	template<>
	struct adl_serializer<cft::ThicknessEvolution>
	{
		static void from_json(const json& data, cft::ThicknessEvolution& value)
		{
			value = cft::ThicknessEvolution{
				data["distribution"].get<cft::ThicknessEvolutionDistribution>(),
				data["speed"]
			};
		}
	};

	template<>
	struct adl_serializer<cft::PathImage>
	{
		static void from_json(const json& data, cft::PathImage& value)
		{
			value = cft::PathImage{
				data["imageId"],
				data["repeatStretch"].is_null() ? std::nullopt : std::make_optional<float>(data["repeatStretch"])
			};
		}
	};

	template<>
	struct adl_serializer<cft::TimeRange>
	{
		static void from_json(const json& data, cft::TimeRange& value)
		{
			value = cft::TimeRange{
				data["spawnTime"],
				data["duration"]
			};
		}
	};

	template<>
	struct adl_serializer<cft::MotionState>
	{
		static void from_json(const json& data, cft::MotionState& value)
		{
			glm::vec3 eulerAngles = data["rotation"].get<Vec3>().value;
			glm::quat rotation = eulerAnglesToQuaternion(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));

			value = cft::MotionState{
				data["position"].get<Vec3>().value,
				data["linearVelocity"].get<Vec3>().value,
				rotation,
				data["angularVelocity"].get<Vec3>().value
			};
		}
	};

	template<>
	struct adl_serializer<cft::ParticleEmitterSpawnContext>
	{
		static void from_json(const json& data, cft::ParticleEmitterSpawnContext& value)
		{
			value = cft::ParticleEmitterSpawnContext{
				data["emitterDescriptorId"],
				data["timeRange"].get<cft::TimeRange>(),
				data["initialMotionState"].get<cft::MotionState>(),
				data["forceFieldIds"].get<std::vector<unsigned int>>(),
				data["motionBehaviorIds"].get<std::vector<unsigned int>>()
			};
		}
	};

	template<>
	struct adl_serializer<cft::PeriodicSpawnTriggerContext>
	{
		static void from_json(const json& data, cft::PeriodicSpawnTriggerContext& value)
		{
			value = cft::PeriodicSpawnTriggerContext{
				data["emitterSpawnContext"].get<cft::ParticleEmitterSpawnContext>(),
				data["interval"]
			};
		}
	};

	template<>
	struct adl_serializer<cft::PathConfiguration>
	{
		static void from_json(const json& data, cft::PathConfiguration& value)
		{
			value = cft::PathConfiguration{
				data["startThickness"],
				data["endThickness"],
				data["lifetime"].is_null() ? std::nullopt : std::make_optional<float>(data["lifetime"]),
				data["lifetimeFade"].is_null() ? std::nullopt : std::make_optional<cft::LifetimeFade>(data["lifetimeFade"].get<cft::LifetimeFade>()),
				data["appendParticleColor"],
				wrapperToType<glm::vec4>(data["colorGradient"].get<std::vector<Color>>()),
				data["colorStart"].is_null() ? std::nullopt : std::make_optional<std::vector<float>>(data["colorStart"].get<std::vector<float>>()),
				data["colorInterpolation"].get<cft::ColorInterpolation>(),
				data["thicknessDistribution"].get<cft::ThicknessDistribution>(),
				data["thicknessEvolution"].is_null() ? std::nullopt : std::make_optional<cft::ThicknessEvolution>(data["thicknessEvolution"].get<cft::ThicknessEvolution>()),
				data["pathImage"].is_null() ? std::nullopt : std::make_optional<cft::PathImage>(data["pathImage"].get<cft::PathImage>())
			};
		}
	};

	template<>
	struct adl_serializer<cft::TrailConfiguration>
	{
		static void from_json(const json& data, cft::TrailConfiguration& value)
		{
			value = cft::TrailConfiguration{
				data["persistenceLifetime"],
				data["minimumSpawnDistance"],
				data["maximumSpawnTime"].is_null() ? std::nullopt : std::make_optional<float>(data["maximumSpawnTime"]),
				data["maximumSegmentCount"].is_null() ? std::nullopt : std::make_optional<unsigned int>(data["maximumSegmentCount"]),
				data["pathConfiguration"].get<cft::PathConfiguration>()
			};
		}
	};

	template<>
	struct adl_serializer<cft::RibbonConfiguration>
	{
		static void from_json(const json& data, cft::RibbonConfiguration& value)
		{
			value = cft::RibbonConfiguration{
				data["pathConfiguration"].get<cft::PathConfiguration>(),
				data["particleLinkerId"],
				data["ribbonGeneratorId"],
				data["ribbonPointCount"]
			};
		}
	};

	template<>
	struct adl_serializer<cft::SpawnTriggerDescriptor>
	{
		static void from_json(const json& data, cft::SpawnTriggerDescriptor& value)
		{
			value = cft::SpawnTriggerDescriptor{
				data["maximumRecursionDepth"],
				data["spawnEmitterSpawnContext"].is_null() ? std::nullopt : std::make_optional<cft::ParticleEmitterSpawnContext>(data["spawnEmitterSpawnContext"].get<cft::ParticleEmitterSpawnContext>()),
				data["deathEmitterSpawnContext"].is_null() ? std::nullopt : std::make_optional<cft::ParticleEmitterSpawnContext>(data["deathEmitterSpawnContext"].get<cft::ParticleEmitterSpawnContext>()),
				data["periodicEmitterSpawnContext"].is_null() ? std::nullopt : std::make_optional<cft::PeriodicSpawnTriggerContext>(data["periodicEmitterSpawnContext"].get<cft::PeriodicSpawnTriggerContext>())
			};
		}
	};

	template<>
	struct adl_serializer<cft::RenderType>
	{
		static void from_json(const json& data, cft::RenderType& value)
		{
			if (data == "Billboard")
				value = cft::RenderType::Billboard;
			else if (data == "Mesh")
				value = cft::RenderType::Mesh;
			else
				throw std::runtime_error("Invalid render type : '" + std::string(data) + "'");
		}
	};

	template<>
	struct adl_serializer<cft::BillboardRenderConfiguration>
	{
		static void from_json(const json& data, cft::BillboardRenderConfiguration& value)
		{
			value = cft::BillboardRenderConfiguration{
				data["spriteSheetId"].is_null() ? std::nullopt : std::make_optional<unsigned int>(data["spriteSheetId"])
			};
		}
	};

	template<>
	struct adl_serializer<cft::MeshRenderConfiguration>
	{
		static void from_json(const json& data, cft::MeshRenderConfiguration& value)
		{
			value = cft::MeshRenderConfiguration{
				data["modelId"],
				data["imageId"].is_null() ? std::nullopt : std::make_optional<unsigned int>(data["imageId"])
			};
		}
	};

	template<>
	struct adl_serializer<cft::RenderConfiguration>
	{
		static void from_json(const json& data, cft::RenderConfiguration& value)
		{
			cft::RenderType renderType = data["renderType"].get<cft::RenderType>();
			std::variant<cft::BillboardRenderConfiguration, cft::MeshRenderConfiguration> configurationData;

			switch (renderType)
			{
			case cft::RenderType::Billboard:
				configurationData = data["configurationData"].get<cft::BillboardRenderConfiguration>();
				break;
			case cft::RenderType::Mesh:
				configurationData = data["configurationData"].get<cft::MeshRenderConfiguration>();
				break;
			}

			value = cft::RenderConfiguration{
				renderType,
				configurationData
			};
		}
	};

	template<>
	struct adl_serializer<std::unique_ptr<cft::SpawnShape>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::SpawnShape>& value)
		{
			std::string type = data["type"];

			if (type == "Circle")
				value = std::make_unique<cft::CircleSpawnShape>(data["radius"], data["axis"].get<Vec3>().value);
			else if (type == "Cone")
				value = std::make_unique<cft::ConeSpawnShape>(data["height"], data["radius"], data["axis"].get<Vec3>().value);
			else if (type == "ConeVolume")
				value = std::make_unique<cft::ConeVolumeSpawnShape>(data["height"], data["radius"], data["axis"].get<Vec3>().value);
			else if (type == "Cylinder")
				value = std::make_unique<cft::CylinderSpawnShape>(data["height"], data["radius"], data["axis"].get<Vec3>().value);
			else if (type == "CylinderVolume")
				value = std::make_unique<cft::CylinderVolumeSpawnShape>(data["height"], data["radius"], data["axis"].get<Vec3>().value);
			else if (type == "Disk")
				value = std::make_unique<cft::DiskSpawnShape>(data["radius"], data["axis"].get<Vec3>().value);
			else if (type == "Sphere")
				value = std::make_unique<cft::SphereSpawnShape>(data["radius"]);
			else if (type == "SphereVolume")
				value = std::make_unique<cft::SphereVolumeSpawnShape>(data["radius"]);
			else
				throw std::runtime_error("Invalid spanw shape type : '" + type + "'");
		}
	};

	template<typename T>
	struct adl_serializer<cft::WeightedValue<T>>
	{
		static void from_json(const json& data, cft::WeightedValue<T>& value)
		{
			value = cft::WeightedValue<T>{
				data["value"].get<T>(),
				data["weight"]
			};
		}
	};
}

template<typename T, typename WrapperType>
inline std::vector<T> wrapperToType(const std::vector<WrapperType>& wrapper)
{
	std::vector<T> type;
	type.reserve(wrapper.size());

	for (const WrapperType& wrapperValue : wrapper)
		type.push_back(wrapperValue.value);

	return type;
}

template<typename T, typename WrapperType>
inline T wrapperToType(const WrapperType& wrapper)
{
	return wrapper.value;
}

template <typename T, typename WrapperType>
inline std::vector<cft::WeightedValue<T>> wrapperToType(const std::vector<cft::WeightedValue<WrapperType>>& wrapper)
{
	std::vector<cft::WeightedValue<T>> type;
	type.reserve(wrapper.size());

	for (const cft::WeightedValue<WrapperType>& wrapperValue : wrapper)
		type.push_back(cft::WeightedValue<T>{ wrapperToType<T>(wrapperValue.value), wrapperValue.weight });

	return type;
}