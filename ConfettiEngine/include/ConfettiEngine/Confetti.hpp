#pragma once

#include "Particle/ParticleEffect.hpp"
#include "Particle/ParticleEmitter.hpp"
#include "Tools/RandomNumberGenerator.hpp"

#include <unordered_map>

namespace cft
{
	struct Confetti
	{
		std::unordered_map<unsigned int, ParticleEffect> particleEffects;
		std::unordered_map<unsigned int, ParticleEmitter> particleEmitters;
		RandomNumberGenerator randomNumberGenerator;
	};
}