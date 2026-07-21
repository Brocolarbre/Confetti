#pragma once

#include "Confetti/Data/PathConfiguration.hpp"
#include "Confetti/Simulation/Pool/PathPoint.hpp"

#include <deque>

namespace cft
{
	class ParticleSimulationPath
	{
	public:
		static void update(std::deque<PathPoint>& path, const PathConfiguration& pathConfiguration, const std::vector<glm::vec4>& colorGradient, float elapsedTime);
	};
}