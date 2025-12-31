#include "ConfettiEngine/Particle/ParticlePool.hpp"

namespace cft
{
	Particle Particle::create(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime)
	{
		return Particle{
			generator.generate(boundaries.minimumColor, boundaries.maximumColor),
			generator.generate(boundaries.minimumPosition, boundaries.maximumPosition),
			generator.generate(boundaries.minimumVelocity, boundaries.maximumVelocity),
			generator.generate(boundaries.minimumScale, boundaries.maximumScale),
			generator.generate(boundaries.minimumLifetime, boundaries.maximumLifetime),
			elapsedTime
		};
	}

	ParticlePool::ParticlePool() :
		m_color(),
		m_position(),
		m_velocity(),
		m_scale(),
		m_lifetime(),
		m_spawnTime(),
		m_capacity(0),
		m_reservedCapacity(0),
		m_count(0)
	{

	}

	const std::vector<glm::vec4>& ParticlePool::getColor() const
	{
		return m_color;
	}

	const std::vector<glm::vec3>& ParticlePool::getPosition() const
	{
		return m_position;
	}

	const std::vector<glm::vec2>& ParticlePool::getScale() const
	{
		return m_scale;
	}

	unsigned int ParticlePool::getCapacity() const
	{
		return m_capacity;
	}

	unsigned int ParticlePool::getReservedCapacity() const
	{
		return m_reservedCapacity;
	}

	unsigned int ParticlePool::getCount() const
	{
		return m_count;
	}

	void ParticlePool::reserveCapacity(unsigned int capacity)
	{
		if (static_cast<int>(m_capacity) - static_cast<int>(m_count) - static_cast<int>(m_reservedCapacity) < static_cast<int>(capacity))
			resize(m_capacity + capacity);

		m_reservedCapacity += capacity;
	}

	void ParticlePool::createParticle(const Particle& data)
	{
		unsigned int newIndex = m_count++;

		m_color[newIndex] = data.color;
		m_position[newIndex] = data.position;
		m_velocity[newIndex] = data.velocity;
		m_scale[newIndex] = data.scale;
		m_lifetime[newIndex] = data.lifetime;
		m_spawnTime[newIndex] = data.spawnTime;
	}

	void ParticlePool::destroyParticle(unsigned int index)
	{
		unsigned int lastIndex = --m_count;

		m_color[index] = m_color[lastIndex];
		m_position[index] = m_position[lastIndex];
		m_velocity[index] = m_velocity[lastIndex];
		m_scale[index] = m_scale[lastIndex];
		m_lifetime[index] = m_lifetime[lastIndex];
		m_spawnTime[index] = m_spawnTime[lastIndex];

		--m_reservedCapacity;
	}

	void ParticlePool::resize(unsigned int capacity)
	{
		m_color.resize(capacity);
		m_position.resize(capacity);
		m_velocity.resize(capacity);
		m_scale.resize(capacity);
		m_lifetime.resize(capacity);
		m_spawnTime.resize(capacity);
		m_capacity = capacity;
		m_count = glm::min(m_count, m_capacity);
	}

	void ParticlePool::update(float elapsedTime, float deltaTime)
	{
		for (unsigned int i = 0; i < m_count;)
		{
			float despawnTime = m_spawnTime[i] + m_lifetime[i];
			if (despawnTime <= elapsedTime)
			{
				destroyParticle(i);
			}
			else
			{
				m_position[i] += m_velocity[i] * deltaTime;
				++i;
			}
		}
	}
}