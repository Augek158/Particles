//
//  ParticleContainer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-19.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Container.h"
#include <IL/il.h>

/*
 Default constructor
 */
Container::Container(){

    offset = 0;
    
}

void Container::populate(){
    for(int i = 0; i < MAX_SIZE; i++){
        container[i] = *new Particle();
    }
}

Container::~Container(){
    
}


/*
 This function generates a subbuffer with the positions and velocities
 of new particles. The subbuffer can then be used to populate a GL_ARRAY_BUFFER.
*/
GLfloat* Container::getNewParticleData(int particles){
    
    // Return nullptr if theres no room for more particles
    if(offset + particles > MAX_SIZE) return nullptr;
    
    GLfloat* subBuffer = new GLfloat[7 * particles];
    int index = 0;
    
    // Populating the subbuffer
    for(int i = offset; i < offset + particles; i++){
        Particle &p = container[i];
        for (int j = 0; j < 3; j++) {
            subBuffer[index + j] = p.getPosition()[j];
        }
        
        // set w-cordinate = 1.0
        subBuffer[index + 3] = 1.0;
        for(int j = 0; j < 3; j++){
            subBuffer[index + 4 + j] = p.getVelocity()[j];
        }
        index+=7;
    }
    
    // Update values so next call on this function is correct.
    addedParticles = particles;
    offset += particles;
    return subBuffer;
}

void Container::print(){
    for(int i = 0; i < offset; i++){
        container[i].print();
        printf("\n");
    }
}

double Container::getDelta(){
    return 1.0f / 60.0f;
}

int Container::getAddedParticles(){
    return addedParticles;
}

int Container::getNumberParticles(){
    return offset;
}


void Container::insertParticleAt(int index, Particle *p){

    container[index] = *p;

}

void Container::loadTextParticles(){
    
//    /* //Avkommentera om det inte funkar

   if(true){
    //Init texture
    ILboolean result = ilLoadImage( "introLD.png" ) ;


    if( result )
    {
        printf("Image loaded successfully\n");
    }
    else
    {
        printf("The image failed to load\n" ) ;
        
        ILenum err = ilGetError() ;
        printf( "Error: %d\n", err );
        printf( "String is %s\n", ilGetString( err ) );
    }
    
    int size = ilGetInteger( IL_IMAGE_SIZE_OF_DATA ) ;
    ILubyte * bytes = ilGetData() ;
    
    //Get Dimensions of Image
    ILuint imgWidth, imgHeight;
    imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
    imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);


    float x,y;
    float BoundingSize = 20.0f;
    
    float scale = BoundingSize/ imgWidth;
    
    int column=0,row=0, counter=0;
    

    for( int i = 0 ; i < size; i+=4 )
    {
        
        int r = bytes[i];
//        int g = bytes[i+1];
//        int b = bytes[i+2];
//        int a = bytes[i+3];
        
        //If pixel is NOT black place a particle.
        if(r != 0){
            //Scale and uniform XY
            x = scale * (column - ((float)imgWidth / 2.0));
            y = scale * (row - ((float)imgHeight / 2.0));
            
            //Update container with a particle.
            container[counter] = *new Particle(glm::vec3(x, y, 0.0f));
            
            counter++;

        }
    
        //New row compensation
        if(column == imgWidth-1){
        
            row++;
            column=-1;
        }
        //New column
        column++;
    
    } //for

    }
    
    //Här också
//    */
}

void Container::loadObjectFile(){
    
    FILE * file = fopen("teapot.obj", "r");
    if( file == NULL ){
        printf("Could not open .obj file!\n");
        
    }
    int counter=0;
    while( 1 ){
 
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
            
        
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            float scale = 4.0;

           
            container[counter] = *new Particle(scale*vertex);
             counter++;

        }
        



    }
    printf("%i", counter);
   // offset += counter;
}
