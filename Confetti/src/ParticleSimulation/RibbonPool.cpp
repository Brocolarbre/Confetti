#include "Confetti/ParticleSimulation/RibbonPool.hpp"

namespace cft
{
	void RibbonPool::resize(unsigned int capacity)
	{
		m_ribbonRegistryId.resize(capacity);
		m_fromParticleId.resize(capacity);
		m_toParticleId.resize(capacity);
		m_spawnTime.resize(capacity);
		m_ribbonPoints.resize(capacity);

		m_capacity = capacity;
		m_reservedCapacity = std::min(m_reservedCapacity, m_capacity);
		m_count = std::min(m_count, m_capacity);
	}

	RibbonPool::RibbonPool() :
		m_ribbonRegistryId(),
		m_fromParticleId(),
		m_toParticleId(),
		m_spawnTime(),
		m_ribbonPoints(),
		m_capacity(0),
		m_reservedCapacity(0),
		m_count(0)
	{

	}

	const std::vector<unsigned int>& RibbonPool::getRibbonRegistryId() const
	{
		return m_ribbonRegistryId;
	}

	const std::vector<unsigned int>& RibbonPool::getFromParticleId() const
	{
		return m_fromParticleId;
	}

	const std::vector<unsigned int>& RibbonPool::getToParticleId() const
	{
		return m_toParticleId;
	}

	const std::vector<float>& RibbonPool::getSpawnTime() const
	{
		return m_spawnTime;
	}

	const std::vector<std::deque<TrailPoint>>& RibbonPool::getRibbonPoints() const
	{
		return m_ribbonPoints;
	}

	std::vector<unsigned int>& RibbonPool::getRibbonRegistryId()
	{
		return m_ribbonRegistryId;
	}

	std::vector<unsigned int>& RibbonPool::getFromParticleId()
	{
		return m_fromParticleId;
	}

	std::vector<unsigned int>& RibbonPool::getToParticleId()
	{
		return m_toParticleId;
	}

	std::vector<float>& RibbonPool::getSpawnTime()
	{
		return m_spawnTime;
	}

	std::vector<std::deque<TrailPoint>>& RibbonPool::getRibbonPoints()
	{
		return m_ribbonPoints;
	}

	unsigned int RibbonPool::getCount() const
	{
		return m_count;
	}

	void RibbonPool::reserve(unsigned int capacity)
	{
		if (static_cast<int>(m_capacity) - static_cast<int>(m_count) - static_cast<int>(m_reservedCapacity) < static_cast<int>(capacity))
			resize(m_capacity + capacity);

		m_reservedCapacity += capacity;
	}

	void RibbonPool::insert(const Ribbon& ribbon)
	{
		unsigned int newIndex = m_count++;

		m_ribbonRegistryId[newIndex] = ribbon.ribbonRegistryId;
		m_fromParticleId[newIndex] = ribbon.fromParticleId;
		m_toParticleId[newIndex] = ribbon.toParticleId;
		m_spawnTime[newIndex] = ribbon.spawnTime;
		m_ribbonPoints[newIndex] = ribbon.points;

		--m_reservedCapacity;
	}

	void RibbonPool::remove(unsigned int index)
	{
		unsigned int lastIndex = --m_count;

		m_ribbonRegistryId[index] = m_ribbonRegistryId[lastIndex];
		m_fromParticleId[index] = m_fromParticleId[lastIndex];
		m_toParticleId[index] = m_toParticleId[lastIndex];
		m_spawnTime[index] = m_spawnTime[lastIndex];
		m_ribbonPoints[index] = m_ribbonPoints[lastIndex];
	}
}