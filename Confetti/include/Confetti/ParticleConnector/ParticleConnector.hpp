#pragma once

#include "Confetti/Particle/Ribbon.hpp"
#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/RibbonPool.hpp"
#include "Confetti/Tools/Cloneable.hpp"

namespace cft
{
	struct RibbonUpdate
	{
		unsigned int createdCount;
		unsigned int removedCount;
	};

	class ParticleConnector
	{
	private:
		virtual bool isRibbonValid(const Ribbon& ribbon, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;
		virtual void updateRibbon(Ribbon& ribbon) = 0;
		virtual unsigned int createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool) = 0;

	public:
		virtual ~ParticleConnector() = default;

		virtual std::unique_ptr<ParticleConnector> clone() const = 0;
		virtual RibbonUpdate update(RibbonPool& ribbonPool, const ParticlePool& particlePool);
	};
}