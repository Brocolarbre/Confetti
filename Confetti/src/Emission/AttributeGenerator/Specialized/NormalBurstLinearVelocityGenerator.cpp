#include "Confetti/Emission/AttributeGenerator/Specialized/NormalBurstLinearVelocityGenerator.hpp"

namespace cft
{
	LinearVelocity NormalBurstLinearVelocityGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context)
	{
		glm::vec3 direction = glm::normalize(context.normal + m_randomNumberGenerator.generate(glm::vec3(-m_maximumAngle), glm::vec3(m_maximumAngle)));
		return context.position + direction * m_strength;
	}

	NormalBurstLinearVelocityGenerator::NormalBurstLinearVelocityGenerator(float strength, float maximumAngle, std::uint64_t seed) :
		m_strength(strength),
		m_maximumAngle(maximumAngle),
		m_randomNumberGenerator(seed)
	{

	}

	std::optional<std::uint64_t> NormalBurstLinearVelocityGenerator::getSeed() const
	{
		return m_randomNumberGenerator.getSeed();
	}

	void NormalBurstLinearVelocityGenerator::setSeed(std::uint64_t seed)
	{
		m_randomNumberGenerator.setSeed(seed);
	}
}