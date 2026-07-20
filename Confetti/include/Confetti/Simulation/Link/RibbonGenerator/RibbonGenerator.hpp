#pragma once

#include "Confetti/Simulation/Core/Particle.hpp"
#include "Confetti/Simulation/Core/Ribbon.hpp"
#include "Confetti/Data/RibbonConfiguration.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class RibbonGenerator
	{
	public:
		virtual ~RibbonGenerator() = default;

		virtual std::unique_ptr<RibbonGenerator> clone() const = 0;

		virtual void updateRibbon(RibbonView& ribbon, const PathConfiguration& pathConfiguration, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) = 0;
	};
}