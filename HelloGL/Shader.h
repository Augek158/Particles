//
//  Shader.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-17.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__Shader__
#define __HelloGL__Shader__

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include "ShaderUtils.h"

class Shader{
private:
    GLuint shaderID;
public:
    GLuint getShaderID();
    Shader(std::string path, GLenum type);
    virtual ~Shader();
    
};

#endif /* defined(__HelloGL__Shader__) */
