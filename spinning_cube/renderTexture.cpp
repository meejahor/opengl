#include <iostream>

#include "renderTexture.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// RenderTexture::RenderTexture(int _width, int _height) {
//     width = _width;
//     height = _height;

//     glGenFramebuffers(1, &frameBuffer);
//     glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//     glGenRenderbuffers(1, &depthBuffer);
//     glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
//     glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

//     glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
//     glDrawBuffers(1, drawBuffers);

//     if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//         throw std::exception();
//     }
// }

void RenderTexture::createColor() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    int nrChannels;

    unsigned char *data = stbi_load("image.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);

    // float pixels[] = {
    //     1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
    //     1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f
    // };
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	// glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
    // glDrawBuffer(GL_FRONT);

    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::exception();
    }
}

void RenderTexture::createDepth() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    // float pixels[] = {
    //     1.0f, 0.0f,
    //     0.0f, 1.0f
    // };
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 2, 2, 0, GL_DEPTH_COMPONENT, GL_FLOAT, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::exception();
    }
}

// https://stackoverflow.com/questions/22419682/glsl-sampler2dshadow-and-shadow2d-clarification
// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDepthRange.xhtml

RenderTexture* RenderTexture::createColorTexture(int _width, int _height) {
    std::cout << "creating rt" << std::endl;
    
    RenderTexture* rt = new RenderTexture();
    rt->width = _width;
    rt->height = _height;

    try {
        rt->createColor();
    } catch (...) {
        throw;
    }

    return rt;
}

RenderTexture* RenderTexture::createDepthTexture(int _width, int _height) {
    std::cout << "creating rt depth" << std::endl;
    
    RenderTexture* rt = new RenderTexture();
    rt->width = _width;
    rt->height = _height;

    try {
        rt->createDepth();
    } catch (...) {
        throw;
    }

    return rt;
}

void RenderTexture::activateAsLightmap() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    // glClearDepth(0.2);
    // glEnable(GL_SCISSOR_TEST);
    // glScissor(width/4, height/4, width/4, height/4);
    // glClear(GL_DEPTH_BUFFER_BIT);
    // glDisable(GL_SCISSOR_TEST);
    // glDepthMask(true);

    // glEnable(GL_SCISSOR_TEST);
    // glScissor(100, 100, 50, 50);
    // glClearColor(1, 0, 0, 1);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glDisable(GL_SCISSOR_TEST);
}

void RenderTexture::useAsTexture() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    // glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    // glViewport(0, 0, width, height);
}
