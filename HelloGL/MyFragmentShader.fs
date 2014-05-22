#version 150 core

uniform vec4 color;

out vec4 fragData;

void main(){
    fragData = color;
}