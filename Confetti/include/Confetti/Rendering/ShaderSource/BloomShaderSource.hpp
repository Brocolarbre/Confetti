#pragma once

namespace cft
{
    constexpr const char* BLOOM_DOWNSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;

        in vec2 fTextureCoordinates;

        out vec3 downsample;

        void main()
        {
            vec2 texelSize = 1.0 / textureSize(uTexture, 0);
            float x = texelSize.x;
            float y = texelSize.y;

            vec3 a = texture(uTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y + 2 * y)).rgb;
            vec3 b = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y + 2 * y)).rgb;
            vec3 c = texture(uTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y + 2 * y)).rgb;

            vec3 d = texture(uTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y)).rgb;
            vec3 e = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y)).rgb;
            vec3 f = texture(uTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y)).rgb;

            vec3 g = texture(uTexture, vec2(fTextureCoordinates.x - 2 * x, fTextureCoordinates.y - 2 * y)).rgb;
            vec3 h = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y - 2 * y)).rgb;
            vec3 i = texture(uTexture, vec2(fTextureCoordinates.x + 2 * x, fTextureCoordinates.y - 2 * y)).rgb;

            vec3 j = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y + y)).rgb;
            vec3 k = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y + y)).rgb;
            vec3 l = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y - y)).rgb;
            vec3 m = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y - y)).rgb;

            downsample = e * 0.125;
            downsample += (a + c + g + i) * 0.03125;
            downsample += (b + d + f + h) * 0.0625;
            downsample += (j + k + l + m) * 0.125;
        }
	)";

    constexpr const char* BLOOM_UPSAMPLE_FRAGMENT_SHADER_SOURCE = R"(
		#version 460 core

        uniform sampler2D uTexture;
        uniform float uFilterRadius;

        in vec2 fTextureCoordinates;

        out vec3 upsample;

        void main()
        {
            ivec2 size = textureSize(uTexture, 0);

            float x = uFilterRadius * float(size.y) / float(size.x);
            float y = uFilterRadius;

            vec3 a = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y + y)).rgb;
            vec3 b = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y + y)).rgb;
            vec3 c = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y + y)).rgb;

            vec3 d = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y)).rgb;
            vec3 e = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y)).rgb;
            vec3 f = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y)).rgb;

            vec3 g = texture(uTexture, vec2(fTextureCoordinates.x - x, fTextureCoordinates.y - y)).rgb;
            vec3 h = texture(uTexture, vec2(fTextureCoordinates.x, fTextureCoordinates.y - y)).rgb;
            vec3 i = texture(uTexture, vec2(fTextureCoordinates.x + x, fTextureCoordinates.y - y)).rgb;

            upsample = e * 4.0;
            upsample += (b + d + f + h) * 2.0;
            upsample += (a + c + g + i);
            upsample *= 1.0 / 16.0;
        }
	)";
}