#pragma once

#include "RibbonGenerator.hpp"

namespace cft
{
	class SegmentRibbonGenerator : public Cloneable<SegmentRibbonGenerator, RibbonGenerator>
	{
	public:
		void updateRibbon(RibbonView& ribbon, const PathConfiguration& pathConfiguration, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) override;
	};
}