#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>

#include <string>

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
    void addImage(GLuint& textureID, std::string filename, GLenum attachment = GL_COLOR_ATTACHMENT0);
    void loadImage_Albedo(std::string filename);
    void loadImage_Cookie(std::string filename);

    protected:
    void createLightmap();
    void createPositionNormalsAlbedo();

    public:
    GLuint position;
    GLuint normals;
    GLuint albedo;
    GLuint lighting;
    GLuint depth;
    GLuint cookie;
    RenderTexture();
    RenderTexture(int _width, int _height);
    static RenderTexture* createLightmap(int width, int height);
    static RenderTexture* createPositionNormalsAlbedo(int width, int height);
    void beginRenderingLightmap();
    void showTexture();
    void showLightmap();
    void showPosition();
    void showNormals();
    void showAlbedo();
    void showFinal();
    void beginRenderingPositionNormalsAlbedo();
    void beginRenderingLighting();
    void useAlbedo();
    void showCookie();
    static RenderTexture* loadAlbedo(std::string filename);
    static RenderTexture* loadCookie(std::string filename);
    static void setDefaultDrawBuffersAndTexture();
};

#endif
