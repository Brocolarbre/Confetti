#pragma once

#include "JsonLoader.hpp"
#include "JsonTools.hpp"
#include "JsonTypes.hpp"

#include <Confetti/Behavior/Force/SpatialInfluence.hpp>
#include <Confetti/Behavior/Visual/ParticleTime.hpp>
#include <Confetti/Emission/ParticleSpawner.hpp>
#include <Confetti/Simulation/Registry/AssetRegistry.hpp>

namespace nlohmann
{
	template <>
	struct adl_serializer<cft::JsonTypes::Color>
	{
		static void from_json(const json& data, cft::JsonTypes::Color& value);
	};

	template <>
	struct adl_serializer<cft::JsonTypes::Vec3>
	{
		static void from_json(const json& data, cft::JsonTypes::Vec3& value);
	};

	template <>
	struct adl_serializer<cft::JsonTypes::Vec2>
	{
		static void from_json(const json& data, cft::JsonTypes::Vec2& value);
	};

	template <>
	struct adl_serializer<lw::Point>
	{
		static void from_json(const json& data, lw::Point& value);
	};

	template <>
	struct adl_serializer<glm::vec4>
	{
		static void from_json(const json& data, glm::vec4& value);
	};

	template <>
	struct adl_serializer<cft::Falloff>
	{
		static void from_json(const json& data, cft::Falloff& value);
	};

	template <>
	struct adl_serializer<cft::SpatialInfluence>
	{
		static cft::SpatialInfluence from_json(const json& data);
	};

	template <>
	struct adl_serializer<std::unique_ptr<lw::Interpolator>>
	{
		static void from_json(const json& data, std::unique_ptr<lw::Interpolator>& value);
	};

	template <>
	struct adl_serializer<std::unique_ptr<lw::Easing>>
	{
		static void from_json(const json& data, std::unique_ptr<lw::Easing>& value);
	};

	template <>
	struct adl_serializer<cft::ParticleTime::Space>
	{
		static void from_json(const json& data, cft::ParticleTime::Space& value);
	};

	template <>
	struct adl_serializer<cft::ParticleTime>
	{
		static void from_json(const json& data, cft::ParticleTime& value);
	};

	template <>
	struct adl_serializer<std::unique_ptr<cft::LinkRule>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::LinkRule>& value);
	};

	template <>
	struct adl_serializer<cft::ThicknessEvolutionDistribution>
	{
		static void from_json(const json& data, cft::ThicknessEvolutionDistribution& value);
	};

	template <>
	struct adl_serializer<cft::LifetimeFade>
	{
		static void from_json(const json& data, cft::LifetimeFade& value);
	};

	template <>
	struct adl_serializer<cft::ColorInterpolation>
	{
		static void from_json(const json& data, cft::ColorInterpolation& value);
	};

	template <>
	struct adl_serializer<cft::ThicknessDistribution>
	{
		static void from_json(const json& data, cft::ThicknessDistribution& value);
	};

	template <>
	struct adl_serializer<cft::ThicknessEvolution>
	{
		static void from_json(const json& data, cft::ThicknessEvolution& value);
	};

	template <>
	struct adl_serializer<cft::PathImage>
	{
		static void from_json(const json& data, cft::PathImage& value);
	};

	template <>
	struct adl_serializer<cft::TimeRange>
	{
		static void from_json(const json& data, cft::TimeRange& value);
	};

	template <>
	struct adl_serializer<cft::MotionState>
	{
		static void from_json(const json& data, cft::MotionState& value);
	};

	template <>
	struct adl_serializer<cft::ParticleEmitterSpawnContext>
	{
		static void from_json(const json& data, cft::ParticleEmitterSpawnContext& value);
	};

	template <>
	struct adl_serializer<cft::PeriodicSpawnTriggerContext>
	{
		static void from_json(const json& data, cft::PeriodicSpawnTriggerContext& value);
	};

	template <>
	struct adl_serializer<cft::PathConfiguration>
	{
		static void from_json(const json& data, cft::PathConfiguration& value);
	};

	template <>
	struct adl_serializer<cft::TrailConfiguration>
	{
		static void from_json(const json& data, cft::TrailConfiguration& value);
	};

	template <>
	struct adl_serializer<cft::RibbonConfiguration>
	{
		static void from_json(const json& data, cft::RibbonConfiguration& value);
	};

	template <>
	struct adl_serializer<cft::SpawnTriggerDescriptor>
	{
		static void from_json(const json& data, cft::SpawnTriggerDescriptor& value);
	};

	template <>
	struct adl_serializer<cft::RenderType>
	{
		static void from_json(const json& data, cft::RenderType& value);
	};

	template <>
	struct adl_serializer<cft::BillboardRenderConfiguration>
	{
		static void from_json(const json& data, cft::BillboardRenderConfiguration& value);
	};

	template <>
	struct adl_serializer<cft::MeshRenderConfiguration>
	{
		static void from_json(const json& data, cft::MeshRenderConfiguration& value);
	};

	template <>
	struct adl_serializer<cft::RenderConfiguration>
	{
		static void from_json(const json& data, cft::RenderConfiguration& value);
	};

	template <>
	struct adl_serializer<std::unique_ptr<cft::SpawnShape>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::SpawnShape>& value);
	};

	template <>
	struct adl_serializer<std::unique_ptr<cft::ParticleSpawner>>
	{
		static void from_json(const json& data, std::unique_ptr<cft::ParticleSpawner>& value);
	};

	template <>
	struct adl_serializer<cft::Image>
	{
		static void from_json(const json& data, cft::Image& value);
	};

	template <>
	struct adl_serializer<cft::Model>
	{
		static void from_json(const json& data, cft::Model& value);
	};

	template <>
	struct adl_serializer<cft::SpriteSheetDescriptor>
	{
		static void from_json(const json& data, cft::SpriteSheetDescriptor& value);
	};

	template <>
	struct adl_serializer<cft::ParticleEffectDescriptor>
	{
		static void from_json(const json& data, cft::ParticleEffectDescriptor& value);
	};

	template <>
	struct adl_serializer<cft::ParticleEmitterDescriptor>
	{
		static void from_json(const json& data, cft::ParticleEmitterDescriptor& value);
	};
	
	template <typename T>
	struct adl_serializer<cft::WeightedValue<T>>
	{
		static void from_json(const json& data, cft::WeightedValue<T>& value);
	};

	template <typename T>
	inline void adl_serializer<cft::WeightedValue<T>>::from_json(const json& data, cft::WeightedValue<T>& value)
	{
		value = cft::WeightedValue<T>{
			data.at("value").get<T>(),
			data.at("weight")
		};
	}
}