#pragma once

namespace cft
{
    constexpr const char* DOWNSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uSourceTexture;

        in vec2 fTextureCoordinates;

        out vec4 downsample;

        void main()
        {
            vec2 sourceTexelSize = 1.0 / textureSize(uSourceTexture, 0);
            float x = sourceTexelSize.x;
            float y = sourceTexelSize.y;

            vec4 a = texture(uSourceTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y + 2 * y)).rgba;
            vec4 b = texture(uSourceTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y + 2 * y)).rgba;
            vec4 c = texture(uSourceTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y + 2 * y)).rgba;

            vec4 d = texture(uSourceTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y)).rgba;
            vec4 e = texture(uSourceTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y)).rgba;
            vec4 f = texture(uSourceTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y)).rgba;

            vec4 g = texture(uSourceTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y - 2 * y)).rgba;
            vec4 h = texture(uSourceTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y - 2 * y)).rgba;
            vec4 i = texture(uSourceTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y - 2 * y)).rgba;

            vec4 j = texture(uSourceTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y + y)).rgba;
            vec4 k = texture(uSourceTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y + y)).rgba;
            vec4 l = texture(uSourceTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y - y)).rgba;
            vec4 m = texture(uSourceTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y - y)).rgba;

            downsample = e * 0.125;
            downsample += (a + c + g + i) * 0.03125;
            downsample += (b + d + f + h) * 0.0625;
            downsample += (j + k + l + m) * 0.125;
        }
	)";

    constexpr const char* UPSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uSourceTexture;
        uniform float uFilterRadius;

        in vec2 fTextureCoordinates;

        out vec4 upsample;

        void main()
        {
            ivec2 size = textureSize(uSourceTexture, 0);

            float x = uFilterRadius * float(size.y) / float(size.x);
            float y = uFilterRadius;

            vec4 a = texture(uSourceTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y + y)).rgba;
            vec4 b = texture(uSourceTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y + y)).rgba;
            vec4 c = texture(uSourceTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y + y)).rgba;

            vec4 d = texture(uSourceTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y)).rgba;
            vec4 e = texture(uSourceTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y)).rgba;
            vec4 f = texture(uSourceTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y)).rgba;

            vec4 g = texture(uSourceTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y - y)).rgba;
            vec4 h = texture(uSourceTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y - y)).rgba;
            vec4 i = texture(uSourceTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y - y)).rgba;

            upsample = e * 4.0;
            upsample += (b + d + f + h) * 2.0;
            upsample += (a + c + g + i);
            upsample *= 1.0 / 16.0;
        }
	)";

    constexpr const char* BLOOM_FRAGMENT_SHADER_SOURCE = R"(
        #version 460 core
        
        uniform sampler2D uSourceTexture;
        uniform sampler2D uBloomTexture;
        uniform float uBloomStrength;
        
        in vec2 fTextureCoordinates;
        
        out vec4 color;
        
        void main()
        {
            vec3 sourceColor = texture(uSourceTexture, fTextureCoordinates).rgb;
            vec3 bloomColor = texture(uBloomTexture, fTextureCoordinates).rgb;
            
            //color = vec4(mix(sourceColor, bloomColor, uBloomStrength), 1.0);
            color = vec4(sourceColor + bloomColor * uBloomStrength, 1.0);
        }
    )";
}