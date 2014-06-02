#version 330 core

layout(location = 1) in vec4 aPosition;
layout(location = 2) in vec3 aVelocity;

out vec4 vPosition;
out vec3 vVelocity;

const float dt = 1.0/60.0;
const float gravity = -9.82/10;
const float gravityMagnitude = sqrt( gravity * gravity);
const float mass = 1.0;
const float COR = 0.7;


const float BoundingSouth = -20.0;
const float BoundingNorth = 20.0;
const float BoundingEast = 20.0;
const float BoundingWest = -20.0;
const float BoundingFarthest = -20.0;
const float BoundingNearest = 20.0;

//Random Generator
float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//Returns the potential energy and kinetic energy for the particle.
//Checks height relative to BoundingSouth.
float calculateEnergy(){
   
     //Kinetic energy.
    float v = sqrt( aVelocity.x * aVelocity.x + aVelocity.y * aVelocity.y );
    float kineticEnergy = mass * v * v * 0.5;
    
    //Potential energy.
    float height = sqrt( (aPosition.y - BoundingSouth) * (aPosition.y - BoundingSouth) );
    float potentialEnergy = mass * gravityMagnitude * height;

    return (kineticEnergy + potentialEnergy) ;
}

//Checks collisions with boundings in XYZ. Calculate reflected velocity if collision happend.
//Returns true if collision happend, false otherwise.
bool collisionWithBounds(){
    vec3 tempVelocity = aVelocity + vec3(0.0f, 1.0f * gravity * dt , 0.0f);
    vec4 tempPosition = aPosition;
    vec3 newvelocity;
    vec3 normal;
    
    bool collision = false;

    
    if(tempPosition.y < BoundingSouth){
  
        normal= vec3(0.0f, 1.0f, 0.0f);
        tempPosition.y = BoundingSouth;
        collision = true;

    }
    if(tempPosition.y > BoundingNorth){
  
        normal = vec3(0.0f, -1.0f, 0.0f);
        tempPosition.y = BoundingNorth;
        collision = true;
    }
    if(tempPosition.x > BoundingEast){
  
        normal = vec3(-1.0f, 0.0f, 0.0f);
        tempPosition.x = BoundingEast;
        collision = true;
    }
    if(tempPosition.x < BoundingWest){
  
        normal = vec3(1.0f, 0.0f, 0.0f);
        tempPosition.x = BoundingWest;
        collision = true;
    }
    if(tempPosition.z > BoundingNearest){
  
        normal = vec3(0.0f, 0.0f, -1.0f);
        tempPosition.x = BoundingNearest;
        collision = true;
    }
    if(tempPosition.z < BoundingFarthest){
  
        normal = vec3(0.0f, 0.0f, 1.0f);
        tempPosition.x = BoundingFarthest;
        collision = true;
    }
    
    if(collision){
        newvelocity = ( -2.0f * dot(tempVelocity, normal) ) * normal + tempVelocity;
        vPosition = tempPosition + vec4(newvelocity, 0.0);
        vVelocity = COR * newvelocity;
    }
        
    return collision;

}

bool haveEnergy(){
    float minEnergyValue = 0.05;
//    return false;
    return (calculateEnergy() > minEnergyValue);

}

void main(){

    //If the particle have energy, check for collisions.
    if(haveEnergy()){
    
        //If no collision calculate particles new position and velocity.
        if(!collisionWithBounds()){
            vec3 tempVelocity = aVelocity + vec3(0.0f, 1.0f * gravity * dt , 0.0f);
            vPosition = aPosition + vec4(tempVelocity, 0.0);
            vVelocity = tempVelocity;
        }
    
    }else{ //Dead particle, assign velocity and position.
        vPosition = aPosition;
        vVelocity = vec3(0.0, 0.0, 0.0);
    }

    
}