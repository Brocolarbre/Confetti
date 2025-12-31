#include "ConfettiEngine/ParticleSimulation.hpp"

namespace cft
{
	ParticleSimulation::ParticleSimulation(unsigned int width, unsigned int height) :
		m_elapsedTimeChronometer(false),
		m_deltaTimeChronometer(false),
		m_particleSystems(),
		m_particleEffects(),
		m_particleEmitters(),
		m_particleOrchestrator(*this),
		m_randomNumberGenerator(),
		m_renderer(width, height)
	{

	}

	void ParticleSimulation::addParticleSystem(unsigned int id, const ParticleSystem& particleSystem)
	{
		m_particleSystems.insert(std::make_pair(id, particleSystem));
	}

	void ParticleSimulation::addParticleEffect(unsigned int id, const ParticleEffect& particleEffect)
	{
		m_particleEffects.insert(std::make_pair(id, particleEffect));
	}

	void ParticleSimulation::addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter)
	{
		m_particleEmitters.insert(std::make_pair(id, particleEmitter));
	}

	void ParticleSimulation::removeParticleSystem(unsigned int id)
	{
		m_particleSystems.erase(id);
	}

	void ParticleSimulation::removeParticleEffect(unsigned int id)
	{
		m_particleEffects.erase(id);
	}

	void ParticleSimulation::removeParticleEmitter(unsigned int id)
	{
		m_particleEmitters.erase(id);
	}

	const ParticleSystem& ParticleSimulation::getParticleSystem(unsigned int id) const
	{
		return m_particleSystems.at(id);
	}

	const ParticleEffect& ParticleSimulation::getParticleEffect(unsigned int id) const
	{
		return m_particleEffects.at(id);
	}

	const ParticleEmitter& ParticleSimulation::getParticleEmitter(unsigned int id) const
	{
		return m_particleEmitters.at(id);
	}

	RandomNumberGenerator& ParticleSimulation::getRandomNumberGenerator()
	{
		return m_randomNumberGenerator;
	}

	Renderer& ParticleSimulation::getRenderer()
	{
		return m_renderer;
	}

	void ParticleSimulation::setSeed(unsigned int seed)
	{
		m_randomNumberGenerator = RandomNumberGenerator(seed);
	}

	void ParticleSimulation::setProgress(float progress)
	{

	}

	void ParticleSimulation::setSize(unsigned int width, unsigned int height)
	{
		m_renderer.resize(width, height);
	}

	void ParticleSimulation::start()
	{
		for (auto& [id, particleSystem] : m_particleSystems)
			m_particleOrchestrator.addParticleSystem(particleSystem);

		m_elapsedTimeChronometer.start();
		m_deltaTimeChronometer.start();
	}

	void ParticleSimulation::stop()
	{
		m_elapsedTimeChronometer.stop();
		m_deltaTimeChronometer.stop();
	}

	void ParticleSimulation::resume()
	{
		m_elapsedTimeChronometer.start();
		m_deltaTimeChronometer.start();
	}

	void ParticleSimulation::reset()
	{
		for (auto& [id, particleSystem] : m_particleSystems)
			m_particleOrchestrator.addParticleSystem(particleSystem);

		m_elapsedTimeChronometer.reset();
		m_deltaTimeChronometer.reset();
	}

	void ParticleSimulation::restart()
	{
		for (auto& [id, particleSystem] : m_particleSystems)
			m_particleOrchestrator.addParticleSystem(particleSystem);

		m_elapsedTimeChronometer.restart();
		m_deltaTimeChronometer.restart();
	}

	void ParticleSimulation::update()
	{
		float elapsedTime = static_cast<float>(m_elapsedTimeChronometer.getElapsedTime().seconds);
		float deltaTime = static_cast<float>(m_deltaTimeChronometer.getElapsedTime().seconds);
		m_deltaTimeChronometer.restart();

		m_particleOrchestrator.update(elapsedTime, deltaTime);
	}

	void ParticleSimulation::render(const View& view)
	{
		std::vector<std::reference_wrapper<const cft::ParticlePool>> particlePools;
		particlePools.reserve(m_particleOrchestrator.getParticleEmitterPools().size());

		for (const auto& [id, pool] : m_particleOrchestrator.getParticleEmitterPools())
			particlePools.push_back(std::cref(pool.getParticlePool()));

		m_renderer.render(view, particlePools);
	}
}