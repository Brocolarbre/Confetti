#include "Confetti/ParticleBehavior/ColorShiftParticleBehavior.hpp"

namespace cft
{
	ColorShiftParticleBehavior::ColorShiftParticleBehavior(const std::vector<glm::vec4>& colors, float speed, bool cyclic) :
		m_colors(colors),
		m_speed(speed),
		m_cyclic(cyclic)
	{

	}

	std::unique_ptr<ParticleBehavior> ColorShiftParticleBehavior::clone() const
	{
		return std::make_unique<ColorShiftParticleBehavior>(*this);
	}

	void ColorShiftParticleBehavior::update(float elapsedTime, float deltaTime, float progress, ParticleView& particle)
	{
		if (m_colors.empty())
			return;

		unsigned int colorIndex = static_cast<unsigned int>((elapsedTime - particle.spawnTime) * m_speed);

		if (m_cyclic)
			colorIndex %= m_colors.size();
		else
			colorIndex = glm::min(colorIndex, static_cast<unsigned int>(m_colors.size() - 1));

		particle.color = m_colors[colorIndex];
	}
}