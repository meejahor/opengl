#include <iostream>

#include "renderTexture.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void RenderTexture::createDepth() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(1, &depth);
    glBindTexture(GL_TEXTURE_2D, depth);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::exception();
    }
}

void RenderTexture::createDepthNormals() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glGenTextures(1, &normals);
    glBindTexture(GL_TEXTURE_2D, normals);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, normals, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::exception();
    }
}

RenderTexture* RenderTexture::createDepth(int _width, int _height) {
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

RenderTexture* RenderTexture::createDepthNormals(int _width, int _height) {
    RenderTexture* rt = new RenderTexture();
    rt->width = _width;
    rt->height = _height;

    try {
        rt->createDepthNormals();
    } catch (...) {
        throw;
    }

    return rt;
}

void RenderTexture::renderLightmap() {
    // glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);

    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClear(GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_SCISSOR_TEST);
    // glClearDepth(0);
    // glScissor(width/4, height/4, width/4, height/4);
    // glClear(GL_DEPTH_BUFFER_BIT);
    // glDisable(GL_SCISSOR_TEST);
}

void RenderTexture::renderDepthNormals() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::showTexture() {
    glBindTexture(GL_TEXTURE_2D, color);

    // glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    // glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    // glViewport(0, 0, width, height);
}

void RenderTexture::showDepthNormals() {
    glBindTexture(GL_TEXTURE_2D, normals);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, depth);
    // glActiveTexture(GL_TEXTURE0+1);
    // glBindTexture(GL_TEXTURE_2D, normals);
    
    // glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    // glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);

    // glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    // glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    // glViewport(0, 0, width, height);
}
