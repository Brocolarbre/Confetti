#pragma once

#include "RibbonGenerator.hpp"

namespace cft
{
	class SegmentRibbonGenerator : public Cloneable<SegmentRibbonGenerator, RibbonGenerator>
	{
	private:
		glm::vec3 generateRibbonPoint(float t, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;
	};
}