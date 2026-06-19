#include "Confetti/Renderer/Mesh/MeshParticleBatch.hpp"

namespace cft
{
	bool MeshParticleBatchKey::operator==(const MeshParticleBatchKey& meshParticleBatchKey) const
	{
		return meshId == meshParticleBatchKey.meshId && textureId == meshParticleBatchKey.textureId;
	}

	size_t MeshParticleBatchKeyHash::operator()(const MeshParticleBatchKey& meshParticleBatchKey) const
	{
		size_t h1 = std::hash<unsigned int>{}(meshParticleBatchKey.meshId);
		size_t h2 = meshParticleBatchKey.textureId.has_value() ? std::hash<unsigned int>{}(*meshParticleBatchKey.textureId) : 0;

		return h1 ^ (h2 << 1);
	}
}