#include "Confetti/ParticleSimulation/RibbonPool.hpp"

namespace cft
{
	void RibbonPool::resize(unsigned int capacity)
	{
		m_ribbonRegistryId.resize(capacity);
		m_fromParticleId.resize(capacity);
		m_toParticleId.resize(capacity);
		m_fromParticleColor.resize(capacity);
		m_toParticleColor.resize(capacity);
		m_fromColor.resize(capacity);
		m_toColor.resize(capacity);
		m_fromPosition.resize(capacity);
		m_toPosition.resize(capacity);
		m_fromThickness.resize(capacity);
		m_toThickness.resize(capacity);
		m_spawnTime.resize(capacity);

		m_capacity = capacity;
		m_reservedCapacity = std::min(m_reservedCapacity, m_capacity);
		m_count = std::min(m_count, m_capacity);
	}

	RibbonPool::RibbonPool() :
		m_ribbonRegistryId(),
		m_fromParticleId(),
		m_toParticleId(),
		m_fromParticleColor(),
		m_toParticleColor(),
		m_fromColor(),
		m_toColor(),
		m_fromPosition(),
		m_toPosition(),
		m_fromThickness(),
		m_toThickness(),
		m_spawnTime(),
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

	const std::vector<glm::vec4>& RibbonPool::getFromParticleColor() const
	{
		return m_fromParticleColor;
	}

	const std::vector<glm::vec4>& RibbonPool::getToParticleColor() const
	{
		return m_toParticleColor;
	}

	const std::vector<glm::vec4>& RibbonPool::getFromColor() const
	{
		return m_fromColor;
	}

	const std::vector<glm::vec4>& RibbonPool::getToColor() const
	{
		return m_toColor;
	}

	const std::vector<glm::vec3>& RibbonPool::getFromPosition() const
	{
		return m_fromPosition;
	}

	const std::vector<glm::vec3>& RibbonPool::getToPosition() const
	{
		return m_toPosition;
	}

	const std::vector<float>& RibbonPool::getFromThickness() const
	{
		return m_fromThickness;
	}

	const std::vector<float>& RibbonPool::getToThickness() const
	{
		return m_toThickness;
	}

	const std::vector<float>& RibbonPool::getSpawnTime() const
	{
		return m_spawnTime;
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

	std::vector<glm::vec4>& RibbonPool::getFromParticleColor()
	{
		return m_fromParticleColor;
	}

	std::vector<glm::vec4>& RibbonPool::getToParticleColor()
	{
		return m_toParticleColor;
	}

	std::vector<glm::vec4>& RibbonPool::getFromColor()
	{
		return m_fromColor;
	}

	std::vector<glm::vec4>& RibbonPool::getToColor()
	{
		return m_toColor;
	}

	std::vector<glm::vec3>& RibbonPool::getFromPosition()
	{
		return m_fromPosition;
	}

	std::vector<glm::vec3>& RibbonPool::getToPosition()
	{
		return m_toPosition;
	}

	std::vector<float>& RibbonPool::getFromThickness()
	{
		return m_fromThickness;
	}

	std::vector<float>& RibbonPool::getToThickness()
	{
		return m_toThickness;
	}

	std::vector<float>& RibbonPool::getSpawnTime()
	{
		return m_spawnTime;
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
		m_fromParticleColor[newIndex] = ribbon.fromParticleColor;
		m_toParticleColor[newIndex] = ribbon.toParticleColor;
		m_fromColor[newIndex] = ribbon.fromColor;
		m_toColor[newIndex] = ribbon.toColor;
		m_fromPosition[newIndex] = ribbon.fromPosition;
		m_toPosition[newIndex] = ribbon.toPosition;
		m_fromThickness[newIndex] = ribbon.fromThickness;
		m_toThickness[newIndex] = ribbon.toThickness;
		m_spawnTime[newIndex] = ribbon.spawnTime;

		--m_reservedCapacity;
	}

	void RibbonPool::remove(unsigned int index)
	{
		unsigned int lastIndex = --m_count;

		m_ribbonRegistryId[index] = m_ribbonRegistryId[lastIndex];
		m_fromParticleId[index] = m_fromParticleId[lastIndex];
		m_toParticleId[index] = m_toParticleId[lastIndex];
		m_fromParticleColor[index] = m_fromParticleColor[lastIndex];
		m_toParticleColor[index] = m_toParticleColor[lastIndex];
		m_fromColor[index] = m_fromColor[lastIndex];
		m_toColor[index] = m_toColor[lastIndex];
		m_fromPosition[index] = m_fromPosition[lastIndex];
		m_toPosition[index] = m_toPosition[lastIndex];
		m_fromThickness[index] = m_fromThickness[lastIndex];
		m_toThickness[index] = m_toThickness[lastIndex];
		m_spawnTime[index] = m_spawnTime[lastIndex];
	}
}