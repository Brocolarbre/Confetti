#pragma once

#include "Framebuffer.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "SSBO.hpp"
#include "View.hpp"

#include "ConfettiEngine/Particle/ParticlePool.hpp"

namespace cft
{
	class Renderer
	{
	private:
		Framebuffer m_framebuffer;
		Shader m_shader;
		Mesh m_mesh;
		SSBO m_ssbo;

		unsigned int m_width;
		unsigned int m_height;

		static bool m_intialized;

	public:
		Renderer(unsigned int width, unsigned int height);

		unsigned int getOutputTextureId() const;

		void resize(unsigned int width, unsigned int height);
		void render(const View& view, const std::vector<std::reference_wrapper<const ParticlePool>>& particlePools);

		static bool initialize(void* loader);
	};
}