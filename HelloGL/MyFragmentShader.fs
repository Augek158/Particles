#version 150 core

uniform sampler2D tex;

in vec2 Texcoord;
in vec4 Color;
out vec4 fragData;

void main(){
    fragData = vec4(1.0, 1.0, 1.0, 1.0);
}