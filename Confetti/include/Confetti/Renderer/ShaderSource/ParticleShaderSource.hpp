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

		layout (location = 0) in vec2 vPosition;

		out vec4 fColor;

		uniform mat4 uProjection;
		uniform mat4 uView;

		void main()
		{
			vec3 cameraRight = vec3(uView[0][0], uView[1][0], uView[2][0]);
			vec3 cameraUp = vec3(uView[0][1], uView[1][1], uView[2][1]);

			vec4 color = particleData.particle[gl_InstanceID].color;
			vec3 position = particleData.particle[gl_InstanceID].position.xyz;
			vec2 scale = particleData.particle[gl_InstanceID].scale.xy;

			vec3 vertexPosition = position + cameraRight * vPosition.x * scale.x + cameraUp * vPosition.y * scale.y;

			gl_Position = uProjection * uView * vec4(vertexPosition, 1.0);
			fColor = color;
		}
	)";

	constexpr const char* PARTICLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

		in vec4 fColor;

		out vec4 color;

		void main()
		{
			color = fColor;
		}
	)";
}