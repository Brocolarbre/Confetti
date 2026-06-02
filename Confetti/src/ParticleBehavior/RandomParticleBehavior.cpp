#include "Confetti/ParticleBehavior/RandomParticleBehavior.hpp"

namespace cft
{
	RandomParticleBehavior::RandomParticleBehavior(float strength, RandomNumberGenerator& randomNumberGenerator) :
		m_strength(strength),
		m_randomNumberGenerator(randomNumberGenerator)
	{

	}

	std::unique_ptr<ParticleBehavior> RandomParticleBehavior::clone() const
	{
		return std::make_unique<RandomParticleBehavior>(*this);
	}

	void RandomParticleBehavior::update(float elapsedTime, float deltaTime, ParticleView& particle)
	{
		particle.position += m_randomNumberGenerator.generate(glm::vec3(-m_strength), glm::vec3(m_strength)) * deltaTime;
	}
}