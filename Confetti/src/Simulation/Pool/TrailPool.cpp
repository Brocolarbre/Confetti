#include "Confetti/Simulation/Pool/TrailPool.hpp"

namespace cft
{
	void TrailPool::resizeStorage(unsigned int capacity)
	{
		m_trailRegistryId.resize(capacity);
		m_particleId.resize(capacity);
		m_particleDeathTime.resize(capacity);
		m_particleColor.resize(capacity);
		m_trailPoints.resize(capacity);

		m_storageCapacity = capacity;
		m_reservedSlots = std::min(m_reservedSlots, m_storageCapacity);
		m_count = std::min(m_count, m_storageCapacity);
	}

	TrailPool::TrailPool() :
		m_trailRegistryId(),
		m_particleId(),
		m_particleDeathTime(),
		m_particleColor(),
		m_trailPoints(),
		m_storageCapacity(0),
		m_reservedSlots(0),
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

	void TrailPool::reserveSlots(unsigned int slots)
	{
		if (static_cast<int>(m_storageCapacity) - static_cast<int>(m_count) - static_cast<int>(m_reservedSlots) < static_cast<int>(slots))
			resizeStorage(m_storageCapacity + slots);

		m_reservedSlots += slots;
	}

	void TrailPool::insert(const Trail& trail)
	{
		unsigned int newIndex = m_count++;

		m_trailRegistryId[newIndex] = trail.trailRegistryId;
		m_particleId[newIndex] = trail.particleId;
		m_particleDeathTime[newIndex] = trail.particleDeathTime;
		m_particleColor[newIndex] = trail.particleColor;
		m_trailPoints[newIndex] = trail.points;

		--m_reservedSlots;
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