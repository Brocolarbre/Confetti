#pragma once

#include "ParticleLinker.hpp"

namespace cft
{
	class KNearestNeighborParticleLinker : public Cloneable<KNearestNeighborParticleLinker, ParticleLinker>
	{
	private:
		unsigned int m_neighborCount;

	public:
		KNearestNeighborParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int neighborCount);

		unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
	};
}