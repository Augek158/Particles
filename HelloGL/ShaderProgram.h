//
//  ShaderProgram.h
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-17.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#ifndef __HelloGL__ShaderProgram__
#define __HelloGL__ShaderProgram__

#define GLFW_INCLUDE_GLCOREARB
#include <iostream>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ShaderUtils.h"

class Shader;


class ShaderProgram {
private:
    GLuint programID;
    
public:
    ShaderProgram();
    virtual ~ShaderProgram();
    
    void attachShader(Shader* shader);
    void link();
    void bindFragDataLocation(GLint colorAttachment, std::string name);
    void use();
    GLint getAttribLoc(std::string name);
    GLint getUniformLoc(std::string name);
    
};

#endif /* defined(__HelloGL__ShaderProgram__) */
