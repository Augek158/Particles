
//  main.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-04.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Renderer.h"
#include "Container.h"

int main(int argc, const char *argv[]){
    
    Renderer renderer(70,3);
    renderer.initWindow();
    renderer.initShaderPrograms();
    renderer.initBuffers();
    renderer.initCamera();
    renderer.render();
    
    return 0;
}