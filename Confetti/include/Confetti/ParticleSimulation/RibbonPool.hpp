#pragma once

#include "Confetti/Particle/Ribbon.hpp"

#include <vector>

namespace cft
{
	class RibbonPool
	{
	private:
		std::vector<unsigned int> m_ribbonRegistryId;
		std::vector<unsigned int> m_fromParticleId;
		std::vector<unsigned int> m_toParticleId;
		std::vector<glm::vec4> m_fromParticleColor;
		std::vector<glm::vec4> m_toParticleColor;
		std::vector<glm::vec4> m_fromColor;
		std::vector<glm::vec4> m_toColor;
		std::vector<glm::vec3> m_fromPosition;
		std::vector<glm::vec3> m_toPosition;
		std::vector<float> m_fromThickness;
		std::vector<float> m_toThickness;
		std::vector<float> m_spawnTime;

		unsigned int m_capacity;
		unsigned int m_reservedCapacity;
		unsigned int m_count;

		void resize(unsigned int capacity);

	public:
		RibbonPool();
		
		const std::vector<unsigned int>& getRibbonRegistryId() const;
		const std::vector<unsigned int>& getFromParticleId() const;
		const std::vector<unsigned int>& getToParticleId() const;
		const std::vector<glm::vec4>& getFromParticleColor() const;
		const std::vector<glm::vec4>& getToParticleColor() const;
		const std::vector<glm::vec4>& getFromColor() const;
		const std::vector<glm::vec4>& getToColor() const;
		const std::vector<glm::vec3>& getFromPosition() const;
		const std::vector<glm::vec3>& getToPosition() const;
		const std::vector<float>& getFromThickness() const;
		const std::vector<float>& getToThickness() const;
		const std::vector<float>& getSpawnTime() const;

		std::vector<unsigned int>& getRibbonRegistryId();
		std::vector<unsigned int>& getFromParticleId();
		std::vector<unsigned int>& getToParticleId();
		std::vector<glm::vec4>& getFromParticleColor();
		std::vector<glm::vec4>& getToParticleColor();
		std::vector<glm::vec4>& getFromColor();
		std::vector<glm::vec4>& getToColor();
		std::vector<glm::vec3>& getFromPosition();
		std::vector<glm::vec3>& getToPosition();
		std::vector<float>& getFromThickness();
		std::vector<float>& getToThickness();
		std::vector<float>& getSpawnTime();

		unsigned int getCount() const;

		void reserve(unsigned int capacity);
		void insert(const Ribbon& ribbon);
		void remove(unsigned int index);
	};
}