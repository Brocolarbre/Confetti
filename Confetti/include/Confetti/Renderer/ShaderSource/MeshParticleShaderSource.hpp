#pragma once

namespace cft
{
	constexpr const char* MESH_PARTICLE_VERTEX_SHADER_SOURCE = R"(
		#version 460 core		

		struct Particle
		{
			mat4 modelMatrix;
			vec4 color;
		};

		layout (std430, binding = 0) buffer ParticleData
		{
			Particle particle[];
		} particleData;

		uniform mat4 uProjection;
		uniform mat4 uView;

		layout (location = 0) in vec3 vPosition;
		layout (location = 1) in vec4 vColor;
		layout (location = 2) in vec2 vTextureCoordinates;

		out vec4 fColor;
		out vec2 fTextureCoordinates;

		void main()
		{
			uint particleIndex = gl_BaseInstance + gl_InstanceID;
			vec4 color = particleData.particle[particleIndex].color;
			mat4 modelMatrix = particleData.particle[particleIndex].modelMatrix;

			gl_Position = uProjection * uView * modelMatrix * vec4(vPosition, 1.0);
			fColor = vColor * color;
			fTextureCoordinates = vTextureCoordinates;
		}
	)";

	constexpr const char* MESH_PARTICLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

		uniform sampler2D uTexture;
		uniform bool uUseTexture;

		in vec4 fColor;
		in vec2 fTextureCoordinates;

		out vec4 color;

		void main()
		{
			if (uUseTexture)
				color = texture(uTexture, fTextureCoordinates) * fColor;
			else
				color = fColor;
		}
	)";
}