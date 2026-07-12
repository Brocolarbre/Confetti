#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class SingleBurstEmissionPattern : public CloneableEmissionPattern<SingleBurstEmissionPattern>
	{
	private:
		unsigned int m_count;
		bool m_hasEmitted;

	public:
		SingleBurstEmissionPattern(unsigned int count);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const;
		unsigned int emit(float deltaTime) override;
	};
}