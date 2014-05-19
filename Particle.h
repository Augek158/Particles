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
    
public:
    Particle();
    void draw(GLuint vao, GLuint modelLoc);
    double getDelta();
};

#endif /* defined(__HelloGL__Particle__) */
