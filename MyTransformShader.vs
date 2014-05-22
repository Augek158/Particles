#version 150 core

in vec4 aPosition;
in vec3 aVelocity;

out vec4 vPosition;
out vec3 vVelocity;

void main(){
    vPosition = aPosition;
    vVelocity = aVelocity;
}