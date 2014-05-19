#version 150 core

in vec4 aPosition;
in vec2 aTexcoord;
in vec4 aColor;

uniform mat4 uPMatrix;
uniform mat4 uVMatrix;
uniform mat4 uMMatrix;

out vec2 vTexcoord;
out vec4 vColor;

void main(){
    gl_Position = uPMatrix * uVMatrix * uMMatrix * aPosition;
    vTexcoord = aTexcoord;
    vColor = aColor;
}