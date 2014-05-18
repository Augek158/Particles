//
//  Shader.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-17.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Shader.h"

Shader::Shader(std::string path, GLenum type){
    shaderID = ShaderUtils::createShaderFromFile(path.c_str(), type);
}

Shader::~Shader(){
    glDeleteShader(shaderID);
}

GLuint Shader::getShaderID(){
    return shaderID;
}