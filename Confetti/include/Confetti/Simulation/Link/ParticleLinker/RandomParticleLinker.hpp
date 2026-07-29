#pragma once

#include "ParticleLinker.hpp"
#include "Confetti/Tool/RandomNumberGenerator.hpp"

namespace cft
{
	class CONFETTI_API RandomParticleLinker: public Cloneable<RandomParticleLinker, ParticleLinker>
	{
	private:
		unsigned int m_connectionCount;
		RandomNumberGenerator m_randomNumberGenerator;

	public:
		RandomParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int connectionCount, std::uint64_t seed = 0);

		std::optional<std::uint64_t> getSeed() const override;
		void setSeed(std::uint64_t seed) override;

		unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
	};
}