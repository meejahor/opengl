#include <iostream>

#include "renderTexture.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RenderTexture::RenderTexture(int _width, int _height) {
    width = _width;
    height = _height;
}

void RenderTexture::init(GLuint& textureID) {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void RenderTexture::addColorTexture(GLuint textureID) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void RenderTexture::addDepthTexture(GLuint textureID) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureID, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
}

void RenderTexture::addDepthBuffer() {
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
}

void checkValid() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::exception();
    }
}

void RenderTexture::createLightmap() {
    init(depth);
    addDepthTexture(depth);
}

void RenderTexture::createDepthNormals() {
    init(normals);
    addColorTexture(normals);
    addDepthBuffer();
}

RenderTexture* RenderTexture::createLightmap(int width, int height) {
    RenderTexture* rt = new RenderTexture(width, height);
    rt->createLightmap();
    checkValid();
    return rt;
}

RenderTexture* RenderTexture::createDepthNormals(int width, int height) {
    RenderTexture* rt = new RenderTexture(width, height);
    rt->createDepthNormals();
    checkValid();
    return rt;
}

void RenderTexture::beginLightmap() {
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

void RenderTexture::beginDepthNormals() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::showTexture() {
    glBindTexture(GL_TEXTURE_2D, albedo);
}

void RenderTexture::showDepthNormals() {
    glBindTexture(GL_TEXTURE_2D, normals);
}

void RenderTexture::showLightmap() {
    glBindTexture(GL_TEXTURE_2D, depth);
}
