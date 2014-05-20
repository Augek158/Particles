//
//  Particle.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Particle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Particle::Particle(){
    life = 10.0f;
    position = glm::vec3(-15.0f + (float)(rand() % 30),
                          15.0f + (float)(rand() % 15),
                         -35.0f + (float)(rand() % 8));
    velocity = glm::vec3(0.0f,  (float)(2 + rand() % 5) * getDelta(), 0.0f);
}

glm::vec3 Particle::getPosition(){
    return position;
}

void Particle::update(){
    life -= getDelta();
    position -= velocity;
}

float Particle::getLife(){
    return life;
}

double Particle::getDelta(){
    return 1.0f / 60.0f;
}
