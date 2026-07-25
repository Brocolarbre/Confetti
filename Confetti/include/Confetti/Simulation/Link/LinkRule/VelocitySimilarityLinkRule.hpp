#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class CONFETTI_API VelocitySimilarityLinkRule : public Cloneable<VelocitySimilarityLinkRule, LinkRule>
	{
	private:
		float m_threshold;

	public:
		VelocitySimilarityLinkRule(float threshold);

		bool test(const LinkContext& linkContext) const override;
	};
}