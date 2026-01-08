#include "SelectParticleEmitterCommand.hpp"

SelectParticleEmitterCommand::SelectParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::optional<std::string>& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_name(name)
{
	
}

void SelectParticleEmitterCommand::run()
{
	UserInterfaceState& userInterfaceState = m_confettiInstance.getUserInterfaceState();
	std::optional<std::string> name = userInterfaceState.getSelectedParticleEmitter();
	userInterfaceState.setSelectedParticleEmitter(m_name);
	m_name = name;
}

void SelectParticleEmitterCommand::revert()
{
	run();
}