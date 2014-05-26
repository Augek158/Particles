//
//  Renderer.cpp
//  HelloGL
//
//  Created by August Nam-Ki Ek on 2014-05-23.
//  Copyright (c) 2014 August Nam-Ki Ek. All rights reserved.
//

#include "Renderer.h"

Renderer::Renderer(GLuint batchSize, GLuint interval):
    batchSize(batchSize), interval(interval){
        container = new Container();
}

void Renderer::initWindow(){
    window = new Window(640, 360, "Particles");
    window->makeContextCurrent();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
}
void Renderer::initShaderPrograms(){
    
    renderProgram = new ShaderProgram();

    // Initalize vertex and fragment shaders
    Shader* vertexShader = new Shader("MyVertexShader.vs", GL_VERTEX_SHADER);
    Shader* fragmentShader = new Shader("MyFragmentShader.fs",GL_FRAGMENT_SHADER);
    renderProgram->attachShader(vertexShader);
    renderProgram->attachShader(fragmentShader);
    
    renderProgram->bindFragDataLocation(0, "fragData");
    renderProgram->link();
    
    // Initalizing TransformShader
    Shader* transformShader = new Shader("MyTransformShader.vs", GL_VERTEX_SHADER);
    
    transformProgram = new ShaderProgram();
    transformProgram->attachShader(transformShader);
    
    // Initalizing the feedback variables
    const GLchar* feedbackVaryings[] = {"vPosition", "vVelocity"};
    glTransformFeedbackVaryings(transformProgram->getProgramID(), 2, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
    
    transformProgram->link();
    transformProgram->use();
    
    delete vertexShader;
    delete fragmentShader;
    delete transformShader;
}

void Renderer::initBuffers(){

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(3, vbo);
    
    // The prototype of all particles
    GLfloat prototypeData[] = {
        0.5, 0.5, -0.0
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[PROTO_VBO]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(prototypeData), prototypeData , GL_STATIC_DRAW);
    
    // Creating buffer large enough to store MAX_BUFFER_SIZE particles.
    glBindBuffer(GL_ARRAY_BUFFER, vbo[DATA_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 7 * MAX_BUFFER_SIZE * sizeof(GL_FLOAT), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    glBufferSubData(GL_ARRAY_BUFFER, 7 * sizeof(GL_FLOAT) * particles, sizeof(particleData), particleData);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[TRANSFORM_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 7 * MAX_BUFFER_SIZE * sizeof(GL_FLOAT), nullptr, GL_DYNAMIC_COPY);
    
    glPointSize(2.5f);

}

void Renderer::initCamera(){
    
    cam = Camera();
    cam.setPosition(glm::vec3(0.0,20.0, 40.0));
    cam.setRotation(glm::vec3(-40, 0, 0));
    
}

void Renderer::setUniforms(){
    
    float aspect = (float)window->getFrameBufferWidth()/window->getFrameBufferHeight();
    
    glm::mat4 projectionMat = glm::perspective(60.0f, aspect, 0.01f, 100.0f);
    glm::mat4 viewMat = cam.getMatrix();
    glm::mat4 modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f));
    
    glUniformMatrix4fv(PROJECTION_LOC, 1, GL_FALSE, glm::value_ptr(projectionMat));
    glUniformMatrix4fv(VIEW_LOC, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(MODEL_LOC, 1, GL_FALSE, glm::value_ptr(modelMat));
}

void Renderer::update(){
    frameCount++;
    
    // Start transform feedback
    transformProgram->use();

    glEnable(GL_RASTERIZER_DISCARD);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[DATA_VBO]);
    spawnParticles();

    glEnableVertexAttribArray(POSITION_LOC);
    glEnableVertexAttribArray(VELOCITY_LOC);
    
    glVertexAttribPointer(POSITION_LOC, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
    glVertexAttribPointer(VELOCITY_LOC, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)( 4 * sizeof(GL_FLOAT)));
    
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[TRANSFORM_VBO]);
    
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, particles);
    glEndTransformFeedback();
    
    // Swap the buffers
    std::swap(vbo[DATA_VBO],vbo[TRANSFORM_VBO]);

    
}

void Renderer::draw(){
    
    renderProgram->use();
    glDisable(GL_RASTERIZER_DISCARD);
    
    glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
    glClear(GL_COLOR_BUFFER_BIT);
    
    // TODO: Improve blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[PROTO_VBO]);
    glEnableVertexAttribArray(VERTEX_LOC);
    glVertexAttribPointer(VERTEX_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[DATA_VBO]);
    glEnableVertexAttribArray(POSITION_LOC);
    glVertexAttribPointer(POSITION_LOC, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), 0);
    glVertexAttribDivisor(POSITION_LOC, 1);
    
    // Draw all of the particles in a single call
    glDrawArraysInstanced(GL_POINTS, 0, 1,particles);
    
    glUniformMatrix4fv(VIEW_LOC, 1, GL_FALSE, glm::value_ptr(cam.getMatrix()));
    setUniforms();
    glVertexAttribDivisor(POSITION_LOC, 0);
}

bool Renderer::render(){
    
    while(!window->shouldClose()){
        cam.pollUserInput(window);
        window->setWindowFPS();
        update();
        draw();
        glfwPollEvents();
        window->swapBuffers();
    }
    return 0;
}

/*
 This function spawns particles when the current frame divided by 'interval'
 leaves no remainder. It will stop spawn if the count of particles in the system
 has reached the maximum capacity of the system.
 */
void Renderer::spawnParticles(){
    if(frameCount % interval == 0){
        frameCount = 0;
        GLfloat* particleData = container->getNewParticleData(batchSize);
        if(particleData != nullptr){
            glBufferSubData(GL_ARRAY_BUFFER, 7 * sizeof(GL_FLOAT) * particles, container->getAddedParticles() * 7 *sizeof(GL_FLOAT), particleData);
            particles = container->getNumberParticles();
//            printf("particels: %d\n",particles);
        }
    }
}

Renderer::~Renderer(){
    delete window;
    delete renderProgram;
    delete transformProgram;
    
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(3, vbo);
    glfwTerminate();
}
