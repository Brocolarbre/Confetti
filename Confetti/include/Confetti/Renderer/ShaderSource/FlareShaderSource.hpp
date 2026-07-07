#pragma once

namespace cft
{
    constexpr const char* FLARE_DOWNSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;
        uniform vec2 uDirection;

        in vec2 fTextureCoordinates;

        out vec3 downsample;

        void main()
        {
            vec2 direction = normalize(uDirection);
            vec2 texelSize = 1.0 / textureSize(uTexture, 0);
            downsample = vec3(0.0);

            float weights[9] = float[](0.015, 0.035, 0.075, 0.15, 0.45, 0.15, 0.075, 0.035, 0.015);

            for(int i = -4; i <= 4; ++i)
            {
                vec2 offset = direction * texelSize * float(i) * 2.0;
                downsample += texture(uTexture, fTextureCoordinates + offset).rgb * weights[i + 4];
            }
        }
	)";

    constexpr const char* FLARE_UPSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
        #version 460 core
        
        uniform sampler2D uTexture;
        uniform vec2 uDirection;
        uniform float uRadius;
        uniform float uChromaticAberrationStrength;
        uniform uint uMipLevel;
        
        in vec2 fTextureCoordinates;

        out vec3 upsample;
        
        void main()
        {
            vec2 texelSize = 1.0 / textureSize(uTexture, 0);
            vec2 direction = normalize(uDirection);
            vec2 step = direction * texelSize * uRadius * exp2(float(uMipLevel));

            vec2 chromaticAberration = direction * texelSize * uChromaticAberrationStrength;

            upsample = vec3(0.0);

            float weights[7] = float[](0.035, 0.10, 0.22, 0.29, 0.22, 0.10, 0.035);

            for (int i = -3; i <= 3; i++)
            {
                vec2 offset = step * float(i);

                float r = texture(uTexture, fTextureCoordinates + offset + chromaticAberration).r;
                float g = texture(uTexture, fTextureCoordinates + offset).g;
                float b = texture(uTexture, fTextureCoordinates + offset - chromaticAberration).b;

                upsample += vec3(r, g, b) * weights[i + 3];
            }
        }
    )";
}