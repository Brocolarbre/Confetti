#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class CONFETTI_API PhaseSimilarityLinkRule : public Cloneable<PhaseSimilarityLinkRule, LinkRule>
	{
	private:
		float m_threshold;

	public:
		PhaseSimilarityLinkRule(float threshold);

		bool test(const LinkContext& linkContext) const override;
	};
}