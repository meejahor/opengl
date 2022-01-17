#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

class RenderTexture {
    private:
    GLuint frameBuffer;
    GLuint depthBuffer;
    int width, height;
    GLuint textureSampler;
    void init();
    void addColorTexture(GLuint& textureID, GLint internalFormat, GLenum attachment = GL_COLOR_ATTACHMENT0);
    void addDepthTexture(GLuint& textureID);
    void addDepthBuffer();

    protected:
    void createColor();
    void createLightmap();
    void createDepthNormals();
    void createPositionNormalsAlbedo();

    public:
    GLuint position;     // TODO: this should be back in private
    GLuint normals;     // TODO: this should be back in private
    GLuint albedo;     // TODO: this should be back in private
    GLuint depth;     // TODO: this should be back in private
    static RenderTexture* createLightmap(int width, int height);
    static RenderTexture* createDepthNormals(int width, int height);
    static RenderTexture* createPositionNormalsAlbedo(int width, int height);
    void beginRenderingLightmap();
    void showTexture();
    void showDepthNormals();
    void beginDepthNormals();
    void showLightmap();
    void showPosition();
    void showNormals();
    void showAlbedo();
    void beginRenderingPositionNormalsAlbedo();
    RenderTexture(int _width, int _height);
};

#endif
