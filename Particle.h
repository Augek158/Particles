//
//  Particle.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Particle__
#define __HelloGL__Particle__

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>



class Particle {

private:
    glm::vec3 position;
    glm::vec3 velocity;
    float life;
    float mass;
    bool collision();
    
    
public:
    Particle();
    Particle(glm::vec3 thePosition);
    glm::vec3 getPosition();
    glm::vec3 getVelocity();
    double getDelta();
    float getLife();

    void print();
};

#endif /* defined(__HelloGL__Particle__) */
