#include "Confetti/ParticleSimulation/ParticlePool.hpp"

namespace cft
{
	void ParticlePool::resize(unsigned int capacity)
	{
		m_color.resize(capacity);
		m_position.resize(capacity);
		m_velocity.resize(capacity);
		m_scale.resize(capacity);
		m_lifetime.resize(capacity);
		m_spawnTime.resize(capacity);
		m_id.resize(capacity);

		m_capacity = capacity;
		m_reservedCapacity = glm::min(m_reservedCapacity, m_capacity);
		m_count = glm::min(m_count, m_capacity);
	}

	ParticlePool::ParticlePool() :
		m_color(),
		m_position(),
		m_velocity(),
		m_scale(),
		m_lifetime(),
		m_spawnTime(),
		m_id(),
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

	const std::vector<glm::vec3>& ParticlePool::getVelocity() const
	{
		return m_velocity;
	}

	const std::vector<glm::vec2>& ParticlePool::getScale() const
	{
		return m_scale;
	}

	const std::vector<float>& ParticlePool::getLifetime() const
	{
		return m_lifetime;
	}

	const std::vector<float>& ParticlePool::getSpawnTime() const
	{
		return m_spawnTime;
	}

	const std::vector<unsigned int>& ParticlePool::getId() const
	{
		return m_id;
	}

	std::vector<glm::vec4>& ParticlePool::getColor()
	{
		return m_color;
	}

	std::vector<glm::vec3>& ParticlePool::getPosition()
	{
		return m_position;
	}

	std::vector<glm::vec3>& ParticlePool::getVelocity()
	{
		return m_velocity;
	}

	std::vector<glm::vec2>& ParticlePool::getScale()
	{
		return m_scale;
	}

	std::vector<float>& ParticlePool::getLifetime()
	{
		return m_lifetime;
	}

	std::vector<float>& ParticlePool::getSpawnTime()
	{
		return m_spawnTime;
	}

	std::vector<unsigned int>& ParticlePool::getId()
	{
		return m_id;
	}

	unsigned int ParticlePool::getCount() const
	{
		return m_count;
	}

	void ParticlePool::reserve(unsigned int capacity)
	{
		if (static_cast<int>(m_capacity) - static_cast<int>(m_count) - static_cast<int>(m_reservedCapacity) < static_cast<int>(capacity))
			resize(m_capacity + capacity);

		m_reservedCapacity += capacity;
	}

	void ParticlePool::insert(const Particle& particle)
	{
		unsigned int newIndex = m_count++;

		m_color[newIndex] = particle.color;
		m_position[newIndex] = particle.position;
		m_velocity[newIndex] = particle.velocity;
		m_scale[newIndex] = particle.scale;
		m_lifetime[newIndex] = particle.lifetime;
		m_spawnTime[newIndex] = particle.spawnTime;
		m_id[newIndex] = particle.id;

		--m_reservedCapacity;
	}

	void ParticlePool::remove(unsigned int index)
	{
		unsigned int lastIndex = --m_count;

		m_color[index] = m_color[lastIndex];
		m_position[index] = m_position[lastIndex];
		m_velocity[index] = m_velocity[lastIndex];
		m_scale[index] = m_scale[lastIndex];
		m_lifetime[index] = m_lifetime[lastIndex];
		m_spawnTime[index] = m_spawnTime[lastIndex];
		m_id[index] = m_id[lastIndex];
	}
}