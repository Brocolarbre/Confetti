#include "Confetti/ParticleSystem.hpp"

namespace cft
{
	ParticleSystem::ParticleSystem(float timeStep, unsigned int width, unsigned int height, unsigned int samples) :
		m_assetRegistry(),
		m_simulation(m_assetRegistry),
		m_renderer(width, height, samples),
		m_timeStep(timeStep),
		m_timeScale(1.0f),
		m_elapsedTime(0.0f),
		m_timeAccumulator(0.0f)
	{

	}

	unsigned int ParticleSystem::getRendererOutputTextureId() const
	{
		return m_renderer.getOutputTextureId();
	}

	void ParticleSystem::resize(unsigned int width, unsigned int height)
	{
		m_renderer.resize(width, height);
	}

	void ParticleSystem::clear()
	{
		ParticleSpawner::resetNextId();
		m_simulation.clear();
	}

	void ParticleSystem::setTimeScale(float timeScale)
	{
		m_timeScale = timeScale;
	}

	void ParticleSystem::playEffect(unsigned int id, float delay)
	{
		m_simulation.addParticleEffect(id, m_elapsedTime + delay);
	}

	void ParticleSystem::update(float deltaTime, const View& view)
	{
		float scaledDeltaTime = deltaTime * m_timeScale;

		m_elapsedTime += scaledDeltaTime;
		m_timeAccumulator += scaledDeltaTime;

		while (m_timeAccumulator >= m_timeStep)
		{
			m_simulation.update(m_elapsedTime, scaledDeltaTime);
			m_renderer.update(m_simulation, m_assetRegistry, view, m_elapsedTime);

			m_timeAccumulator -= m_timeStep;
		}
	}

	void ParticleSystem::render(const View& view) const
	{
		m_renderer.render(view, m_simulation.getParticlePools(), m_simulation.getParticleRegistry(), m_assetRegistry);
	}
}