#pragma once

#include "UniqueIdGenerator.hpp"
#include "Camera/OrbitCameraController.hpp"

#include <ConfettiEngine/Particle/ParticleSimulation.hpp>
#include <ConfettiEngine/Renderer/Renderer.hpp>
#include <Krono/Krono.hpp>

struct IdGenerators
{
	UniqueIdGenerator system;
	UniqueIdGenerator effect;
	UniqueIdGenerator emitter;
	UniqueIdGenerator forceField;
};

class ConfettiInstance
{
private:
	Camera m_camera;
	OrbitCameraController m_cameraController;
	IdGenerators m_idGenerators;
	cft::ParticleSimulation m_particleSimulation;
	cft::Renderer m_renderer;
	krono::Chronometer m_elapsedTimeChronometer;
	krono::Chronometer m_deltaTimeChronometer;

	void restartSimulation();

public:
	ConfettiInstance(unsigned int width, unsigned int height, dove::Window& window);

	Camera& getCamera();
	IdGenerators& getIdGenerators();
	cft::Renderer& getRenderer();
	cft::ParticleSimulation& getParticleSimulation();

	void update();
	void render();
};