#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class PhaseSimilarityLinkRule : public Cloneable<PhaseSimilarityLinkRule, LinkRule>
	{
	private:
		float m_threshold;

	public:
		PhaseSimilarityLinkRule(float threshold);

		bool test(const LinkContext& linkContext) const override;
	};
}