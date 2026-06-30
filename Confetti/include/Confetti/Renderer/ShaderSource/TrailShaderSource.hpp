#pragma once

namespace cft
{
	constexpr const char* TRAIL_VERTEX_SHADER_SOURCE = R"(
		#version 460 core

		uniform mat4 uProjection;
		uniform mat4 uView;

		layout (location = 0) in vec3 vPosition;
		layout (location = 1) in vec4 vColor;
		layout (location = 2) in vec2 vTextureCoordinates;

		out vec4 fColor;
		out vec2 fTextureCoordinates;

		void main()
		{
			gl_Position = uProjection * uView * vec4(vPosition, 1.0);
			fColor = vColor;
			fTextureCoordinates = vTextureCoordinates;
		}
	)";

	constexpr const char* TRAIL_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

		in vec4 fColor;
		in vec2 fTextureCoordinates;

		out vec4 color;

		void main()
		{
			color = fColor;
		}
	)";
}