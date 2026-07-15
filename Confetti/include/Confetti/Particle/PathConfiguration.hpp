#pragma once

#include <glm/glm.hpp>
#include <optional>
#include <vector>

namespace cft
{
	struct LifetimeFade
	{
		float start;
		float end;

	};
	enum class ColorInterpolation
	{
		Constant,
		Linear
	};

	enum class ThicknessDistribution
	{
		Constant,
		LinearDecreasing,
		QuadraticDecreasing,
		LinearIncreasing,
		QuadraticIncreasing
	};

	struct ThicknessEvolution
	{
		ThicknessDistribution distribution;
		float speed;
	};

	struct PathImage
	{
		unsigned int imageId;
		std::optional<float> repeatStretch;
	};

	struct PathConfiguration
	{
		float thickness;
		std::optional<float> lifetime;
		std::optional<LifetimeFade> lifetimeFade;
		bool appendParticleColor;
		std::vector<glm::vec4> colorGradient;
		std::optional<std::vector<float>> colorStart;
		ColorInterpolation colorInterpolation;
		ThicknessDistribution thicknessDistribution;
		std::optional<ThicknessEvolution> thicknessEvolution;
		std::optional<PathImage> image;
	};
}