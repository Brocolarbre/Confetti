#pragma once

#include "Camera.hpp"
#include "RenderContext.hpp"

#include <Confetti/Confetti.hpp>
#include <Krono/Krono.hpp>
#include <Windove/Window.hpp>

class ConfettiInstance : public dove::EventHandler
{
private:
	RenderContext m_renderContext;
	Camera m_camera;

	krono::Chronometer m_chronometer;
	cft::ParticleSystem m_particleSystem;

	glm::vec2 m_worldSpaceMousePosition;

public:
	ConfettiInstance(unsigned int width, unsigned int height, unsigned int samples, dove::Window& window);

	void onKeyPressed(dove::KeyEvent keyEvent) override;
	void onMouseMoved(unsigned int x, unsigned int y) override;
	void onWindowResized(unsigned int width, unsigned int height) override;

	void update();
	void render() const;
};