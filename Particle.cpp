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
#include <math.h>
#include "Physics.h"



Particle::Particle(){

    gravity = -9.82 / 10;
    still =false;
    mass = 1.0;
    life = 0.0f;
    
    //Give a random position in each direction to the particle,
    //within the boundings of the vertex shader.
    position = glm::vec3(-10.0f + ((double) 20 * rand() / (RAND_MAX)),
                          -10.0f + ((double) 20 * rand() / (RAND_MAX)),
                         -10.0f + ((double) 20 * rand() / (RAND_MAX)));

    //Give a random speed in each direction to the particle
    float speedX = -2 + 4* ((double) rand() / (RAND_MAX));
    float speedY = -2 + 4* ((double) rand() / (RAND_MAX));
    float speedZ = -2 + 4* ((double) rand() / (RAND_MAX));
    velocity = glm::vec3(0.2*speedX, 0.2*speedY, 0.2*speedZ);
}

glm::vec3 Particle::getPosition(){
    return position;
}

glm::vec3 Particle::getVelocity(){
    return velocity;
}

float Particle::getLife(){
    return life;
}

double Particle::getDelta(){
    return 1.0f / 60.0f;
}

bool Particle::collision(){
    
    GLfloat a = velocity.y * velocity.y;
    GLfloat b = 2*velocity.y* (position.y - BoundingSouth);
    GLfloat c = (position.y - BoundingSouth) * (position.y - BoundingSouth);
    
    GLfloat distance = 0; //?


    GLfloat time = ( -b +- sqrt( b*b - 4*a*( c - distance) ) ) / (2 * a);

    return false;
}

void Particle::print(){
    std::string signs[7] = {"x","y","z","w", "vX", "vY", "vZ"};
    for (int i = 0; i < 3; i++) {
        printf("%s: %f ",signs[i].c_str(),position[i]);
    }
    printf("%s: %f ",signs[3].c_str(), 1.0);
    for (int i = 0; i < 3; i++) {
        printf("%s: %f ",signs[3 + i].c_str(),velocity[i]);

    }
}

