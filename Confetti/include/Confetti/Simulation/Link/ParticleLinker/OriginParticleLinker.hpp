#pragma once

#include "ParticleLinker.hpp"

namespace cft
{
	class OriginParticleLinker : public Cloneable<OriginParticleLinker, ParticleLinker>
	{
	private:
		glm::vec3 m_origin;

	public:
		OriginParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules, const glm::vec3& targetParticleId);

		unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) override;
	};
}