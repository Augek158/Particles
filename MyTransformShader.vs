#version 150 core

in vec4 inPosition;
in vec3 inVelocity;

out vec4 outPosition;
out vec3 outVelocity;

void main(){
    outPosition = inPosition;
    outVelocity = inVelocity;
}