#include "SelectParticleSystemCommand.hpp"

SelectParticleSystemCommand::SelectParticleSystemCommand(ConfettiInstance& confettiInstance, std::optional<unsigned int> id) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id)
{
	
}

void SelectParticleSystemCommand::run()
{
	UserInterfaceState& userInterfaceState = m_confettiInstance.getUserInterfaceState();
	std::optional<unsigned int> id = userInterfaceState.getSelectedParticleSystem();
	userInterfaceState.setSelectedParticleSystem(m_id);
	m_id = id;
}

void SelectParticleSystemCommand::revert()
{
	run();
}