#include "Confetti/ParticleSpawner/AttributeGenerator/Specific/NormalBurstLinearVelocityGenerator.hpp"

namespace cft
{
	LinearVelocity NormalBurstLinearVelocityGenerator::generateValue(unsigned int count, unsigned int index, const SpawnContext& context) const
	{
		glm::vec3 direction = glm::normalize(context.normal + m_randomNumberGenerator.generate(glm::vec3(-m_maximumAngle), glm::vec3(m_maximumAngle)));
		return context.position + direction * m_strength;
	}

	NormalBurstLinearVelocityGenerator::NormalBurstLinearVelocityGenerator(float strength, float maximumAngle, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_maximumAngle(maximumAngle),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<AttributeGenerator<LinearVelocity>> NormalBurstLinearVelocityGenerator::clone() const
	{
		return std::make_unique<NormalBurstLinearVelocityGenerator>(*this);
	}
}