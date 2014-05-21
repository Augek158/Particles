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

    weight = 1000.0f;
    gravity = -9.82 / 10;
    still =false;
    
    life = 0.0f;

    position = glm::vec3(-25.0f + ((double) 40 * rand() / (RAND_MAX)),
                          10.0f + ((double) 20 * rand() / (RAND_MAX)),
                         -35.0f + ((double) 8 * rand() / (RAND_MAX)));
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 Particle::getPosition(){
    return position;
}

void Particle::update(){
    
    life += getDelta();

    

    if(!still){
        velocity += glm::vec3(0.0f, 1.0f * gravity * getDelta() , 0.0f);
        checkBounds();
        position += velocity;
    }
}

float Particle::getLife(){
    return life;
}

double Particle::getDelta(){
    return 1.0f / 60.0f;
}

void Particle::checkBounds(){

    float minEnergyValue = 0.01;
    
    if(position.y < Physics::groundLevel){
        velocity *= -Physics::COR;
        position.y = Physics::groundLevel;
    }
    if(calculateEnergy() <  minEnergyValue){
        still = true;
    }
    
}

float Particle::calculateEnergy(){
    glm::vec3 energy = glm::vec3();

    
    float absY = sqrt((position.y - Physics::groundLevel) * (position.y - Physics::groundLevel) );
    
    energy.y = absY + velocity.y * velocity.y;
    
    return energy.y;
}
