#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>

class RenderTexture {
    private:
    GLuint frameBuffer;
    GLuint depthBuffer;
    int width, height;
    GLuint textureSampler;
    void init(GLuint& textureID);
    void addColorTexture(GLuint textureID);
    void addDepthTexture(GLuint textureID);
    void addDepthBuffer();

    protected:
    void createColor();
    void createLightmap();
    void createDepthNormals();

    public:
    GLuint albedo;     // TODO: this should be back in private
    GLuint normals;     // TODO: this should be back in private
    GLuint depth;     // TODO: this should be back in private
    static RenderTexture* createLightmap(int width, int height);
    static RenderTexture* createDepthNormals(int width, int height);
    void beginLightmap();
    void showTexture();
    void showDepthNormals();
    void beginDepthNormals();
    void showLightmap();
    RenderTexture(int _width, int _height);
};

#endif
