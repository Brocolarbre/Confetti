#pragma once

#include "Confetti/Export.hpp"

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

	struct CONFETTI_API MeshParticleBatchKey
	{
		unsigned int meshId;
		std::optional<unsigned int> textureId;

		bool operator==(const MeshParticleBatchKey& meshParticleBatchKey) const;
	};

	struct CONFETTI_API MeshParticleBatchKeyHash
	{
		size_t operator()(const MeshParticleBatchKey& meshParticleBatchKey) const;
	};
}