#pragma once

#include "Confetti/Simulation/Link/LinkRule/LinkRule.hpp"
#include "Confetti/Simulation/Pool/RibbonPool.hpp"
#include "Confetti/Data/RibbonConfiguration.hpp"
#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class ParticleLinker
	{
	protected:
		std::vector<std::unique_ptr<LinkRule>> m_connectionRules;
		std::vector<std::unique_ptr<LinkRule>> m_validationRules;

		bool testLinkRules(const std::vector<std::unique_ptr<LinkRule>>& linkRules, const LinkContext& linkContext) const;
		void createRibbon(unsigned int& createdRibbonsCount, RibbonPool& ribbonPool, unsigned int fromParticleId, unsigned int toParticleId, unsigned int ribbonRegistryId, unsigned int ribbonPointCount, float elapsedTime) const;
		bool tryConnect(unsigned int& createdRibbonsCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int fromParticleId, unsigned int toParticleId, unsigned int ribbonRegistryId, unsigned int ribbonPointCount, float elapsedTime) const;

	public:
		ParticleLinker(std::vector<std::unique_ptr<LinkRule>> connectionRules, std::vector<std::unique_ptr<LinkRule>> validationRules);
		ParticleLinker(const ParticleLinker& particleLinker);
		virtual ~ParticleLinker() = default;

		virtual std::unique_ptr<ParticleLinker> clone() const = 0;

		virtual unsigned int getMaximumRibbonCount(unsigned int maximumParticleCount) const = 0;
		virtual unsigned int createRibbons(unsigned int ribbonPointCount, RibbonPool& ribbonPool, const ParticlePool& particlePool, unsigned int ribbonRegistryId, float elapsedTime) = 0;
		
		bool isRibbonValid(const LinkContext& linkContext) const;
	};
}