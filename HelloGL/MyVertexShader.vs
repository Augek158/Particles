#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;

uniform mat4 uPMatrix;
uniform mat4 uVMatrix;
uniform mat4 uMMatrix;

out vec2 Texcoord;

void main(){
    gl_Position = uPMatrix * uVMatrix * uMMatrix * position;
    Texcoord = texcoord;
}