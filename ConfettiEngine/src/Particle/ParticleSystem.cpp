#include "ConfettiEngine/Particle/ParticleSystem.hpp"

namespace cft
{
	void ParticleSystem::addParticle(const glm::vec4& color, const glm::vec3& position, const glm::vec3& velocity, const glm::vec2& scale, float lifetime, float spawnTime)
	{
		unsigned int newParticleIndex = m_particleCount++;

		m_particleData.color[newParticleIndex] = color;
		m_particleData.position[newParticleIndex] = position;
		m_particleData.velocity[newParticleIndex] = velocity;
		m_particleData.scale[newParticleIndex] = scale;
		m_particleData.lifetime[newParticleIndex] = lifetime;
		m_particleData.spawnTime[newParticleIndex] = spawnTime;
	}

	void ParticleSystem::removeParticle(unsigned int index)
	{
		unsigned int lastParticleIndex = --m_particleCount;

		m_particleData.color[index] = m_particleData.color[lastParticleIndex];
		m_particleData.position[index] = m_particleData.position[lastParticleIndex];
		m_particleData.velocity[index] = m_particleData.velocity[lastParticleIndex];
		m_particleData.scale[index] = m_particleData.scale[lastParticleIndex];
		m_particleData.lifetime[index] = m_particleData.lifetime[lastParticleIndex];
		m_particleData.spawnTime[index] = m_particleData.spawnTime[lastParticleIndex];
	}

	ParticleSystem::ParticleSystem() :
		m_particleData(),
		m_rng(),
		m_particleCount(0)
	{

	}

	const ParticleData& ParticleSystem::getParticleData() const
	{
		return m_particleData;
	}

	ParticleData& ParticleSystem::getParticleData()
	{
		return m_particleData;
	}

	unsigned int ParticleSystem::getParticleCount() const
	{
		return m_particleCount;
	}

	void ParticleSystem::allocate(unsigned int particleCount)
	{
		m_particleData.color.resize(particleCount);
		m_particleData.position.resize(particleCount);
		m_particleData.velocity.resize(particleCount);
		m_particleData.scale.resize(particleCount);
		m_particleData.lifetime.resize(particleCount);
		m_particleData.spawnTime.resize(particleCount);
		m_particleData.size = particleCount;
	}

	void ParticleSystem::spawnParticle(float spawnTime)
	{
		constexpr glm::vec4 minColor(0.0f);
		constexpr glm::vec4 maxColor(1.0f);
		constexpr glm::vec3 minPos(-10.0f);
		constexpr glm::vec3 maxPos(10.0f);
		constexpr glm::vec3 minVelocity(-1.0f);
		constexpr glm::vec3 maxVelocity(1.0f);
		constexpr glm::vec2 minScale(0.01f);
		constexpr glm::vec2 maxScale(1.0f);
		constexpr float minLifetime = 2.0f;
		constexpr float maxLifetime = 5.0f;

		glm::vec4 color(m_rng(minColor.x, maxColor.x), m_rng(minColor.y, maxColor.y), m_rng(minColor.z, maxColor.z), m_rng(minColor.w, maxColor.w));
		glm::vec3 position(m_rng(minPos.x, maxPos.x), m_rng(minPos.y, maxPos.y), m_rng(minPos.z, maxPos.z));
		glm::vec3 velocity(m_rng(minVelocity.x, maxVelocity.x), m_rng(minVelocity.y, maxVelocity.y), m_rng(minVelocity.z, maxVelocity.z));
		glm::vec2 scale(m_rng(minScale.x, maxScale.x), m_rng(minScale.y, maxScale.y));
		float lifetime = m_rng(minLifetime, maxLifetime);

		addParticle(color, position, velocity, scale, lifetime, spawnTime);
	}

	void ParticleSystem::killParticle(unsigned int particleIndex)
	{
		removeParticle(particleIndex);
	}
}