#pragma once

#include "ParticleLinker.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class RandomParticleLinker: public Cloneable<RandomParticleLinker, ParticleLinker>
	{
	private:
		unsigned int m_connectionsCount;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		RandomParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int connectionsCount, RandomNumberGenerator& randomNumberGenerator);

		unsigned int getMaximumRibbonCount(unsigned int maximumParticleCount) const override;
		unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
	};
}