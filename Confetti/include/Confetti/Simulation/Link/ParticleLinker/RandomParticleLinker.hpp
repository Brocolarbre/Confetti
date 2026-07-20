#pragma once

#include "ParticleLinker.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomParticleLinker: public Cloneable<RandomParticleLinker, ParticleLinker>
	{
	private:
		float m_maximumDistance;
		unsigned int m_connectionsCount;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		RandomParticleLinker(float maximumDistance, unsigned int connectionsCount, RandomNumberGenerator& randomNumberGenerator);

		unsigned int getMaximumRibbonCount(unsigned int maximumParticleCount) const override;
		unsigned int createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
		bool isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const override;
	};
}