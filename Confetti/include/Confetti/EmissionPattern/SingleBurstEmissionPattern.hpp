#pragma once

#include "EmissionPattern.hpp"

namespace cft
{
	class SingleBurstEmissionPattern : public EmissionPattern
	{
	private:
		unsigned int m_count;
		bool m_hasEmitted;

	public:
		SingleBurstEmissionPattern(unsigned int count);

		unsigned int getMaximumSimultaneousParticleCount(float maximumParticleLifetime) const;
		unsigned int emit(float deltaTime) override;
		std::unique_ptr<EmissionPattern> clone() const override;
	};
}