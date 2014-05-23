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

    position = glm::vec3(-1.0 + 2 * (double)rand()/RAND_MAX,
                          -1.0 + 2 * (double)rand()/RAND_MAX,
                         0.0);//+ ((double) 8 * rand() / (RAND_MAX)));
    velocity = glm::vec3(0.0f, -1.0f, 0.0f);


    float speed = -2 + 4* ((double) rand() / (RAND_MAX));
//    velocity = glm::vec3( speed, speed, 0);

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

    
    if(position.y < BoundingSouth){
  
        glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 newvelocity = -2.0f * (velocity * normal) * normal + velocity;
        
        velocity = (COR * newvelocity);
        position.y = BoundingSouth;
        
    }
    
    if(position.y > BoundingNorth){
  
        glm::vec3 normal = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 newvelocity = -2.0f * (velocity * normal) * normal + velocity;
        
        velocity = (COR * newvelocity);
        position.y = BoundingNorth;
    }
    
    if(position.x < BoundingWest){
        glm::vec3 normal = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 newvelocity = -2.0f * (velocity * normal) * normal + velocity;
        
        velocity = (COR * newvelocity);
        position.x = BoundingWest;
    }
    
    if(position.x > BoundingEast){
        glm::vec3 normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        glm::vec3 newvelocity = -2.0f * (velocity * normal) * normal + velocity;
        
        velocity = (COR * newvelocity);
        position.x = BoundingEast;
    }
    
    if(position.z < BoundingFarthest){
        glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 newvelocity = -2.0f * (velocity * normal) * normal + velocity;
        
        velocity = (COR * newvelocity);
        position.z = BoundingFarthest;
    }
    
    if(position.z > BoundingNearest){
        glm::vec3 normal = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 newvelocity = -2.0f * (velocity * normal) * normal + velocity;
        
        velocity = (COR * newvelocity);
        position.z = BoundingNearest;
    }
    
}

float Particle::calculateEnergy(){
    
    float v = sqrt( velocity.x * velocity.x + velocity.y * velocity.y );
    float kineticEnergy = mass * v * v * 0.5;
    float potentialEnergy = mass * Physics::gravity * sqrt((position.y - BoundingSouth) * (position.y - BoundingSouth) );

    return (kineticEnergy + potentialEnergy);
}

bool Particle::collision(){
    
    GLfloat a = velocity.y * velocity.y;
    GLfloat b = 2*velocity.y* (position.y - BoundingSouth);
    GLfloat c = (position.y - BoundingSouth) * (position.y - BoundingSouth);
    
    GLfloat distance = 0; //?


    GLfloat time = ( -b +- sqrt( b*b - 4*a*( c - distance) ) ) / (2 * a);

    return false;
}
