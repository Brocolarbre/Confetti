#pragma once

#include "Confetti/Tool/Cloneable.hpp"
#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Pool/RibbonPool.hpp"

namespace cft
{
	struct LinkContext
	{
		const ConstantParticleView& fromParticle;
		const ConstantParticleView& toParticle;
		const RibbonPool& ribbonPool;
	};

	class LinkRule
	{
	public:
		virtual ~LinkRule() = default;

		virtual std::unique_ptr<LinkRule> clone() const = 0;

		virtual bool test(const LinkContext& linkContext) const = 0;
	};
}