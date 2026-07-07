#pragma once

namespace cft
{
    constexpr const char* FLARE_DOWNSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;
        uniform vec2 uDirection;

        in vec2 fTextureCoordinates;

        out vec4 downsample;

        void main()
        {
            vec2 direction = normalize(uDirection);
            vec2 texelSize = 1.0 / textureSize(uTexture, 0);
            vec3 result = vec3(0.0);

            float weights[9] = float[](0.02, 0.04, 0.07, 0.12, 0.50, 0.12, 0.07, 0.04, 0.02);

            for(int i = -4; i <= 4; ++i)
            {
                vec2 offset = direction * texelSize * float(i) * 2.0;
                result += texture(uTexture, fTextureCoordinates + offset).rgb * weights[i + 4];
            }

            downsample = vec4(result, 1.0);
        }
	)";

    constexpr const char* FLARE_UPSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
        #version 460 core
        
        uniform sampler2D uTexture;
        uniform vec2 uDirection;
        uniform float uRadius;
        uniform float uChromaticAberrationStrength;
        
        in vec2 fTextureCoordinates;

        out vec4 color;
        
        void main()
        {
            vec2 texelSize = 1.0 / textureSize(uTexture, 0);
            vec2 direction = normalize(uDirection);
            vec2 step = direction * texelSize * uRadius;

            vec2 chromaticAberration = direction * texelSize * uChromaticAberrationStrength;

            vec3 result = vec3(0.0);

            float weights[7] = float[](0.05, 0.15, 0.25, 0.30, 0.25, 0.15, 0.05);

            for (int i = -3; i <= 3; i++)
            {
                vec2 offset = step * float(i);

                float r = texture(uTexture, fTextureCoordinates + offset + chromaticAberration).r;
                float g = texture(uTexture, fTextureCoordinates + offset).g;
                float b = texture(uTexture, fTextureCoordinates + offset - chromaticAberration).b;

                result += vec3(r, g, b) * weights[i + 3];
            }

            color = vec4(result, 1.0);
        }
    )";
}