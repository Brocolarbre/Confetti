#pragma once

#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/RibbonPool.hpp"

namespace cft
{
	struct RibbonUpdate
	{
		std::vector<>
	};

	class RibbonGenerator
	{
	private:
		virtual bool isRibbonValid(const RibbonView& ribbon, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;
		virtual void updateRibbon(RibbonView& ribbon) = 0;
		virtual void createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool) = 0;

	public:
		virtual ~RibbonGenerator() = default;

		virtual void update(RibbonPool& ribbonPool, const ParticlePool& particlePool);
	};
}