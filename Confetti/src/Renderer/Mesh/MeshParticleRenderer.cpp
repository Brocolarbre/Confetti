#include "Confetti/Renderer/Mesh/MeshParticleRenderer.hpp"
#include "Confetti/Renderer/ShaderSource/MeshParticleShaderSource.hpp"

#include <glad/glad.h>

namespace cft
{
	MeshParticleRenderer::MeshParticleRenderer() :
		m_textures(),
		m_meshes(),
		m_particleBatches(),
		m_particleSsbo(),
		m_shader()
	{
		m_shader.loadFromMemory(std::string(MESH_PARTICLE_VERTEX_SHADER_SOURCE), std::string(MESH_PARTICLE_FRAGMENT_SHADER_SOURCE));
		m_shader.use();
		m_shader.setUniform("uTexture", 0);
	}

	void MeshParticleRenderer::loadTextures(AssetRegistry& assetRegistry, const std::vector<unsigned int>& images)
	{
		m_textures.clear();

		for (unsigned int imageId : images)
		{
			const Image& image = assetRegistry.getImage(imageId);
			unsigned int channelCount = image.getChannelCount();
			Texture texture(GL_TEXTURE_2D, channelCount > 3 ? GL_RGBA8 : GL_RGB8, channelCount > 3 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE);
			texture.load(image.getData().data(), image.getWidth(), image.getHeight(), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, true);
			m_textures.insert({ imageId, std::move(texture) });
		}
	}

	void MeshParticleRenderer::loadMeshes(AssetRegistry& assetRegistry, const std::vector<unsigned int>& models)
	{
		m_meshes.clear();

		for (unsigned int modelId : models)
		{
			const Model& model = assetRegistry.getModel(modelId);
			MeshParticleMesh mesh;

			const std::vector<Vertex>& vertexData = model.getVertexData();
			std::vector<MeshParticleMesh::Vertex> particleMeshVertexData;
			particleMeshVertexData.reserve(vertexData.size());

			for (const Vertex& vertex : vertexData)
				particleMeshVertexData.push_back(MeshParticleMesh::Vertex{ vertex.position, vertex.color, vertex.textureCoordinates });

			mesh.load(particleMeshVertexData, model.getIndexData());
			m_meshes.insert({ modelId, std::move(mesh) });
		}
	}

	void MeshParticleRenderer::update(const std::unordered_map<unsigned int, ParticlePool>& particlePools, const ParticleRegistry& particleRegistry)
	{
		m_particleBatches.clear();
		std::unordered_map<MeshParticleBatchKey, std::vector<MeshParticleSSBO::ParticleData>, MeshParticleBatchKeyHash> particleGroups;

		for (const auto& [id, pool] : particlePools)
		{
			const std::vector<glm::vec4>& color = pool.getColor();
			const std::vector<glm::vec3>& position = pool.getPosition();
			const std::vector<glm::quat>& rotation = pool.getRotation();
			const std::vector<glm::vec3>& scale = pool.getScale();
			const std::vector<unsigned int>& id = pool.getParticleRegistryId();
			unsigned int count = pool.getCount();

			for (unsigned int i = 0; i < count; ++i)
			{
				const ParticleRegistryEntry& entry = particleRegistry.getEntry(id[i]);

				if (entry.renderDescriptor.renderType != RenderType::Mesh)
					continue;

				const MeshRenderDescriptor& descriptor = std::get<MeshRenderDescriptor>(entry.renderDescriptor.descriptorData);

				MeshParticleBatchKey key{ descriptor.modelId, descriptor.imageId };

				glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position[i]);
				glm::mat4 rotationMatrix = glm::mat4_cast(rotation[i]);
				glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale[i]);
				glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

				MeshParticleSSBO::ParticleData particleData{ modelMatrix, color[i] };

				particleGroups[key].push_back(particleData);
			}
		}

		std::vector<MeshParticleSSBO::ParticleData> ssboData;

		size_t totalParticleCount = 0;

		for (const auto& [key, particleGroup] : particleGroups)
			totalParticleCount += particleGroup.size();

		ssboData.reserve(totalParticleCount);

		unsigned int firstInstance = 0;

		for (const auto& [key, particleGroup] : particleGroups)
		{
			MeshParticleBatch batch;

			batch.meshId = key.meshId;
			batch.textureId = key.textureId;
			batch.firstInstance = firstInstance;
			batch.instanceCount = static_cast<unsigned int>(particleGroup.size());

			m_particleBatches.push_back(batch);

			ssboData.insert(ssboData.end(), particleGroup.begin(), particleGroup.end());
			firstInstance += batch.instanceCount;
		}

		m_particleSsbo.bind();
		m_particleSsbo.setData(ssboData);
	}

	void MeshParticleRenderer::render(const View& view) const
	{
		m_particleSsbo.bind();

		m_shader.use();
		m_shader.setUniform("uView", view.viewMatrix);
		m_shader.setUniform("uProjection", view.projectionMatrix);

		Texture::setActiveSlot(0);

		for (const MeshParticleBatch& batch : m_particleBatches)
		{
			bool useTexture = batch.textureId.has_value();
			m_shader.setUniform("uUseTexture", useTexture);

			if (useTexture)
				m_textures.at(batch.textureId.value()).bind();

			m_meshes.at(batch.meshId).drawInstancedBaseInstance(batch.firstInstance, batch.instanceCount);
		}
	}
}