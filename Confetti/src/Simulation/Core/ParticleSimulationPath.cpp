#include "Confetti/Simulation/Core/ParticleSimulationPath.hpp"

namespace cft
{
	void ParticleSimulationPath::update(std::deque<PathPoint>& path, const PathConfiguration& pathConfiguration, const std::vector<glm::vec4>& colorGradient, float elapsedTime)
	{
		unsigned int trailSize = static_cast<unsigned int>(path.size());
		unsigned int colorGradientSize = static_cast<unsigned int>(colorGradient.size());

		for (unsigned int pointIndex = 0; pointIndex < path.size(); ++pointIndex)
		{
			float t = 1.0f - (trailSize > 1 ? static_cast<float>(pointIndex) / static_cast<float>(trailSize - 1) : 0.0f);

			switch (pathConfiguration.thicknessDistribution)
			{
			case ThicknessDistribution::Linear: path[pointIndex].thickness = glm::mix(pathConfiguration.startThickness, pathConfiguration.endThickness, t); break;
			case ThicknessDistribution::Quadratic: path[pointIndex].thickness = glm::mix(pathConfiguration.startThickness, pathConfiguration.endThickness, t * t); break;
			}

			if (pathConfiguration.thicknessEvolution.has_value())
			{
				const ThicknessEvolution& trailThicknessEvolution = pathConfiguration.thicknessEvolution.value();
				float pointAge = (elapsedTime - path[pointIndex].spawnTime);

				switch (trailThicknessEvolution.distribution)
				{
				case ThicknessEvolutionDistribution::Constant: path[pointIndex].thickness += pointAge * trailThicknessEvolution.speed; break;
				case ThicknessEvolutionDistribution::Linear: path[pointIndex].thickness += t * pointAge * trailThicknessEvolution.speed; break;
				case ThicknessEvolutionDistribution::Quadratic: path[pointIndex].thickness += t * t * pointAge * trailThicknessEvolution.speed; break;
				}

				path[pointIndex].thickness = glm::max(path[pointIndex].thickness, 0.0f);
			}

			switch (pathConfiguration.colorInterpolation)
			{
			case ColorInterpolation::Constant:
			{
				if (pathConfiguration.colorStart.has_value())
				{
					const std::vector<float>& colorStart = pathConfiguration.colorStart.value();
					float distanceFromHead = path.back().distanceOnPath - path[pointIndex].distanceOnPath;

					size_t count = std::min(colorGradient.size(), colorStart.size());
					unsigned int colorIndex = colorGradientSize - 1;
					for (unsigned int j = 0; j < count; ++j)
					{
						if (distanceFromHead <= colorStart[j])
						{
							colorIndex = j;
							break;
						}
					}

					path[pointIndex].color = colorGradient[colorIndex];
				}
				else
				{
					unsigned int colorIndex = glm::min(static_cast<unsigned int>(t * colorGradientSize), colorGradientSize - 1);
					path[pointIndex].color = colorGradient[colorIndex];
				}
				break;
			}
			case ColorInterpolation::Linear:
			{
				if (pathConfiguration.colorStart.has_value())
				{
					const std::vector<float>& colorStart = pathConfiguration.colorStart.value();
					float distanceFromHead = path.back().distanceOnPath - path[pointIndex].distanceOnPath;

					size_t intervalCount = std::min(colorStart.size(), colorGradient.size() > 0 ? colorGradient.size() - 1 : 0);
					if (intervalCount == 0)
						break;

					if (distanceFromHead >= colorStart.back())
					{
						path[pointIndex].color = colorGradient.back();
					}
					else
					{
						for (size_t j = 0; j < intervalCount; ++j)
						{
							float start = (j == 0) ? 0.0f : colorStart[j - 1];
							float end = colorStart[j];

							if (distanceFromHead <= end)
							{
								float t = (distanceFromHead - start) / (end - start);
								t = glm::clamp(t, 0.0f, 1.0f);

								path[pointIndex].color = glm::mix(colorGradient[j], colorGradient[j + 1], t);

								break;
							}
						}
					}
				}
				else
				{
					float integralPart;
					float colorT = std::modf(t * static_cast<float>(colorGradientSize - 1), &integralPart);

					unsigned int colorIndexA = static_cast<unsigned int>(integralPart);
					unsigned int colorIndexB = glm::min(colorIndexA + 1, colorGradientSize - 1);
					path[pointIndex].color = glm::mix(colorGradient[colorIndexA], colorGradient[colorIndexB], colorT);
				}
				break;
			}
			}

			if (pathConfiguration.lifetimeFade.has_value())
			{
				float start = pathConfiguration.lifetimeFade.value().start;
				float end = pathConfiguration.lifetimeFade.value().end;

				float age = elapsedTime - path[pointIndex].spawnTime;
				float trailFadeT = end > start ? (glm::clamp(age, start, end) - start) / (end - start) : 1.0f;

				path[pointIndex].color.a *= 1.0f - trailFadeT;
			}
		}

		if (pathConfiguration.lifetime.has_value())
		{
			while (!path.empty() && elapsedTime >= path.front().spawnTime + pathConfiguration.lifetime.value())
				path.pop_front();
		}
	}
}