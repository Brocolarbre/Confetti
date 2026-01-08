#include "SelectParticleEffectCommand.hpp"

SelectParticleEffectCommand::SelectParticleEffectCommand(ConfettiInstance& confettiInstance, const std::optional<std::string>& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_name(name)
{
	
}

void SelectParticleEffectCommand::run()
{
	UserInterfaceState& userInterfaceState = m_confettiInstance.getUserInterfaceState();
	std::optional<std::string> name = userInterfaceState.getSelectedParticleEffect();
	userInterfaceState.setSelectedParticleEffect(m_name);
	m_name = name;
}

void SelectParticleEffectCommand::revert()
{
	run();
}