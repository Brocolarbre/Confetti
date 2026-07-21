#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <optional>
#include <vector>

namespace cft
{
	struct Particle
	{
		glm::vec4 color;
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
		glm::vec3 linearVelocity;
		glm::vec3 angularVelocity;
		glm::vec4 initialColor;
		glm::vec3 initialScale;
		glm::vec3 postBehaviorPosition;
		float phase;
		float lifetime;
		float spawnTime;
		unsigned int id;
		unsigned int particleRegistryId;
	};

	struct ParticleView
	{
		glm::vec4& color;
		const glm::vec3& position;
		const glm::quat& rotation;
		glm::vec3& scale;
		const glm::vec3& linearVelocity;
		const glm::vec3& angularVelocity;
		const glm::vec4& initialColor;
		const glm::vec3& initialScale;
		const glm::vec3& postBehaviorPosition;
		const float& phase;
		const float& lifetime;
		const float& spawnTime;
		const unsigned int& id;
		const unsigned int& particleRegistryId;
	};

	struct ConstantParticleView
	{
		const glm::vec4& color;
		const glm::vec3& position;
		const glm::quat& rotation;
		const glm::vec3& scale;
		const glm::vec3& linearVelocity;
		const glm::vec3& angularVelocity;
		const glm::vec4& initialColor;
		const glm::vec3& initialScale;
		const glm::vec3& postBehaviorPosition;
		const float& phase;
		const float& lifetime;
		const float& spawnTime;
		const unsigned int& id;
		const unsigned int& particleRegistryId;
	};

	class ParticlePool
	{
	private:
		std::vector<glm::vec4> m_color;
		std::vector<glm::vec3> m_position;
		std::vector<glm::quat> m_rotation;
		std::vector<glm::vec3> m_scale;
		std::vector<glm::vec3> m_linearVelocity;
		std::vector<glm::vec3> m_angularVelocity;
		std::vector<glm::vec4> m_initialColor;
		std::vector<glm::vec3> m_initialScale;
		std::vector<glm::vec3> m_postBehaviorPosition;
		std::vector<float> m_phase;
		std::vector<float> m_lifetime;
		std::vector<float> m_spawnTime;
		std::vector<unsigned int> m_id;
		std::vector<unsigned int> m_particleRegistryId;

		std::unordered_map<unsigned int, unsigned int> m_idIndexMapping;

		unsigned int m_storageCapacity;
		unsigned int m_reservedSlots;
		unsigned int m_count;

		void resizeStorage(unsigned int capacity);

	public:
		ParticlePool();

		const std::vector<glm::vec4>& getColor() const;
		const std::vector<glm::vec3>& getPosition() const;
		const std::vector<glm::quat>& getRotation() const;
		const std::vector<glm::vec3>& getScale() const;
		const std::vector<glm::vec3>& getLinearVelocity() const;
		const std::vector<glm::vec3>& getAngularVelocity() const;
		const std::vector<glm::vec4>& getInitialColor() const;
		const std::vector<glm::vec3>& getInitialScale() const;
		const std::vector<glm::vec3>& getPostBehaviorPosition() const;
		const std::vector<float>& getPhase() const;
		const std::vector<float>& getLifetime() const;
		const std::vector<float>& getSpawnTime() const;
		const std::vector<unsigned int>& getId() const;
		const std::vector<unsigned int>& getParticleRegistryId() const;

		std::vector<glm::vec4>& getColor();
		std::vector<glm::vec3>& getPosition();
		std::vector<glm::quat>& getRotation();
		std::vector<glm::vec3>& getScale();
		std::vector<glm::vec3>& getLinearVelocity();
		std::vector<glm::vec3>& getAngularVelocity();
		std::vector<glm::vec4>& getInitialColor();
		std::vector<glm::vec3>& getInitialScale();
		std::vector<glm::vec3>& getPostBehaviorPosition();
		std::vector<float>& getPhase();
		std::vector<float>& getLifetime();
		std::vector<float>& getSpawnTime();
		std::vector<unsigned int>& getId();
		std::vector<unsigned int>& getParticleRegistryId();

		std::optional<unsigned int> getIndex(unsigned int id) const;
		unsigned int getCount() const;

		void reserveSlots(unsigned int slots);
		void insert(const Particle& particle);
		void remove(unsigned int index);

		ParticleView getParticleView(unsigned int index);
		ConstantParticleView getParticleView(unsigned int index) const;
	};
}