#pragma once

#include "VisualBehavior.hpp"
#include "ParticleTime.hpp"

namespace cft
{
	class DimOutVisualBehavior : public Cloneable<DimOutVisualBehavior, VisualBehavior>
	{
	private:
		ParticleTime m_duration;

	public:
		DimOutVisualBehavior(ParticleTime duration);

		void evaluate(float elapsedTime, float normalizedAge, ParticleView& particle) override;
	};
}