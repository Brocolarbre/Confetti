#pragma once

#include "Confetti/Emission/EmissionPattern/EmissionPattern.hpp"
#include "Confetti/Behavior/Force/ForceField.hpp"
#include "Confetti/Behavior/Motion/MotionBehavior.hpp"
#include "Confetti/Resource/Image.hpp"
#include "Confetti/Resource/Model.hpp"
#include "Confetti/Data/ParticleEffectDescriptor.hpp"
#include "Confetti/Data/ParticleEmitterDescriptor.hpp"
#include "Confetti/Data/SpriteSheetDescriptor.hpp"
#include "Confetti/Behavior/Visual/VisualBehavior.hpp"
#include "Confetti/Simulation/Link/ParticleLinker.hpp"
#include "Confetti/Emission/ParticleSpawner.hpp"

#include <unordered_map>

namespace cft
{
	class AssetRegistry
	{
	private:
		std::unordered_map<unsigned int, std::unique_ptr<ForceField>> m_forceFields;
		std::unordered_map<unsigned int, std::unique_ptr<MotionBehavior>> m_motionBehaviors;
		std::unordered_map<unsigned int, std::unique_ptr<VisualBehavior>> m_visualBehaviors;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>> m_particleSpawners;
		std::unordered_map<unsigned int, std::unique_ptr<EmissionPattern>> m_emissionPatterns;
		std::unordered_map<unsigned int, std::unique_ptr<ParticleLinker>> m_particleLinkers;
		std::unordered_map<unsigned int, Image> m_images;
		std::unordered_map<unsigned int, Model> m_models;
		std::unordered_map<unsigned int, SpriteSheetDescriptor> m_spriteSheetDescriptors;
		std::unordered_map<unsigned int, ParticleEffectDescriptor> m_particleEffectDescriptors;
		std::unordered_map<unsigned int, ParticleEmitterDescriptor> m_particleEmitterDescriptors;

	public:
		void addForceField(unsigned int id, std::unique_ptr<ForceField> forceField);
		void addMotionBehavior(unsigned int id, std::unique_ptr<MotionBehavior> motionBehavior);
		void addVisualBehavior(unsigned int id, std::unique_ptr<VisualBehavior> visualBehavior);
		void addParticleSpawner(unsigned int id, std::unique_ptr<ParticleSpawner> particleSpawner);
		void addEmissionPattern(unsigned int id, std::unique_ptr<EmissionPattern> emissionPattern);
		void addParticleLinker(unsigned int id, std::unique_ptr<ParticleLinker> particleLinker);
		void addImage(unsigned int id, Image image);
		void addModel(unsigned int id, Model model);
		void addSpriteSheetDescriptor(unsigned int id, SpriteSheetDescriptor spriteSheetDescriptor);
		void addParticleEffectDescriptor(unsigned int id, ParticleEffectDescriptor particleEffectDescriptor);
		void addParticleEmitterDescriptor(unsigned int id, ParticleEmitterDescriptor particleEmitterDescriptor);

		void removeForceField(unsigned int id);
		void removeMotionBehavior(unsigned int id);
		void removeVisualBehavior(unsigned int id);
		void removeParticleSpawner(unsigned int id);
		void removeEmissionPattern(unsigned int id);
		void removeParticleLinker(unsigned int id);
		void removeImage(unsigned int id);
		void removeModel(unsigned int id);
		void removeSpriteSheetDescriptor(unsigned int id);
		void removeParticleEffectDescriptor(unsigned int id);
		void removeParticleEmitterDescriptor(unsigned int id);

		const ForceField& getForceField(unsigned int id) const;
		const MotionBehavior& getMotionBehavior(unsigned int id) const;
		const VisualBehavior& getVisualBehavior(unsigned int id) const;
		const ParticleSpawner& getParticleSpawner(unsigned int id) const;
		const EmissionPattern& getEmissionPattern(unsigned int id) const;
		const ParticleLinker& getParticleLinker(unsigned int id) const;
		const Image& getImage(unsigned int id) const;
		const Model& getModel(unsigned int id) const;
		const SpriteSheetDescriptor& getSpriteSheetDescriptor(unsigned int id) const;
		const ParticleEffectDescriptor& getParticleEffectDescriptor(unsigned int id) const;
		const ParticleEmitterDescriptor& getParticleEmitterDescriptor(unsigned int id) const;

		ForceField& getForceField(unsigned int id);
		MotionBehavior& getMotionBehavior(unsigned int id);
		VisualBehavior& getVisualBehavior(unsigned int id);
		ParticleSpawner& getParticleSpawner(unsigned int id);
		EmissionPattern& getEmissionPattern(unsigned int id);
		ParticleLinker& getParticleLinker(unsigned int id);
		Image& getImage(unsigned int id);
		Model& getModel(unsigned int id);
		SpriteSheetDescriptor& getSpriteSheetDescriptor(unsigned int id);
		ParticleEffectDescriptor& getParticleEffectDescriptor(unsigned int id);
		ParticleEmitterDescriptor& getParticleEmitterDescriptor(unsigned int id);

		const std::unordered_map<unsigned int, std::unique_ptr<ForceField>>& getForceFields() const;
		const std::unordered_map<unsigned int, std::unique_ptr<MotionBehavior>>& getMotionBehaviors() const;
		const std::unordered_map<unsigned int, std::unique_ptr<VisualBehavior>>& getVisualBehaviors() const;
		const std::unordered_map<unsigned int, std::unique_ptr<ParticleSpawner>>& getParticleSpawners() const;
		const std::unordered_map<unsigned int, std::unique_ptr<EmissionPattern>>& getEmissionPatterns() const;
		const std::unordered_map<unsigned int, std::unique_ptr<ParticleLinker>>& getParticleLinkers() const;
		const std::unordered_map<unsigned int, Image>& getImages() const;
		const std::unordered_map<unsigned int, Model>& getModels() const;
		const std::unordered_map<unsigned int, SpriteSheetDescriptor>& getSpriteSheetDescriptors() const;
		const std::unordered_map<unsigned int, ParticleEffectDescriptor>& getParticleEffectDescriptors() const;
		const std::unordered_map<unsigned int, ParticleEmitterDescriptor>& getParticleEmitterDescriptors() const;
	};
}