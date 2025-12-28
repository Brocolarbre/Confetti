#include "ConfettiEngine/Renderer/Renderer.hpp"

#include <GL/glew.h>

namespace cft
{
	bool Renderer::m_intialized = false;

	bool Renderer::initialize()
	{
		if (m_intialized)
			return true;

		if (glewInit() == GLEW_OK)
			m_intialized = true;

		return m_intialized;
	}
}