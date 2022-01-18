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
    void addImage(GLuint& textureID, std::string filename, GLenum attachment = GL_COLOR_ATTACHMENT0);
    void loadImage_Albedo(std::string filename);

    protected:
    void createColor();
    void createLightmap();
    void createDepthNormals();
    void createPositionNormalsAlbedo();

    public:
    GLuint position;     // TODO: this should be back in private
    GLuint normals;     // TODO: this should be back in private
    GLuint albedo;     // TODO: this should be back in private
    GLuint lighting;
    GLuint depth;     // TODO: this should be back in private
    RenderTexture();
    RenderTexture(int _width, int _height);
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
    void showFinal();
    void beginRenderingPositionNormalsAlbedo();
    void beginRenderingLighting();
    void useAlbedo();
    static void resetDrawBuffer();
    static RenderTexture* loadAlbedo(std::string filename);
};

#endif
