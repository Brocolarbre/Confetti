#pragma once

namespace cft
{
	struct Ribbon
	{
		unsigned int fromParticleId;
		unsigned int toParticleId;
	};

	struct RibbonView
	{
		const unsigned int& fromParticleId;
		const unsigned int& toParticleId;
	};
}