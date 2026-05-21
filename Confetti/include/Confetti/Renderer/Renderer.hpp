#pragma once

#include "Framebuffer.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "SSBO.hpp"
#include "View.hpp"

#include "Confetti/Particle/ParticlePool.hpp"

namespace cft
{
	class Renderer
	{
	private:
		unsigned int m_width;
		unsigned int m_height;

		Framebuffer m_framebuffer;
		Shader m_shader;
		Mesh m_mesh;
		SSBO m_ssbo;

	public:
		Renderer(unsigned int width, unsigned int height);

		unsigned int getOutputTextureId() const;

		void resize(unsigned int width, unsigned int height);
		void render(const View& view, const std::unordered_map<unsigned int, ParticlePool>& particlePools);
	};
}