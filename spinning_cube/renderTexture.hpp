#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>

class RenderTexture {
    private:
    GLuint frameBuffer;
    GLuint renderBuffer;
    GLuint depthBuffer;
    // GLenum drawBuffers[1];
    int width, height;
    GLuint textureSampler;

    protected:
    void createColor();
    void createDepth();

    public:
    GLuint texture;     // TODO: this should be back in private
    static RenderTexture* createColorTexture(int _width, int _height);
    static RenderTexture* createDepthTexture(int _width, int _height);
    void activateAsLightmap();
    void useAsTexture();
};

#endif
