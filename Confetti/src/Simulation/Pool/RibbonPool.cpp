#include "Confetti/Simulation/Pool/RibbonPool.hpp"

namespace cft
{
	void RibbonPool::resizeStorage(unsigned int capacity)
	{
		m_ribbonRegistryId.resize(capacity);
		m_fromParticleId.resize(capacity);
		m_toParticleId.resize(capacity);
		m_spawnTime.resize(capacity);
		m_ribbonPoints.resize(capacity);

		m_storageCapacity = capacity;
		m_reservedSlots = std::min(m_reservedSlots, m_storageCapacity);
		m_count = std::min(m_count, m_storageCapacity);
	}

	RibbonPool::RibbonPool() :
		m_ribbonRegistryId(),
		m_fromParticleId(),
		m_toParticleId(),
		m_spawnTime(),
		m_ribbonPoints(),
		m_pointConnections(),
		m_storageCapacity(0),
		m_reservedSlots(0),
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

	const std::vector<std::deque<PathPoint>>& RibbonPool::getRibbonPoints() const
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

	std::vector<std::deque<PathPoint>>& RibbonPool::getRibbonPoints()
	{
		return m_ribbonPoints;
	}

	std::unordered_set<unsigned int>& RibbonPool::getPointConnections(unsigned int particleId)
	{
		return m_pointConnections[particleId];
	}

	unsigned int RibbonPool::getCount() const
	{
		return m_count;
	}

	void RibbonPool::reserveSlots(unsigned int slots)
	{
		if (static_cast<int>(m_storageCapacity) - static_cast<int>(m_count) - static_cast<int>(m_reservedSlots) < static_cast<int>(slots))
			resizeStorage(m_storageCapacity + slots);

		m_reservedSlots += slots;
	}

	void RibbonPool::insert(const Ribbon& ribbon)
	{
		unsigned int newIndex = m_count++;

		m_ribbonRegistryId[newIndex] = ribbon.ribbonRegistryId;
		m_fromParticleId[newIndex] = ribbon.fromParticleId;
		m_toParticleId[newIndex] = ribbon.toParticleId;
		m_spawnTime[newIndex] = ribbon.spawnTime;
		m_ribbonPoints[newIndex] = ribbon.points;

		--m_reservedSlots;

		m_pointConnections[ribbon.fromParticleId].insert(ribbon.toParticleId);
	}

	void RibbonPool::remove(unsigned int index)
	{
		m_pointConnections[m_fromParticleId[index]].erase(m_toParticleId[index]);

		unsigned int lastIndex = --m_count;

		m_ribbonRegistryId[index] = m_ribbonRegistryId[lastIndex];
		m_fromParticleId[index] = m_fromParticleId[lastIndex];
		m_toParticleId[index] = m_toParticleId[lastIndex];
		m_spawnTime[index] = m_spawnTime[lastIndex];
		m_ribbonPoints[index] = m_ribbonPoints[lastIndex];
	}
}