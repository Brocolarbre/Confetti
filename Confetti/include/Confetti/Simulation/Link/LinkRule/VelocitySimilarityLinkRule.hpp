#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class VelocitySimilarityLinkRule : public Cloneable<VelocitySimilarityLinkRule, LinkRule>
	{
	private:
		float m_threshold;

	public:
		VelocitySimilarityLinkRule(float threshold);

		bool test(const LinkContext& linkContext) const override;
	};
}