#include "Confetti/Simulation/Link/RibbonGenerator/SegmentRibbonGenerator.hpp"

namespace cft
{
	void SegmentRibbonGenerator::updateRibbon(RibbonView& ribbon, const PathConfiguration& pathConfiguration, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle)
	{
		ribbon.points[0] = PathPoint{ glm::vec4{}, fromParticle.postBehaviorPosition, 0.0f, 0.0f, ribbon.points[0].spawnTime };
		ribbon.points[1] = PathPoint{ glm::vec4{}, toParticle.postBehaviorPosition, 0.0f, 1.0f, ribbon.points[1].spawnTime };

		float length = glm::distance(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition);

		for (unsigned int i = 0; i < ribbon.points.size(); ++i)
		{
			float t = static_cast<float>(i) / static_cast<float>(ribbon.points.size() - 1);
			ribbon.points[i].position = glm::mix(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition, t);
			ribbon.points[i].distanceOnTrail = length * t;
		}
	}
}