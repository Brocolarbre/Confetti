#include "SelectParticleEffectCommand.hpp"

SelectParticleEffectCommand::SelectParticleEffectCommand(ConfettiInstance& confettiInstance, std::optional<unsigned int> id) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id)
{
	
}

void SelectParticleEffectCommand::run()
{
	UserInterfaceState& userInterfaceState = m_confettiInstance.getUserInterfaceState();
	std::optional<unsigned int> id = userInterfaceState.getSelectedParticleEffect();
	userInterfaceState.setSelectedParticleEffect(m_id);
	m_id = id;
}

void SelectParticleEffectCommand::revert()
{
	run();
}