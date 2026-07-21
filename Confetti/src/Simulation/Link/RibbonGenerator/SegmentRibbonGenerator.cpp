#include "Confetti/Simulation/Link/RibbonGenerator/SegmentRibbonGenerator.hpp"

namespace cft
{
	glm::vec3 SegmentRibbonGenerator::generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const
	{
		return glm::mix(fromParticle.postBehaviorPosition, toParticle.postBehaviorPosition, t);
	}
}