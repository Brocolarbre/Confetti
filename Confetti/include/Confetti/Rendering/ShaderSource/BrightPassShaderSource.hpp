#pragma once

namespace cft
{
    constexpr const char* BRIGHT_PASS_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;
        uniform float uThreshold;

        in vec2 fTextureCoordinates;

        out vec4 color;

        void main()
        {
            vec3 colorSample = texture(uTexture, fTextureCoordinates).rgb;
            float brightness = max(colorSample.r, max(colorSample.g, colorSample.b));

            if (brightness > uThreshold)
                color = vec4(colorSample, 1.0);
            else
                color = vec4(0.0);
        }
	)";
}