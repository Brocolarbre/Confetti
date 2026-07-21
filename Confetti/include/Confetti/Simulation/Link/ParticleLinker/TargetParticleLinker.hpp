#pragma once

#include "ParticleLinker.hpp"

namespace cft
{
	class TargetParticleLinker : public Cloneable<TargetParticleLinker, ParticleLinker>
	{
	private:
		unsigned int m_targetParticleId;

	public:
		TargetParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, unsigned int targetParticleId);

		unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
	};
}