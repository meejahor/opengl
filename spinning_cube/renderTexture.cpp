#include <iostream>

#include "renderTexture.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int drawBuffersDefault[1] = {
    GL_COLOR_ATTACHMENT0
    };

unsigned int drawBuffersPositionNormalsAlbedo[3] = {
    GL_COLOR_ATTACHMENT0,
    GL_COLOR_ATTACHMENT1,
    GL_COLOR_ATTACHMENT2
    };

unsigned int drawBuffersLighting[1] = {
    GL_COLOR_ATTACHMENT3
    };

RenderTexture::RenderTexture() {
}

RenderTexture::RenderTexture(int _width, int _height) {
    width = _width;
    height = _height;
}

void RenderTexture::init() {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void RenderTexture::addColorTexture(GLuint& textureID, GLint internalFormat, GLenum attachment) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureID, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void RenderTexture::addDepthTexture(GLuint& textureID) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
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

void RenderTexture::addImage(GLuint& textureID, std::string filename, GLenum attachment) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int nrChannels;

    unsigned char *data = stbi_load(const_cast<char*>(filename.c_str()), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureID, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void checkValid() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::exception();
    }
}

void RenderTexture::createLightmap() {
    init();
    addDepthTexture(depth);
}

void RenderTexture::loadImage_Albedo(std::string filename) {
    init();
    addImage(albedo, filename);
}

void RenderTexture::loadImage_Cookie(std::string filename) {
    init();
    addImage(cookie, filename);
}

void RenderTexture::createPositionNormalsAlbedo() {
    init();
    addColorTexture(position, GL_RGBA16F);
    addColorTexture(normals, GL_RGBA16F, GL_COLOR_ATTACHMENT1);
    addColorTexture(albedo, GL_RGBA, GL_COLOR_ATTACHMENT2);
    addColorTexture(lighting, GL_RGBA, GL_COLOR_ATTACHMENT3);
    addDepthBuffer();
}

RenderTexture* RenderTexture::createLightmap(int width, int height) {
    RenderTexture* rt = new RenderTexture(width, height);
    rt->createLightmap();
    checkValid();
    return rt;
}

RenderTexture* RenderTexture::createPositionNormalsAlbedo(int width, int height) {
    RenderTexture* rt = new RenderTexture(width, height);
    rt->createPositionNormalsAlbedo();
    checkValid();
    return rt;
}

RenderTexture* RenderTexture::loadAlbedo(std::string filename) {
    RenderTexture* rt = new RenderTexture();
    rt->loadImage_Albedo(filename);
    return rt;
}

RenderTexture* RenderTexture::loadCookie(std::string filename) {
    RenderTexture* rt = new RenderTexture();
    rt->loadImage_Cookie(filename);
    return rt;
}

void RenderTexture::beginRenderingLightmap() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glDrawBuffers(1, drawBuffersDefault);
    glViewport(0, 0, width, height);
    glClearDepth(1);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::showTexture() {
    glBindTexture(GL_TEXTURE_2D, albedo);
}

void RenderTexture::useAlbedo() {
    glBindTexture(GL_TEXTURE_2D, albedo);
}

void RenderTexture::showLightmap() {
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, depth);
}

void RenderTexture::showCookie() {
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, cookie);
}

void RenderTexture::showPosition() {
    glBindTexture(GL_TEXTURE_2D, position);
}

void RenderTexture::showNormals() {
    glBindTexture(GL_TEXTURE_2D, normals);
}

void RenderTexture::showAlbedo() {
    glBindTexture(GL_TEXTURE_2D, albedo);
}

void RenderTexture::showFinal() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, lighting);
    glActiveTexture(GL_TEXTURE0);
}

void RenderTexture::beginRenderingPositionNormalsAlbedo() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glDrawBuffers(3, drawBuffersPositionNormalsAlbedo);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::beginRenderingLighting() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, position);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normals);
    // glActiveTexture(GL_TEXTURE2);
    // we set this to GL_TEXTURE2 because we'll call showLightmap for each light

    glDrawBuffers(1, drawBuffersLighting);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTexture::setDefaultDrawBuffersAndTexture() {
    glDrawBuffers(1, drawBuffersDefault);
    glActiveTexture(GL_TEXTURE0);
}
