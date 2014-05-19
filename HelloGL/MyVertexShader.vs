#version 150 core

in vec4 aVertex;
in vec2 aTexcoord;
in vec4 aColor;
in vec4 aPosition;

uniform mat4 uPMatrix;
uniform mat4 uVMatrix;
uniform mat4 uMMatrix;

out vec2 vTexcoord;
out vec4 vColor;

void main(){
    gl_Position = uPMatrix * uVMatrix * uMMatrix * (aVertex + aPosition);
    vTexcoord = aTexcoord;
    vColor = aColor;
}