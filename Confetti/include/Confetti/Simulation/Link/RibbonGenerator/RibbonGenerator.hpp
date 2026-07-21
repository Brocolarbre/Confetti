#pragma once

#include "Confetti/Simulation/Pool/ParticlePool.hpp"
#include "Confetti/Simulation/Pool/RibbonPool.hpp"
#include "Confetti/Data/RibbonConfiguration.hpp"
#include "Confetti/Tool/Cloneable.hpp"

namespace cft
{
	class RibbonGenerator
	{
	private:
		virtual glm::vec3 generateRibbonPoint(float t, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const = 0;

	public:
		virtual ~RibbonGenerator() = default;

		virtual std::unique_ptr<RibbonGenerator> clone() const = 0;

		std::vector<glm::vec3> generateRibbon(unsigned int pointCount, float elapsedTime, const ConstantParticleView& fromParticle, const ConstantParticleView& toParticle) const;
	};
}