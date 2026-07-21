#pragma once

#include "LinkRule.hpp"

namespace cft
{
	class ConnectionLinkRule : public Cloneable<ConnectionLinkRule, LinkRule>
	{
	private:
		unsigned int m_maximumConnectionCount;

	public:
		ConnectionLinkRule(unsigned int maximumConnectionCount);

		bool test(const LinkContext& linkContext) const override;
	};
}