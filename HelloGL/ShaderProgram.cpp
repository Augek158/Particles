//
//  ShaderProgram.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-17.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(){
    programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram(){
    glDeleteShader(programID);
}

void ShaderProgram::attachShader(Shader* shader){
    glAttachShader(programID, shader->getShaderID());
}

void ShaderProgram::bindFragDataLocation(GLint colorAttachment, std::string name){
    glBindFragDataLocation(programID, colorAttachment, name.c_str());
}

void ShaderProgram::link(){
    
    glLinkProgram(programID);
    
    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if(linkStatus != GL_TRUE){
        std::cout << "Program link failed!" << std::endl;
        GLint infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete[] infoLog;
    }
}

void ShaderProgram::use(){
    glUseProgram(programID);
}

GLint ShaderProgram::getAttribLoc(std::string name){
    return glGetAttribLocation(programID, name.c_str());
}
GLint ShaderProgram::getUniformLoc(std::string name){
    return glGetUniformLocation(programID, name.c_str());
}