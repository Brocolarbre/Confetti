#pragma once

#include "Confetti/Simulation/Core/Particle.hpp"
#include "Confetti/Simulation/Core/Ribbon.hpp"
#include "Confetti/Data/RibbonConfiguration.hpp"
#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Pool/RibbonPool.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class ParticleLinker
	{
	public:
		virtual ~ParticleLinker() = default;

		virtual std::unique_ptr<ParticleLinker> clone() const = 0;

		virtual unsigned int getMaximumRibbonCount(unsigned int maximumParticleCount) const = 0;
		virtual unsigned int createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) = 0;
		virtual bool isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;
	};
}