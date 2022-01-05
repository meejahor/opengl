#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>

class RenderTexture {
    private:
    GLuint frameBuffer;
    GLuint texture;
    GLuint depthBuffer;
    GLenum drawBuffers[1];
    int width, height;

    protected:
    void createColor();
    void createDepth();

    public:
    static RenderTexture* createColorTexture(int _width, int _height);
    void activate();
};

#endif
