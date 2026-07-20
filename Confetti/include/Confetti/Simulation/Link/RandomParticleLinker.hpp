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

		unsigned int createRibbons(RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime);
		void updateRibbon(RibbonView& ribbon, const PathConfiguration& pathConfiguration, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle);
		bool isRibbonValid(const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;
	};
}