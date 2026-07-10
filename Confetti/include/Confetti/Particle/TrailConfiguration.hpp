#pragma once

#include <glm/glm.hpp>
#include <optional>
#include <vector>

namespace cft
{
	enum class TrailThicknessDistribution
	{
		Constant,
		LinearDecreasing,
		QuadraticDecreasing,
		LinearIncreasing,
		QuadraticIncreasing
	};

	struct TrailThicknessEvolution
	{
		TrailThicknessDistribution distribution;
		float speed;
	};

	struct LifetimeFade
	{
		float start;
		float end;
	};

	enum class TrailColorInterpolation
	{
		Constant,
		Linear
	};

	struct TrailImage
	{
		unsigned int imageId;
		std::optional<float> repeatStretch;
	};

	struct TrailConfiguration
	{
		float presistenceLifetime;
		float thickness;
		float minimumSpawnDistance;
		std::optional<float> maximumSpawnTime;

		std::optional<float> pointLifetime;
		std::optional<LifetimeFade> lifetimeFade;
		std::optional<unsigned int> maximumSegmentCount;

		bool appendParticleColor;
		std::vector<glm::vec4> colorGradient;
		std::optional<std::vector<float>> colorStart;
		TrailColorInterpolation colorInterpolation;
		TrailThicknessDistribution thicknessDistribution;
		std::optional<TrailThicknessEvolution> thicknessEvolution;
		std::optional<TrailImage> image;
	};
}