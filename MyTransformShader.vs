#version 330 core

layout(location = 1) in vec4 aPosition;
layout(location = 2) in vec3 aVelocity;

out vec4 vPosition;
out vec3 vVelocity;

const float dt = 1.0/60.0;

void main(){
    vPosition = aPosition + vec4(aVelocity * dt, 0.0);
    vVelocity = aVelocity;
}