//
//  ParticleContainer.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Container__
#define __HelloGL__Container__

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Container {
    std::vector<glm::vec3> container;
    
public:
    Container(int size);
    virtual ~Container();
    void draw(GLuint vao, GLuint modelLoc);
    double getDelta();
};

#endif /* defined(__HelloGL__ParticleContainer__) */
