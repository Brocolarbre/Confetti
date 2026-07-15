#pragma once

#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/RibbonPool.hpp"

namespace cft
{
	class RibbonGenerator
	{
	private:
		virtual bool isRibbonValid(const RibbonView& ribbon, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;
		virtual void updateRibbon(RibbonView& ribbon) = 0;
		virtual void createRibbons(const ParticlePool& particlePool, RibbonPool& ribbonPool) = 0;

	public:
		virtual ~RibbonGenerator() = default;

		virtual void update(const ParticlePool& particlePool, RibbonPool& ribbonPool);
	};
}