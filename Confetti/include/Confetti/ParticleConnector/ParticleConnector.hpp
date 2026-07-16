#pragma once

#include "Confetti/Particle/Ribbon.hpp"
#include "Confetti/ParticleSimulation/ParticlePool.hpp"
#include "Confetti/ParticleSimulation/RibbonPool.hpp"
#include "Confetti/Tools/Cloneable.hpp"

namespace cft
{
	class ParticleConnector
	{
	public:
		virtual ~ParticleConnector() = default;

		virtual std::unique_ptr<ParticleConnector> clone() const = 0;

		virtual unsigned int createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool) = 0;
		virtual bool isRibbonValid(const ConstantRibbonView& ribbon, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;
		virtual void updateRibbon(RibbonView& ribbon) = 0;
	};
}