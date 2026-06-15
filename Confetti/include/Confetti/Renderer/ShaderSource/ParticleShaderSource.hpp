#pragma once

namespace cft
{
	constexpr const char* PARTICLE_VERTEX_SHADER_SOURCE = R"(
		#version 460 core

		uniform sampler2DArray uTexture;

		struct Particle
		{
			vec4 color;
			vec4 positionPhase;
			vec4 scaleSpriteSheetIdTextureId;
		};

		struct SpriteSheet
		{
			uvec2 frameSize;
			uint frameCount;
			uint rowFrameCount;
			float animationSpeed;
			vec3 padding;
		};

		layout (std430, binding = 0) buffer ParticleData
		{
			Particle particle[];
		} particleData;

		layout (std430, binding = 1) buffer SpriteSheetData
		{
			SpriteSheet spriteSheet[];
		} spriteSheetData;

		uniform mat4 uProjection;
		uniform mat4 uView;
		uniform float uTime;

		layout (location = 0) in vec2 vPosition;
		layout (location = 1) in vec2 vTextureCoordinates;

		out vec4 fColor;
		out vec2 fTextureCoordinates;
		flat out float fTextureId;

		void main()
		{
			vec3 cameraRight = vec3(uView[0][0], uView[1][0], uView[2][0]);
			vec3 cameraUp = vec3(uView[0][1], uView[1][1], uView[2][1]);

			vec4 color = particleData.particle[gl_InstanceID].color;
			vec3 position = particleData.particle[gl_InstanceID].positionPhase.xyz;
			vec2 scale = particleData.particle[gl_InstanceID].scaleSpriteSheetIdTextureId.xy;
			float phase = particleData.particle[gl_InstanceID].positionPhase.w;
			float spriteSheetId = particleData.particle[gl_InstanceID].scaleSpriteSheetIdTextureId.z;
			float textureId = particleData.particle[gl_InstanceID].scaleSpriteSheetIdTextureId.w;

			vec3 vertexPosition = position + cameraRight * vPosition.x * scale.x + cameraUp * vPosition.y * scale.y;

			gl_Position = uProjection * uView * vec4(vertexPosition, 1.0);
			fColor = color;

			if (spriteSheetId < 0.0)
			{
				fTextureCoordinates = vTextureCoordinates;
				fTextureId = -1.0;
			}
			else
			{
				SpriteSheet spriteSheet = spriteSheetData.spriteSheet[uint(spriteSheetId)];
				float animationTime = uTime * spriteSheet.animationSpeed + phase;
				uint frame = uint(animationTime) % spriteSheet.frameCount;
				uint column = frame % spriteSheet.rowFrameCount;
				uint row = frame / spriteSheet.rowFrameCount;
				row = (spriteSheet.frameCount - 1) / spriteSheet.rowFrameCount - row;

				vec2 frameOffset = vec2(column, row) * vec2(spriteSheet.frameSize);

				fTextureCoordinates = (frameOffset + vTextureCoordinates * vec2(spriteSheet.frameSize)) / vec2(textureSize(uTexture, 0).xy);
				fTextureId = textureId;
			}
		}
	)";

	constexpr const char* PARTICLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

		uniform sampler2DArray uTexture;

		in vec4 fColor;
		in vec2 fTextureCoordinates;
		flat in float fTextureId;

		out vec4 color;

		void main()
		{
			if (fTextureId < 0.0)
				color = fColor;
			else
				color = texture(uTexture, vec3(fTextureCoordinates, fTextureId)) * fColor;
		}
	)";
}