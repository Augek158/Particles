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

    position = glm::vec3(-1.0 + 2 * (double)rand()/RAND_MAX,
                          0.0,
                         0.0);//+ ((double) 8 * rand() / (RAND_MAX)));
    velocity = glm::vec3(0.0f, -1.0f, 0.0f);
}

glm::vec3 Particle::getPosition(){
    return position;
}

glm::vec3 Particle::getVelocity(){
    return velocity;
}

void Particle::update(){
    
    life += getDelta();

    float minEnergyValue = 0.1;

    if(calculateEnergy() > minEnergyValue){
        velocity += glm::vec3(0.0f, 1.0f * gravity * getDelta() , 0.0f);
        checkBounds();
        position += velocity;
    }else{
        velocity = glm::vec3(0.0, 0.0, 0.0);
    }
}

float Particle::getLife(){
    return life;
}

double Particle::getDelta(){
    return 1.0f / 60.0f;
}

void Particle::checkBounds(){
    
    if(position.y < Physics::groundLevel){
        velocity *= -Physics::COR;
        position.y = Physics::groundLevel;
    }
    
}

float Particle::calculateEnergy(){
    glm::vec3 energy = glm::vec3();

    
    float absY = sqrt((position.y - Physics::groundLevel) * (position.y - Physics::groundLevel) );
    
    energy.y = absY + velocity.y * velocity.y;
    
    return energy.y;
}

bool Particle::collision(){
    
    GLfloat a = velocity.y * velocity.y;
    GLfloat b = 2*velocity.y* (position.y - Physics::groundLevel);
    GLfloat c = (position.y - Physics::groundLevel) * (position.y - Physics::groundLevel);
    
    GLfloat distance = 0; //?


    GLfloat time = ( -b +- sqrt( b*b - 4*a*( c - distance) ) ) / (2 * a);

    return false;
}
