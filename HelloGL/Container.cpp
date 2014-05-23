//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"

/*
 Default constructor
 */
Container::Container(){
        
    for(int i = 0; i < MAX_SIZE; i++){
        container[i] = *new Particle();
    }
    offset = 0;
}

Container::~Container(){
    
}

/*
 This function generates a subbuffer with the positions and velocities
 of new particles. The subbuffer can then be used to populate a GL_ARRAY_BUFFER.
*/
GLfloat* Container::getNewParticleData(int particles){
    
    // Return nullptr if theres no room for more particles
    if(offset + particles > MAX_SIZE) return nullptr;
    
    GLfloat* subBuffer = new GLfloat[7 * particles];
    int index = 0;
    
    // Populating the subbuffer
    for(int i = offset; i < offset + particles; i++){
        Particle &p = container[i];
        for (int j = 0; j < 3; j++) {
            subBuffer[index + j] = p.getPosition()[j];
        }
        
        // set w-cordinate = 1.0
        subBuffer[index + 3] = 1.0;
        for(int j = 0; j < 3; j++){
            subBuffer[index + 4 + j] = p.getVelocity()[j];
        }
        index+=7;
    }
    
    // Update values so next call on this function is correct.
    addedParticles = particles;
    offset += particles;
    return subBuffer;
}

void Container::print(){
    for(int i = 0; i < offset; i++){
        container[i].print();
        printf("\n");
    }
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}

int Container::getAddedParticles(){
    return addedParticles;
}

int Container::getNumberParticles(){
    return offset;
}

