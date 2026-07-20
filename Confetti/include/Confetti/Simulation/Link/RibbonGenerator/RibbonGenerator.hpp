#pragma once

#include "Confetti/Simulation/Core/Particle.hpp"
#include "Confetti/Simulation/Core/Ribbon.hpp"
#include "Confetti/Data/RibbonConfiguration.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class RibbonGenerator
	{
	private:
		virtual glm::vec3 generateRibbonPoint(float t, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;

	public:
		virtual ~RibbonGenerator() = default;

		virtual std::unique_ptr<RibbonGenerator> clone() const = 0;

		std::vector<glm::vec3> generateRibbon(unsigned int pointCount, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;
	};
}