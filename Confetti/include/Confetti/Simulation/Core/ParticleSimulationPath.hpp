#pragma once

#include "Confetti/Export.hpp"
#include "Confetti/Data/PathConfiguration.hpp"
#include "Confetti/Simulation/Pool/PathPoint.hpp"

#include <deque>

namespace cft
{
	class CONFETTI_API ParticleSimulationPath
	{
	public:
		static void update(std::deque<PathPoint>& path, const PathConfiguration& pathConfiguration, const std::vector<glm::vec4>& colorGradient, float elapsedTime);
	};
}