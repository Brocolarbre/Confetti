#include "Confetti/Behavior/Visual/SmoothColorShiftVisualBehavior.hpp"

#include <cmath>

namespace cft
{
	SmoothColorShiftVisualBehavior::SmoothColorShiftVisualBehavior(const std::vector<glm::vec4>& colors, float speed, bool cyclic) :
		m_colors(colors),
		m_speed(speed),
		m_cyclic(cyclic)
	{

	}

	void SmoothColorShiftVisualBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		if (m_colors.empty())
			return;

		if (m_colors.size() == 1)
		{
			particle.color = m_colors[0];
			return;
		}

		float colorIndex;
		float t = std::modf((elapsedTime - particle.spawnTime) * m_speed + particle.phase, &colorIndex);

		unsigned int i = static_cast<unsigned int>(colorIndex);
		unsigned int j;

		if (m_cyclic)
		{
			i %= m_colors.size();
			j = (i + 1) % static_cast<unsigned int>(m_colors.size());
		}
		else
		{
			i = glm::min(i, static_cast<unsigned int>(m_colors.size() - 1));
			j = glm::min(i + 1, static_cast<unsigned int>(m_colors.size() - 1));
		}

		if (i == m_colors.size() - 2)
		unsigned int j = i + 1;

		particle.color = glm::mix(m_colors[i], m_colors[j], t);
	}
}