#include "Confetti/Behavior/Visual/ColorShiftVisualBehavior.hpp"

namespace cft
{
	ColorShiftVisualBehavior::ColorShiftVisualBehavior(const std::vector<glm::vec4>& colors, float speed, bool cyclic) :
		m_colors(colors),
		m_speed(speed),
		m_cyclic(cyclic)
	{

	}

	void ColorShiftVisualBehavior::evaluate(float elapsedTime, float normalizedAge, ParticleView& particle)
	{
		if (m_colors.empty())
			return;

		unsigned int colorIndex = static_cast<unsigned int>((elapsedTime - particle.spawnTime) * m_speed + static_cast<unsigned int>(particle.phase));

		if (m_cyclic)
			colorIndex %= m_colors.size();
		else
			colorIndex = glm::min(colorIndex, static_cast<unsigned int>(m_colors.size() - 1));

		particle.color = m_colors[colorIndex];
	}
}