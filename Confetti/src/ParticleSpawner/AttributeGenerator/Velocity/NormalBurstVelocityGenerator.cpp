#include "Confetti/ParticleSpawner/AttributeGenerator/Velocity/NormalBurstVelocityGenerator.hpp"

namespace cft
{
	Velocity NormalBurstVelocityGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		glm::vec3 direction = glm::normalize(context.normal + m_randomNumberGenerator.generate(glm::vec3(-m_maximumAngle), glm::vec3(m_maximumAngle)));
		return context.position + direction * m_strength;
	}

	NormalBurstVelocityGenerator::NormalBurstVelocityGenerator(float strength, float maximumAngle, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_maximumAngle(maximumAngle),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<AttributeGenerator<Velocity>> NormalBurstVelocityGenerator::clone() const
	{
		return std::make_unique<NormalBurstVelocityGenerator>(*this);
	}
}