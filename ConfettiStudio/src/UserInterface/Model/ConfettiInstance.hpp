#pragma once

#include "Camera/OrbitCameraController.hpp"

#include <ConfettiEngine/Renderer/Renderer.hpp>
#include <ConfettiEngine/Particle/ParticleEmitterPool.hpp>

#include <krono/Krono.hpp>

class ConfettiInstance
{
private:
	cft::Renderer m_renderer;
	cft::RandomNumberGenerator m_generator;
	cft::ParticleEmitterPool m_particleSystem;
	krono::Chronometer m_elapsedTimeChronometer;
	krono::Chronometer m_deltaTimeChronometer;
	Camera m_camera;
	OrbitCameraController m_cameraController;

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	cft::Renderer& getRenderer();

	void update();
	void render();
};