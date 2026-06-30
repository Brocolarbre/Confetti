#pragma once

#include "TrailMesh.hpp"
#include "Confetti/ParticleSimulation/TrailPool.hpp"
#include "Confetti/Renderer/View.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"

namespace cft
{
	class TrailRenderer
	{
	private:
		TrailMesh m_trailMesh;
		Shader m_shader;

	public:
		TrailRenderer();

		void update(const std::unordered_map<unsigned int, TrailPool>& trailPools, const View& view);
		void render(const View& view) const;
	};
}