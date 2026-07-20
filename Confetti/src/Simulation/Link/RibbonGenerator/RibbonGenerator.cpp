#include "Confetti/Simulation/Link/RibbonGenerator/RibbonGenerator.hpp"

namespace cft
{
	std::vector<glm::vec3> RibbonGenerator::generateRibbon(unsigned int pointCount, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		std::vector<glm::vec3> points;
		points.reserve(pointCount);

		float segmentCount = static_cast<float>(pointCount - 1);

		for (unsigned int i = 0; i < pointCount; ++i)
		{
			float t = static_cast<float>(i) / segmentCount;
			points.push_back(generateRibbonPoint(t, fromParticle, toParticle));
		}

		return points;
	}
}