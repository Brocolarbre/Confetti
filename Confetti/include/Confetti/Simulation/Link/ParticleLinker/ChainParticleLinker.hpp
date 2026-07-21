#pragma once

#include "ParticleLinker.hpp"

namespace cft
{
	class ChainParticleLinker : public Cloneable<ChainParticleLinker, ParticleLinker>
	{
	public:
		ChainParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules);

		unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
	};
}