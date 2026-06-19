#pragma once

#include <optional>
#include <variant>

namespace cft
{
	enum class RenderType
	{
		Billboard,
		Mesh
	};

	struct BillboardRenderDescriptor
	{
		std::optional<unsigned int> spriteSheet;
	};

	struct MeshRenderDescriptor
	{
		unsigned int mesh;
		std::optional<unsigned int> colorTexture;
	};

	struct RenderDescriptor
	{
		RenderType renderType;
		std::variant<BillboardRenderDescriptor, MeshRenderDescriptor> descriptorData;
	};
}