#include "Confetti/Simulation/Pool/TrailPool.hpp"

namespace cft
{
	void TrailPool::resize(unsigned int capacity)
	{
		m_trailRegistryId.resize(capacity);
		m_particleId.resize(capacity);
		m_particleDeathTime.resize(capacity);
		m_particleColor.resize(capacity);
		m_trailPoints.resize(capacity);

		m_capacity = capacity;
		m_reservedCapacity = std::min(m_reservedCapacity, m_capacity);
		m_count = std::min(m_count, m_capacity);
	}

	TrailPool::TrailPool() :
		m_trailRegistryId(),
		m_particleId(),
		m_particleDeathTime(),
		m_particleColor(),
		m_trailPoints(),
		m_capacity(0),
		m_reservedCapacity(0),
		m_count(0)
	{

	}

	const std::vector<unsigned int>& TrailPool::getTrailRegistryId() const
	{
		return m_trailRegistryId;
	}

	const std::vector<unsigned int>& TrailPool::getParticleId() const
	{
		return m_particleId;
	}

	const std::vector<float>& TrailPool::getParticleDeathTime() const
	{
		return m_particleDeathTime;
	}

	const std::vector<glm::vec4>& TrailPool::getParticleColor() const
	{
		return m_particleColor;
	}

	const std::vector<std::deque<PathPoint>>& TrailPool::getPathPoints() const
	{
		return m_trailPoints;
	}

	std::vector<unsigned int>& TrailPool::getTrailRegistryId()
	{
		return m_trailRegistryId;
	}

	std::vector<unsigned int>& TrailPool::getParticleId()
	{
		return m_particleId;
	}

	std::vector<float>& TrailPool::getParticleDeathTime()
	{
		return m_particleDeathTime;
	}

	std::vector<glm::vec4>& TrailPool::getParticleColor()
	{
		return m_particleColor;
	}

	std::vector<std::deque<PathPoint>>& TrailPool::getPathPoints()
	{
		return m_trailPoints;
	}

	unsigned int TrailPool::getCount() const
	{
		return m_count;
	}

	void TrailPool::reserve(unsigned int capacity)
	{
		if (static_cast<int>(m_capacity) - static_cast<int>(m_count) - static_cast<int>(m_reservedCapacity) < static_cast<int>(capacity))
			resize(m_capacity + capacity);

		m_reservedCapacity += capacity;
	}

	void TrailPool::insert(const Trail& trail)
	{
		unsigned int newIndex = m_count++;

		m_trailRegistryId[newIndex] = trail.trailRegistryId;
		m_particleId[newIndex] = trail.particleId;
		m_particleDeathTime[newIndex] = trail.particleDeathTime;
		m_particleColor[newIndex] = trail.particleColor;
		m_trailPoints[newIndex] = trail.points;

		--m_reservedCapacity;
	}

	void TrailPool::remove(unsigned int index)
	{
		unsigned int lastIndex = --m_count;

		m_trailRegistryId[index] = m_trailRegistryId[lastIndex];
		m_particleId[index] = m_particleId[lastIndex];
		m_particleDeathTime[index] = m_particleDeathTime[lastIndex];
		m_particleColor[index] = m_particleColor[lastIndex];
		m_trailPoints[index] = m_trailPoints[lastIndex];
	}
}