#pragma once

#include "RibbonGenerator.hpp"

namespace cft
{
	class WaveRibbonGenerator : public Cloneable<WaveRibbonGenerator, RibbonGenerator>
	{
	private:
		float m_frequency;
		float m_amplitude;
		float m_animationSpeed;

		glm::vec3 generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;

	public:
		WaveRibbonGenerator(float frequency, float amplitude, float animationSpeed);
	};
}