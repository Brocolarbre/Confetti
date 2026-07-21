#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class AgeSimilarityLinkRule : public Cloneable<AgeSimilarityLinkRule, LinkRule>
	{
	private:
		float m_threshold;

	public:
		AgeSimilarityLinkRule(float threshold);

		bool test(const LinkContext& linkContext) const override;
	};
}