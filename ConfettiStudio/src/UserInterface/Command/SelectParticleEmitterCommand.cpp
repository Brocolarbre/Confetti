#include "SelectParticleEmitterCommand.hpp"

SelectParticleEmitterCommand::SelectParticleEmitterCommand(ConfettiInstance& confettiInstance, std::optional<unsigned int> id) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id)
{
	
}

void SelectParticleEmitterCommand::run()
{
	UserInterfaceState& userInterfaceState = m_confettiInstance.getUserInterfaceState();
	std::optional<unsigned int> id = userInterfaceState.getSelectedParticleEmitter();
	userInterfaceState.setSelectedParticleEmitter(m_id);
	m_id = id;
}

void SelectParticleEmitterCommand::revert()
{
	run();
}