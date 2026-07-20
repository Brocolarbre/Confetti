#include "Confetti/Simulation/Registry/AssetRegistry.hpp"

namespace cft
{
	void AssetRegistry::addForceField(unsigned int id, std::unique_ptr<ForceField> forceField)
	{
		m_forceFields[id] = std::move(forceField);
	}

	void AssetRegistry::addMotionBehavior(unsigned int id, std::unique_ptr<MotionBehavior> motionBehavior)
	{
		m_motionBehaviors[id] = std::move(motionBehavior);
	}

	void AssetRegistry::addVisualBehavior(unsigned int id, std::unique_ptr<VisualBehavior> visualBehavior)
	{
		m_visualBehaviors[id] = std::move(visualBehavior);
	}

	void AssetRegistry::addParticleSpawner(unsigned int id, std::unique_ptr<ParticleSpawner> particleSpawner)
	{
		m_particleSpawners[id] = std::move(particleSpawner);
	}

	void AssetRegistry::addEmissionPattern(unsigned int id, std::unique_ptr<EmissionPattern> emissionPattern)
	{
		m_emissionPatterns[id] = std::move(emissionPattern);
	}

	void AssetRegistry::addParticleLinker(unsigned int id, std::unique_ptr<ParticleLinker> particleLinker)
	{
		m_particleLinkers[id] = std::move(particleLinker);
	}

	void AssetRegistry::addRibbonGenerator(unsigned int id, std::unique_ptr<RibbonGenerator> ribbonGenerator)
	{
		m_ribbonGenerators[id] = std::move(ribbonGenerator);
	}

	void AssetRegistry::addImage(unsigned int id, Image image)
	{
		m_images[id] = std::move(image);
	}

	void AssetRegistry::addModel(unsigned int id, Model model)
	{
		m_models[id] = std::move(model);
	}

	void AssetRegistry::addSpriteSheetDescriptor(unsigned int id, SpriteSheetDescriptor spriteSheetDescriptor)
	{
		m_spriteSheetDescriptors[id] = std::move(spriteSheetDescriptor);
	}

	void AssetRegistry::addParticleEffectDescriptor(unsigned int id, ParticleEffectDescriptor particleEffectDescriptor)
	{
		m_particleEffectDescriptors[id] = std::move(particleEffectDescriptor);
	}

	void AssetRegistry::addParticleEmitterDescriptor(unsigned int id, ParticleEmitterDescriptor particleEmitterDescriptor)
	{
		m_particleEmitterDescriptors[id] = std::move(particleEmitterDescriptor);
	}

	void AssetRegistry::removeForceField(unsigned int id)
	{
		m_forceFields.erase(id);
	}

	void AssetRegistry::removeMotionBehavior(unsigned int id)
	{
		m_motionBehaviors.erase(id);
	}

	void AssetRegistry::removeVisualBehavior(unsigned int id)
	{
		m_visualBehaviors.erase(id);
	}

	void AssetRegistry::removeParticleSpawner(unsigned int id)
	{
		m_particleSpawners.erase(id);
	}

	void AssetRegistry::removeEmissionPattern(unsigned int id)
	{
		m_emissionPatterns.erase(id);
	}

	void AssetRegistry::removeParticleLinker(unsigned int id)
	{
		m_particleLinkers.erase(id);
	}

	void AssetRegistry::removeRibbonGenerator(unsigned int id)
	{
		m_ribbonGenerators.erase(id);
	}

	void AssetRegistry::removeImage(unsigned int id)
	{
		m_images.erase(id);
	}

	void AssetRegistry::removeModel(unsigned int id)
	{
		m_models.erase(id);
	}

	void AssetRegistry::removeSpriteSheetDescriptor(unsigned int id)
	{
		m_spriteSheetDescriptors.erase(id);
	}

	void AssetRegistry::removeParticleEffectDescriptor(unsigned int id)
	{
		m_particleEffectDescriptors.erase(id);
	}

	void AssetRegistry::removeParticleEmitterDescriptor(unsigned int id)
	{
		m_particleEmitterDescriptors.erase(id);
	}

	const ForceField& AssetRegistry::getForceField(unsigned int id) const
	{
		return *m_forceFields.at(id);
	}

	const MotionBehavior& AssetRegistry::getMotionBehavior(unsigned int id) const
	{
		return *m_motionBehaviors.at(id);
	}

	const VisualBehavior& AssetRegistry::getVisualBehavior(unsigned int id) const
	{
		return *m_visualBehaviors.at(id);
	}

	const ParticleSpawner& AssetRegistry::getParticleSpawner(unsigned int id) const
	{
		return *m_particleSpawners.at(id);
	}

	const EmissionPattern& AssetRegistry::getEmissionPattern(unsigned int id) const
	{
		return *m_emissionPatterns.at(id);
	}

	const ParticleLinker& AssetRegistry::getParticleLinker(unsigned int id) const
	{
		return *m_particleLinkers.at(id);
	}

	const RibbonGenerator& AssetRegistry::getRibbonGenerator(unsigned int id) const
	{
		return *m_ribbonGenerators.at(id);
	}

	const Image& AssetRegistry::getImage(unsigned int id) const
	{
		return m_images.at(id);
	}

	const Model& AssetRegistry::getModel(unsigned int id) const
	{
		return m_models.at(id);
	}

	const SpriteSheetDescriptor& AssetRegistry::getSpriteSheetDescriptor(unsigned int id) const
	{
		return m_spriteSheetDescriptors.at(id);
	}

	const ParticleEffectDescriptor& AssetRegistry::getParticleEffectDescriptor(unsigned int id) const
	{
		return m_particleEffectDescriptors.at(id);
	}

	const ParticleEmitterDescriptor& AssetRegistry::getParticleEmitterDescriptor(unsigned int id) const
	{
		return m_particleEmitterDescriptors.at(id);
	}

	ForceField& AssetRegistry::getForceField(unsigned int id)
	{
		return *m_forceFields.at(id);
	}

	MotionBehavior& AssetRegistry::getMotionBehavior(unsigned int id)
	{
		return *m_motionBehaviors.at(id);
	}

	VisualBehavior& AssetRegistry::getVisualBehavior(unsigned int id)
	{
		return *m_visualBehaviors.at(id);
	}

	ParticleSpawner& AssetRegistry::getParticleSpawner(unsigned int id)
	{
		return *m_particleSpawners.at(id);
	}

	EmissionPattern& AssetRegistry::getEmissionPattern(unsigned int id)
	{
		return *m_emissionPatterns.at(id);
	}

	ParticleLinker& AssetRegistry::getParticleLinker(unsigned int id)
	{
		return *m_particleLinkers.at(id);
	}

	RibbonGenerator& AssetRegistry::getRibbonGenerator(unsigned int id)
	{
		return *m_ribbonGenerators.at(id);
	}

	Image& AssetRegistry::getImage(unsigned int id)
	{
		return m_images.at(id);
	}

	Model& AssetRegistry::getModel(unsigned int id)
	{
		return m_models.at(id);
	}

	SpriteSheetDescriptor& AssetRegistry::getSpriteSheetDescriptor(unsigned int id)
	{
		return m_spriteSheetDescriptors.at(id);
	}

	ParticleEffectDescriptor& AssetRegistry::getParticleEffectDescriptor(unsigned int id)
	{
		return m_particleEffectDescriptors.at(id);
	}

	ParticleEmitterDescriptor& AssetRegistry::getParticleEmitterDescriptor(unsigned int id)
	{
		return m_particleEmitterDescriptors.at(id);
	}

	const std::unordered_map<unsigned int, std::unique_ptr<ForceField>>& AssetRegistry::getForceFields() const
	{
		return m_forceFields;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<MotionBehavior>>& AssetRegistry::getMotionBehaviors() const
	{
		return m_motionBehaviors;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<VisualBehavior>>& AssetRegistry::getVisualBehaviors() const
	{
		return m_visualBehaviors;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>>& AssetRegistry::getParticleSpawners() const
	{
		return m_particleSpawners;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<EmissionPattern>>& AssetRegistry::getEmissionPatterns() const
	{
		return m_emissionPatterns;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<ParticleLinker>>& AssetRegistry::getParticleLinkers() const
	{
		return m_particleLinkers;
	}

	const std::unordered_map<unsigned int, std::unique_ptr<RibbonGenerator>>& AssetRegistry::getRibbonGenerators() const
	{
		return m_ribbonGenerators;
	}

	const std::unordered_map<unsigned int, Image>& AssetRegistry::getImages() const
	{
		return m_images;
	}

	const std::unordered_map<unsigned int, Model>& AssetRegistry::getModels() const
	{
		return m_models;
	}

	const std::unordered_map<unsigned int, SpriteSheetDescriptor>& AssetRegistry::getSpriteSheetDescriptors() const
	{
		return m_spriteSheetDescriptors;
	}

	const std::unordered_map<unsigned int, ParticleEffectDescriptor>& AssetRegistry::getParticleEffectDescriptors() const
	{
		return m_particleEffectDescriptors;
	}

	const std::unordered_map<unsigned int, ParticleEmitterDescriptor>& AssetRegistry::getParticleEmitterDescriptors() const
	{
		return m_particleEmitterDescriptors;
	}
}