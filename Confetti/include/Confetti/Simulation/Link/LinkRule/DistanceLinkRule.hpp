#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class DistanceLinkRule : public Cloneable<DistanceLinkRule, LinkRule>
	{
	private:
		float m_squaredMinimumDistance;
		float m_squaredMaximumDistance;

	public:
		DistanceLinkRule(float minimumDistance, float maximumDistance);

		bool test(const LinkContext& linkContext) const override;
	};
}