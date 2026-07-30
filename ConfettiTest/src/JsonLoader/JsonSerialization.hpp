#pragma once

#include "JsonTypes.hpp"
#include "JsonTools.hpp"

#include <Confetti/Simulation/Registry/AssetRegistry.hpp>
#include <Confetti/Behavior/Force/SpatialInfluence.hpp>
#include <Confetti/Behavior/Visual/ParticleTime.hpp>
#include <Confetti/Tool/RandomNumberGenerator.hpp>

#include <Confetti/Emission/ParticleSpawner.hpp>

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

#include <stdexcept>
#include <string>

namespace nlohmann
{
	template <>
	struct adl_serializer<Color>
	{
		static void from_json(const json& data, Color& value)
		{
			value.value = glm::vec4(data.at("r"), data.at("g"), data.at("b"), data.at("a"));
		}
	};

	template <>
	struct adl_serializer<Vec3>
	{
		static void from_json(const json& data, Vec3& value)
		{
			value.value = glm::vec3(data.at("x"), data.at("y"), data.at("z"));
		}
	};

	template <>
	struct adl_serializer<Vec2>
	{
		static void from_json(const json& data, Vec2& value)
		{
			value.value = glm::vec2(data.at("x"), data.at("y"));
		}
	};

	template <>
	struct adl_serializer<lw::Point>
	{
		static void from_json(const json& data, lw::Point& value)
		{
			value = lw::Point(data.at("x"), data.at("y"), data.at("z"));
		}
	};

	template <>
	struct adl_serializer<glm::vec4>
	{
		static void from_json(const json& data, glm::vec4& value)
		{
			value = glm::vec4(data.at("x"), data.at("y"), data.at("z"), data.at("w"));
		}
	};

	template <>
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

	template <>
	struct adl_serializer<cft::SpatialInfluence>
	{
		static cft::SpatialInfluence from_json(const json& data)
		{
			return cft::SpatialInfluence{
				data.at("origin").get<Vec3>().value,
				data.at("radius"),
				data.at("falloff").get<cft::Falloff>()
			};
		}
	};

	template <>
	struct adl_serializer<std::unique_ptr<lw::Interpolator>>
	{
		static void from_json(const json& data, std::unique_ptr<lw::Interpolator>& value)
		{
			std::string type = data.at("type");

			if (type == "Bezier")
				value = std::make_unique<lw::BezierInterpolator>(data.at("pointsPerSegment"));
			else if (type == "BSpline")
				value = std::make_unique<lw::BSplineInterpolator>(data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>());
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

	template <>
	struct adl_serializer<std::unique_ptr<lw::Easing>>
	{
		static void from_json(const json& data, std::unique_ptr<lw::Easing>& value)
		{
			std::string type = data.at("type");

			if (type == "Curve")
				value = std::make_unique<lw::EaseCurve>(data.at("interpolator").get<std::unique_ptr<lw::Interpolator>>(), data.at("path").get<std::vector<lw::Point>>());
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

	template <>
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

	template <>
	struct adl_serializer<cft::ParticleTime>
	{
		static void from_json(const json& data, cft::ParticleTime& value)
		{
			value = cft::ParticleTime{
				data.at("value"),
				data.at("space").get<cft::ParticleTime::Space>()
			};
		}
	};

	template <>
	struct adl_serializer<std::unique_ptr<cft::LinkRule>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::LinkRule>& value)
		{
			std::string type = data.at("type");

			if (type == "AgeSimilarity")
				value = std::make_unique<cft::AgeSimilarityLinkRule>(data.at("threshold"));
			else if (type == "ColorSimilarity")
				value = std::make_unique<cft::ColorSimilarityLinkRule>(data.at("threshold"));
			else if (type == "Connection")
				value = std::make_unique<cft::ConnectionLinkRule>(data.at("maximumConnectionCount"));
			else if (type == "Distance")
				value = std::make_unique<cft::DistanceLinkRule>(data.at("minimumDistance"), data.at("maximumDistance"));
			else if (type == "PhaseSimilarity")
				value = std::make_unique<cft::PhaseSimilarityLinkRule>(data.at("threshold"));
			else if (type == "VelocitySimilarity")
				value = std::make_unique<cft::VelocitySimilarityLinkRule>(data.at("threshold"));
			else
				throw std::runtime_error("Invalid link rule type : '" + type + "'");
		}
	};

	template <>
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

	template <>
	struct adl_serializer<cft::LifetimeFade>
	{
		static void from_json(const json& data, cft::LifetimeFade& value)
		{
			value = cft::LifetimeFade{
				data.at("start"),
				data.at("end")
			};
		}
	};

	template <>
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

	template <>
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

	template <>
	struct adl_serializer<cft::ThicknessEvolution>
	{
		static void from_json(const json& data, cft::ThicknessEvolution& value)
		{
			value = cft::ThicknessEvolution{
				data.at("distribution").get<cft::ThicknessEvolutionDistribution>(),
				data.at("speed")
			};
		}
	};

	template <>
	struct adl_serializer<cft::PathImage>
	{
		static void from_json(const json& data, cft::PathImage& value)
		{
			value = cft::PathImage{
				data.at("imageId"),
				JsonTools::parseOptional<float>(data.at("repeatStretch"))
			};
		}
	};

	template <>
	struct adl_serializer<cft::TimeRange>
	{
		static void from_json(const json& data, cft::TimeRange& value)
		{
			value = cft::TimeRange{
				data.at("spawnTime"),
				data.at("duration")
			};
		}
	};

	template <>
	struct adl_serializer<cft::MotionState>
	{
		static void from_json(const json& data, cft::MotionState& value)
		{
			glm::vec3 eulerAngles = data.at("rotation").get<Vec3>().value;
			glm::quat rotation = JsonTools::eulerAnglesToQuaternion(glm::vec3(glm::radians(eulerAngles.x), glm::radians(eulerAngles.y), glm::radians(eulerAngles.z)));

			value = cft::MotionState{
				data.at("position").get<Vec3>().value,
				data.at("linearVelocity").get<Vec3>().value,
				rotation,
				data.at("angularVelocity").get<Vec3>().value
			};
		}
	};

	template <>
	struct adl_serializer<cft::ParticleEmitterSpawnContext>
	{
		static void from_json(const json& data, cft::ParticleEmitterSpawnContext& value)
		{
			value = cft::ParticleEmitterSpawnContext{
				data.at("emitterDescriptorId"),
				data.at("timeRange").get<cft::TimeRange>(),
				data.at("initialMotionState").get<cft::MotionState>(),
				data.at("forceFieldIds").get<std::vector<unsigned int>>(),
				data.at("motionBehaviorIds").get<std::vector<unsigned int>>()
			};
		}
	};

	template <>
	struct adl_serializer<cft::PeriodicSpawnTriggerContext>
	{
		static void from_json(const json& data, cft::PeriodicSpawnTriggerContext& value)
		{
			value = cft::PeriodicSpawnTriggerContext{
				data.at("emitterSpawnContext").get<cft::ParticleEmitterSpawnContext>(),
				data.at("interval")
			};
		}
	};

	template <>
	struct adl_serializer<cft::PathConfiguration>
	{
		static void from_json(const json& data, cft::PathConfiguration& value)
		{
			value = cft::PathConfiguration{
				data.at("startThickness"),
				data.at("endThickness"),
				JsonTools::parseOptional<float>(data.at("lifetime")),
				JsonTools::parseOptional<cft::LifetimeFade>(data.at("lifetimeFade")),
				data.at("appendParticleColor"),
				JsonTools::wrapperToType<cft::Color>(data.at("colorGradient").get<std::vector<Color>>()),
				JsonTools::parseOptional<std::vector<float>>(data.at("colorStart")),
				data.at("colorInterpolation").get<cft::ColorInterpolation>(),
				data.at("thicknessDistribution").get<cft::ThicknessDistribution>(),
				JsonTools::parseOptional<cft::ThicknessEvolution>(data.at("thicknessEvolution")),
				JsonTools::parseOptional<cft::PathImage>(data.at("pathImage"))
			};
		}
	};

	template <>
	struct adl_serializer<cft::TrailConfiguration>
	{
		static void from_json(const json& data, cft::TrailConfiguration& value)
		{
			value = cft::TrailConfiguration{
				data.at("persistenceLifetime"),
				data.at("minimumSpawnDistance"),
				JsonTools::parseOptional<float>(data.at("maximumSpawnTime")),
				JsonTools::parseOptional<unsigned int>(data.at("maximumSegmentCount")),
				data.at("pathConfiguration").get<cft::PathConfiguration>()
			};
		}
	};

	template <>
	struct adl_serializer<cft::RibbonConfiguration>
	{
		static void from_json(const json& data, cft::RibbonConfiguration& value)
		{
			value = cft::RibbonConfiguration{
				data.at("pathConfiguration").get<cft::PathConfiguration>(),
				data.at("particleLinkerId"),
				data.at("ribbonGeneratorId"),
				data.at("ribbonPointCount")
			};
		}
	};

	template <>
	struct adl_serializer<cft::SpawnTriggerDescriptor>
	{
		static void from_json(const json& data, cft::SpawnTriggerDescriptor& value)
		{
			value = cft::SpawnTriggerDescriptor{
				data.at("maximumRecursionDepth"),
				JsonTools::parseOptional<cft::ParticleEmitterSpawnContext>(data.at("spawnEmitterSpawnContext")),
				JsonTools::parseOptional<cft::ParticleEmitterSpawnContext>(data.at("deathEmitterSpawnContext")),
				JsonTools::parseOptional<cft::PeriodicSpawnTriggerContext>(data.at("periodicEmitterSpawnContext"))
			};
		}
	};

	template <>
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

	template <>
	struct adl_serializer<cft::BillboardRenderConfiguration>
	{
		static void from_json(const json& data, cft::BillboardRenderConfiguration& value)
		{
			value = cft::BillboardRenderConfiguration{
				JsonTools::parseOptional<unsigned int>(data.at("spriteSheetId"))
			};
		}
	};

	template <>
	struct adl_serializer<cft::MeshRenderConfiguration>
	{
		static void from_json(const json& data, cft::MeshRenderConfiguration& value)
		{
			value = cft::MeshRenderConfiguration{
				data.at("modelId"),
				JsonTools::parseOptional<unsigned int>(data.at("imageId"))
			};
		}
	};

	template <>
	struct adl_serializer<cft::RenderConfiguration>
	{
		static void from_json(const json& data, cft::RenderConfiguration& value)
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
	};

	template <>
	struct adl_serializer<std::unique_ptr<cft::SpawnShape>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::SpawnShape>& value)
		{
			std::string type = data.at("type");

			if (type == "Circle")
				value = std::make_unique<cft::CircleSpawnShape>(data.at("radius"), data.at("axis").get<Vec3>().value);
			else if (type == "Cone")
				value = std::make_unique<cft::ConeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<Vec3>().value);
			else if (type == "ConeVolume")
				value = std::make_unique<cft::ConeVolumeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<Vec3>().value);
			else if (type == "Cylinder")
				value = std::make_unique<cft::CylinderSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<Vec3>().value);
			else if (type == "CylinderVolume")
				value = std::make_unique<cft::CylinderVolumeSpawnShape>(data.at("height"), data.at("radius"), data.at("axis").get<Vec3>().value);
			else if (type == "Disk")
				value = std::make_unique<cft::DiskSpawnShape>(data.at("radius"), data.at("axis").get<Vec3>().value);
			else if (type == "Sphere")
				value = std::make_unique<cft::SphereSpawnShape>(data.at("radius"));
			else if (type == "SphereVolume")
				value = std::make_unique<cft::SphereVolumeSpawnShape>(data.at("radius"));
			else
				throw std::runtime_error("Invalid spawn shape type : '" + type + "'");
		}
	};

	template <>
	struct adl_serializer<std::unique_ptr<cft::ParticleSpawner>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::ParticleSpawner>& value);
	};

	template <>
	struct adl_serializer<cft::Image>
	{
		static void from_json(const json& data, cft::Image& value)
		{
			cft::Image image;
			image.loadFromFile(data.at("path"));

			value = image;
		}
	};

	template <>
	struct adl_serializer<cft::Model>
	{
		static void from_json(const json& data, cft::Model& value)
		{
			cft::Model model;
			model.loadFromFile(data.at("path"));

			value = model;
		}
	};

	template <>
	struct adl_serializer<cft::SpriteSheetDescriptor>
	{
		static void from_json(const json& data, cft::SpriteSheetDescriptor& value)
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
	};

	template <>
	struct adl_serializer<cft::ParticleEffectDescriptor>
	{
		static void from_json(const json& data, cft::ParticleEffectDescriptor& value)
		{
			value = cft::ParticleEffectDescriptor{
				data.at("emitterSpawnContexts").get<std::vector<cft::ParticleEmitterSpawnContext>>()
			};
		}
	};

	template <>
	struct adl_serializer<cft::ParticleEmitterDescriptor>
	{
		static void from_json(const json& data, cft::ParticleEmitterDescriptor& value)
		{
			value = cft::ParticleEmitterDescriptor{
				data.at("poolId"),
				data.at("particleSpawnerId"),
				data.at("emissionPatternId"),
				JsonTools::parseOptional<cft::TrailConfiguration>(data.at("trailConfiguration")),
				JsonTools::parseOptional<cft::RibbonConfiguration>(data.at("ribbonConfiguration")),
				JsonTools::parseOptional<cft::SpawnTriggerDescriptor>(data.at("spawnTriggerDescriptor")),
				data.at("renderConfiguration").get<cft::RenderConfiguration>(),
				data.at("forceFieldIds").get<std::vector<unsigned int>>(),
				data.at("motionBehaviorIds").get<std::vector<unsigned int>>(),
				data.at("visualBehaviorIds").get<std::vector<unsigned int>>()
			};
		}
	};
	
	template <typename T>
	struct adl_serializer<cft::WeightedValue<T>>
	{
		static void from_json(const json& data, cft::WeightedValue<T>& value)
		{
			value = cft::WeightedValue<T>{
				data.at("value").get<T>(),
				data.at("weight")
			};
		}
	};
}