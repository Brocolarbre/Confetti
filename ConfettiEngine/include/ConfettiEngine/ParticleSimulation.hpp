#pragma once

#include "Particle/ParticleOrchestrator.hpp"
#include "Renderer/Renderer.hpp"

#include <Krono/Krono.hpp>

namespace cft
{
	class ParticleSimulation
	{
	private:
		krono::Chronometer m_elapsedTimeChronometer;
		krono::Chronometer m_deltaTimeChronometer;
		
		std::unordered_map<unsigned int, ParticleSystem> m_particleSystems;
		std::unordered_map<unsigned int, ParticleEffect> m_particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> m_particleEmitters;

		ParticleOrchestrator m_particleOrchestrator;
		RandomNumberGenerator m_randomNumberGenerator;
		Renderer m_renderer;

	public:
		ParticleSimulation(unsigned int width, unsigned int height);

		void addParticleSystem(unsigned int id, const ParticleSystem& particleSystem);
		void addParticleEffect(unsigned int id, const ParticleEffect& particleEffect);
		void addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter);

		void removeParticleSystem(unsigned int id);
		void removeParticleEffect(unsigned int id);
		void removeParticleEmitter(unsigned int id);

		const ParticleSystem& getParticleSystem(unsigned int id) const;
		const ParticleEffect& getParticleEffect(unsigned int id) const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;

		RandomNumberGenerator& getRandomNumberGenerator();
		Renderer& getRenderer();

		void setSeed(unsigned int seed);
		void setProgress(float progress);
		void setSize(unsigned int width, unsigned int height);

		void start();
		void stop();
		void resume();
		void reset();
		void restart();

		void update();
		void render(const View& view);
	};
}