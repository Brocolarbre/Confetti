#pragma once

#include "PathConfiguration.hpp"

namespace cft
{
	struct RibbonConfiguration
	{
		PathConfiguration pathConfiguration;
		unsigned int particleLinkerId;
		unsigned int ribbonGeneratorId;
		unsigned int ribbonPointCount;
	};
}