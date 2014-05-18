#version 150 core

in vec4 position;
in vec2 texcoord;

uniform mat4 uPMatrix;
uniform mat4 uVMatrix;
uniform mat4 uMMatrix;

out vec2 Texcoord;

void main(){
    gl_Position = uPMatrix * uVMatrix * uMMatrix * position;
    Texcoord = texcoord;
}