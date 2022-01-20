#ifndef RENDERING_H
#define RENDERING_H

#include "renderTexture.hpp"
#include "light.hpp"
#include "object.hpp"

extern RenderTexture* rt_DepthNormals;
extern RenderTexture* rt_PositionNormalsAlbedo;

class Rendering {
    public:
    static void init();
    static void beginLightmaps();
    static void renderObjectToLightmap(Object* object, Light* light);
    static void endLightmaps();
    static void beginPositionNormalsAlbedo();
    static void renderObjectToPositionNormalsAlbedo(Object* object);
    static void beginLightSpheres();
    static void renderLightSphere(Light* light);
    static void showLightmap(Object* plane, Light* light);
    static void showPosition(Object* plane);
    static void showNormals(Object* plane);
    static void showFinal(Object* plane);
};

#endif
