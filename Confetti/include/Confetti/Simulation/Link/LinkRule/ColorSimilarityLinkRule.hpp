#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class CONFETTI_API ColorSimilarityLinkRule : public Cloneable<ColorSimilarityLinkRule, LinkRule>
	{
	private:
		float m_threshold;

	public:
		ColorSimilarityLinkRule(float threshold);

		bool test(const LinkContext& linkContext) const override;
	};
}