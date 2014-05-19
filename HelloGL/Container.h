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
    std::vector<Particle> container;
    GLuint vao;
    GLuint modelLoc;
    int max;
    int frameCount;
    int batchSize;
public:
    Container(int max, int batchSize, GLuint vao, GLuint modelLoc);
    virtual ~Container();
    void draw();
    void spawn();
    double getDelta();
};

#endif /* defined(__HelloGL__ParticleContainer__) */
