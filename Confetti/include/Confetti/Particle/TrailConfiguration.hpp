#pragma once

#include <glm/glm.hpp>
#include <optional>
#include <vector>

namespace cft
{
	enum class TrailThicknessEvolution
	{
		Constant,
		LinearDecreasing,
		QuadraticDecreasing,
		LinearIncreasing,
		QuadraticIncreasing
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
		TrailThicknessEvolution thicknessEvolution;
		// Thickness progress
	};
}