#pragma once

#include "Confetti/Renderer/Tools/Framebuffer.hpp"
#include "Confetti/Renderer/Tools/Shader.hpp"

namespace cft
{
	class BrightPass
	{
	private:
		Framebuffer m_framebuffer;
		Shader m_shader;
		unsigned int m_vertexArray;

		float m_threshold;

	public:
		BrightPass(unsigned int width, unsigned int height, float threshold);
		~BrightPass();

		unsigned int getOutputTexture() const;

		void setThreshold(float threshold);

		void resize(unsigned int width, unsigned int height);
		void render(unsigned int texture);
	};
}