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

    constexpr const char* FLARE_FRAGMENT_SHADER_SOURCE = R"(
        #version 460 core
        
        uniform sampler2D uTexture;
        uniform vec2 uDirection;
        uniform int uRadius;
        uniform int uChromaticSeparationStrength;
        
        in vec2 fTextureCoordinates;

        out vec4 color;
        
        void main()
        {
            vec2 texel = 1.0 / textureSize(uTexture, 0);

            vec3 sum = vec3(0.0);
            float sumWeight = 0.0;

            for (int i = -uRadius; i <= uRadius; ++i)
            {
                float x = float(i);

                //float weight = pow(max(0.0, 1.0 - abs(x)/uRadius), 2.0);
                //float weight = 1.0 / (1.0 + abs(x));
                float weight = exp(-x * x / 800.0);

                //vec2 sampleOffset = x;
                vec2 sampleOffset = uDirection * x * texel;
                vec2 chromaticOffset = uDirection * texel * uChromaticSeparationStrength;
                /*float r = texture(uTexture, fTextureCoordinates + sampleOffset + chromaticOffset).r;
                float g = texture(uTexture, fTextureCoordinates + sampleOffset).g;
                float b = texture(uTexture, fTextureCoordinates + sampleOffset - chromaticOffset).b;
                sum += vec3(r, g, b) * weight;*/

                

                vec3 colorSample = texture(uTexture, fTextureCoordinates + vec2(x * texel.x, 0.0)).rgb;
                sum += colorSample * weight;

                sumWeight += weight;                
            }

            color = vec4(sum / sumWeight, 1.0);
        }
    )";
}