//
//  ParticleContainer.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Container__
#define __HelloGL__Container__

#include "Particle.h"
#include <iostream>
#include <vector>


class Container {
private:
    static const int MAX_PARTICLES = 10000000;

    Particle container[MAX_PARTICLES];
    int numParticles;
    int frameCount;
    int batchSize;
    
    double getDelta();
public:
    Container(int numParticles, int batchSize);
    virtual ~Container();
    GLfloat* getPositionBuffer();
    int update();
    void spawn(int particles);
};

#endif /* defined(__HelloGL__ParticleContainer__) */
