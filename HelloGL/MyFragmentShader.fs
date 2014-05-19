#version 150 core

uniform sampler2D tex;

in vec2 vTexcoord;
in vec4 vColor;
out vec4 fragData;

void main(){
    fragData = vColor;
}