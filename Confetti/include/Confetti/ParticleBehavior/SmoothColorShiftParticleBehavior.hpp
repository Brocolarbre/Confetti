#pragma once

#include "ParticleBehavior.hpp"

namespace cft
{
	class SmoothColorShiftParticleBehavior : public ParticleBehavior
	{
	private:
		std::vector<glm::vec4> m_colors;
		float m_speed;
		bool m_cyclic;

	public:
		SmoothColorShiftParticleBehavior(const std::vector<glm::vec4>& colors, float speed, bool cyclic);

		std::unique_ptr<ParticleBehavior> clone() const override;
		void evaluate(float elapsedTime, float particleNormalizedAge, ParticleView& particle) override;
	};
}