//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"

Container::Container(int numParticles, int batchSize){
    this->numParticles = numParticles;
    this->batchSize = batchSize;
    for (int i = 0; i < numParticles; i++) {
        container[i] = *new Particle();
    }
    frameCount = 0;
}

Container::~Container(){
    
}

GLfloat* Container::getPositionBuffer(){
    
    GLfloat* positionBuffer = new GLfloat[4*numParticles];
    int index = 0;
    for(int i = 0; i < numParticles; i++){
        Particle& p = container[i];
        p.update();
        positionBuffer[index] = p.getPosition().x;
        positionBuffer[index + 1] = p.getPosition().y;
        positionBuffer[index + 2] = p.getPosition().z;
        positionBuffer[index + 3] = 1.0f;
        index += 4;
    }
    return positionBuffer;
}

/*
Spawn batchSize particles twice a second. Returns the size of the array with the new particles.
*/
int Container::update(){
    frameCount++;
    if(frameCount % 5 == 0){
        spawn(batchSize);
        frameCount = 0;
        printf("Particles: %d\n", numParticles);
    }
    return numParticles;
}

/*
Spawns new particles to the system.
*/
void Container::spawn(int particles){
    if((numParticles + particles) < MAX_PARTICLES){ // If there are room for the new particles.
        for(int i = numParticles; i < (numParticles + particles); i++){
            container[i] = *new Particle();
        }
        numParticles += particles; // Update number of particles in system.
    } else{
        printf("Too many particles! Cannot add %d particles\n", particles);
    }
    
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}