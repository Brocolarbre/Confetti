#pragma once

#include <optional>

namespace cft
{
	struct MeshParticleBatch
	{
		unsigned int meshId;
		std::optional<unsigned int> textureId;

		unsigned int firstInstance;
		unsigned int instanceCount;
	};

	struct MeshParticleBatchKey
	{
		unsigned int meshId;
		std::optional<unsigned int> textureId;

		bool operator==(const MeshParticleBatchKey& meshParticleBatchKey) const;
	};

	struct MeshParticleBatchKeyHash
	{
		size_t operator()(const MeshParticleBatchKey& meshParticleBatchKey) const;
	};
}