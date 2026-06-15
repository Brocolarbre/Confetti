#pragma once

namespace cft
{
	struct SpriteSheet
	{
		unsigned int imageId;
		unsigned int frameCount;
		unsigned int rowFrameCount;
		unsigned int frameWidth;
		unsigned int frameHeight;
		float animationSpeed;
	};
}