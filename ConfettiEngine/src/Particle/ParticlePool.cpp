#include "ConfettiEngine/Particle/ParticlePool.hpp"

namespace cft
{
	ParticlePool::ParticlePool() :
		color(),
		position(),
		velocity(),
		scale(),
		lifetime(),
		spawnTime(),
		capacity(0),
		count(0)
	{

	}

	void ParticlePool::allocate(unsigned int capacity)
	{
		color.resize(capacity);
		position.resize(capacity);
		velocity.resize(capacity);
		scale.resize(capacity);
		lifetime.resize(capacity);
		spawnTime.resize(capacity);
		capacity = capacity;
		count = glm::min(count, capacity);
	}

	void ParticlePool::add(const ParticleData& data)
	{
		unsigned int newIndex = count++;

		color[newIndex] = data.color;
		position[newIndex] = data.position;
		velocity[newIndex] = data.velocity;
		scale[newIndex] = data.scale;
		lifetime[newIndex] = data.lifetime;
		spawnTime[newIndex] = data.spawnTime;
	}

	void ParticlePool::remove(unsigned int index)
	{
		unsigned int lastIndex = --count;

		color[index] = color[lastIndex];
		position[index] = position[lastIndex];
		velocity[index] = velocity[lastIndex];
		scale[index] = scale[lastIndex];
		lifetime[index] = lifetime[lastIndex];
		spawnTime[index] = spawnTime[lastIndex];
	}
}