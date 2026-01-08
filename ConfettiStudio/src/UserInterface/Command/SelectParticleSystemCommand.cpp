#include "SelectParticleSystemCommand.hpp"

SelectParticleSystemCommand::SelectParticleSystemCommand(ConfettiInstance& confettiInstance, const std::optional<std::string>& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_name(name)
{
	
}

void SelectParticleSystemCommand::run()
{
	UserInterfaceState& userInterfaceState = m_confettiInstance.getUserInterfaceState();
	std::optional<std::string> name = userInterfaceState.getSelectedParticleSystem();
	userInterfaceState.setSelectedParticleSystem(m_name);
	m_name = name;
}

void SelectParticleSystemCommand::revert()
{
	run();
}