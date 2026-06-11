#pragma once

namespace cft
{
	constexpr const char* PARTICLE_VERTEX_SHADER_SOURCE = R"(
		#version 460 core

		struct Particle
		{
			vec4 color;
			vec4 position;
			vec4 scale;
		};

		layout (std430, binding = 0) buffer ParticleData
		{
			Particle particle[];
		} particleData;

		uniform mat4 uProjection;
		uniform mat4 uView;

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
			vec3 position = particleData.particle[gl_InstanceID].position.xyz;
			vec2 scale = particleData.particle[gl_InstanceID].scale.xy;
			float textureId = particleData.particle[gl_InstanceID].scale.z;

			vec3 vertexPosition = position + cameraRight * vPosition.x * scale.x + cameraUp * vPosition.y * scale.y;

			gl_Position = uProjection * uView * vec4(vertexPosition, 1.0);
			fColor = color;
			fTextureCoordinates = vTextureCoordinates;
			fTextureId = textureId;
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
			if (fTextureId >= 0.0)
				color = texture(uTexture, vec3(fTextureCoordinates, fTextureId)) * fColor;
			else
				color = fColor;
		}
	)";
}