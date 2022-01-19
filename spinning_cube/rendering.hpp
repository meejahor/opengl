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
    static void beginPositionsNormalAlbedo();
    static void renderObjectToPositionsNormalAlbedo(Object* object);
};

#endif
