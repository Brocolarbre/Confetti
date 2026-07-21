#pragma once

#include "RibbonGenerator.hpp"

namespace cft
{
	class SpiralRibbonGenerator : public Cloneable<SpiralRibbonGenerator, RibbonGenerator>
	{
	private:
		float m_frequency;
		float m_radius;
		float m_animationSpeed;

		glm::vec3 generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;
	
	public:
		SpiralRibbonGenerator(float frequency, float radius, float animationSpeed);
	};
}