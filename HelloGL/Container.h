//
//  ParticleContainer.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Container__
#define __HelloGL__Container__

// Maximum particles the system can handle.
#define MAX_SIZE 10000000

#include "Particle.h"
#include <iostream>
#include <vector>


class Container {
private:
    int numParticles;
    int frameCount;
    int addedParticles;
    int offset;
    Particle container[MAX_SIZE];
    
    double getDelta();
public:
    Container();
    virtual ~Container();
    GLfloat* getNewParticleData(int particles);
    void spawnParticles(int particles);
    void print();
    int getAddedParticles();
    int getNumberParticles();
};

#endif /* defined(__HelloGL__ParticleContainer__) */
