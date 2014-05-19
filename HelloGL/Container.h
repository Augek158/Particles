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
    
public:
    Container(int size, GLuint vao, GLuint modelLoc);
    virtual ~Container();
    void draw();
    double getDelta();
};

#endif /* defined(__HelloGL__ParticleContainer__) */
