#pragma once

namespace cft
{
    constexpr const char* HDR_COMPOSITE_FRAGMENT_SHADER_SOURCE = R"(
        #version 460 core
        
        uniform sampler2D uSourceTexture;
        uniform sampler2D uBloomTexture;
        uniform sampler2D uFlareTexture;
        uniform float uBloomStrength;
        uniform float uFlareStrength;
        
        in vec2 fTextureCoordinates;
        
        out vec4 color;
        
        void main()
        {
            vec3 sourceSample = texture(uSourceTexture, fTextureCoordinates).rgb;
            vec3 bloomSample = texture(uBloomTexture, fTextureCoordinates).rgb;
            vec3 flareSample = texture(uFlareTexture, fTextureCoordinates).rgb;
            
            color = vec4(sourceSample + bloomSample * uBloomStrength + flareSample * uFlareStrength, 1.0);
        }
    )";
}