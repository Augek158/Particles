//
//  ShaderUtils.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-04.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__ShaderUtils__
#define __HelloGL__ShaderUtils__

#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

class ShaderUtils{
public:
    static GLuint createShaderFromFile(const GLchar* path, GLenum shaderType);
};

#endif /* defined(__HelloGL__ShaderUtils__) */
