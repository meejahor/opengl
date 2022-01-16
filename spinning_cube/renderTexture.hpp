#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/OpenGL.h>

class RenderTexture {
    private:
    GLuint frameBuffer;
    GLuint renderBuffer;
    GLuint depthBuffer;
    int width, height;
    GLuint textureSampler;

    protected:
    void createColor();
    void createLightmap();
    void createDepthNormals();

    public:
    GLuint color;     // TODO: this should be back in private
    GLuint normals;     // TODO: this should be back in private
    GLuint depth;     // TODO: this should be back in private
    static RenderTexture* createLightmap(int _width, int _height);
    static RenderTexture* createDepthNormals(int _width, int _height);
    void beginLightmap();
    void showTexture();
    void showDepthNormals();
    void beginDepthNormals();
    void showLightmap();
};

#endif
