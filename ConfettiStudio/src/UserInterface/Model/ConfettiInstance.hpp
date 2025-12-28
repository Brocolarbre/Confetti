#pragma once

#include <ConfettiEngine/Renderer/Renderer.hpp>

class ConfettiInstance
{
private:
	cft::Renderer m_renderer;

public:
	ConfettiInstance();

	cft::Renderer& getRenderer();
};