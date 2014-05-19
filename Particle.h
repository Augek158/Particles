//
//  Particle.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-18.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Particle__
#define __HelloGL__Particle__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
class Particle {
public:
    Particle(glm::vec3 _position);
    void draw(GLuint VAO);
    void update(GLuint modelLoc);
    glm::vec3 getPosition();
    std::string toString();
private:
    double getDelta();
    glm::vec3 position;
};

#endif /* defined(__HelloGL__Particle__) */
