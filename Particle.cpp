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
    life = 0.0f;
    position = glm::vec3(-25.0f + ((double) 40 * rand() / (RAND_MAX)),
                          0.0f + ((double) 20 * rand() / (RAND_MAX)),
                         -35.0f + ((double) 8 * rand() / (RAND_MAX)));
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Particle::getPosition(){
    return position;
}

void Particle::update(){
    life += getDelta();
    velocity = glm::vec3(0.0f, 0.5f * 9.82f * life * getDelta() , 0.0f);
    checkBounds();
    position -= velocity;
}

float Particle::getLife(){
    return life;
}

double Particle::getDelta(){
    return 1.0f / 60.0f;
}

void Particle::checkBounds(){
    if(position.y < -20.0f || position.y > 26.0f)
        velocity *= -1.0f;
}
