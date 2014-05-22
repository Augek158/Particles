#version 330 core

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 uPMatrix;
uniform mat4 uVMatrix;
uniform mat4 uMMatrix;


void main(){
    gl_Position = uPMatrix * uVMatrix * uMMatrix * aPosition;
    vColor = aColor;
}