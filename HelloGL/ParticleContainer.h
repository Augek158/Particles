//
//  ParticleContainer.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-18.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__ParticleContainer__
#define __HelloGL__ParticleContainer__

#include <iostream>
#include <vector>
#include "Particle.h"

class ParticleContainer {
private:
    std::vector<Particle> *container;
public:
    ParticleContainer(int size);
    void draw(GLuint VAO);
    void update(GLuint modelLoc);
    unsigned long getSize();
    std::string toString();
};

#endif /* defined(__HelloGL__ParticleContainer__) */
