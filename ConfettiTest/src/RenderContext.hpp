#pragma once

#include <Confetti/Rendering/Tool/Shader.hpp>

class RenderContext
{
private:
	cft::Shader m_shader;
	unsigned int m_vertexArray;

	unsigned int m_width;
	unsigned int m_height;

	static bool m_initialized;

public:
	RenderContext(unsigned int width, unsigned int height);
	~RenderContext();

	void resize(unsigned int width, unsigned int height);
	void render(unsigned int outputTextureId) const;

	static bool initialize(void* loader);
};