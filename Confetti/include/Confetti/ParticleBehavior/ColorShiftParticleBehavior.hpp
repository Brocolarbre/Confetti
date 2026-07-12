#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class ColorShiftParticleBehavior : public Cloneable<ColorShiftParticleBehavior, ParticleBehavior>
	{
	private:
		std::vector<glm::vec4> m_colors;
		float m_speed;
		bool m_cyclic;

	public:
		ColorShiftParticleBehavior(const std::vector<glm::vec4>& colors, float speed, bool cyclic);

		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}