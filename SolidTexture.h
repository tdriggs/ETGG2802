#ifndef SOLIDTEXTURE_H
#define SOLIDTEXTURE_H

#include "ppng.h"
#include "util.h"
#include "Texture2D.h"

class SolidTexture: public Texture2D {

public:

    int fmt;
    
	SolidTexture(float r, float g, float b, float a);
	SolidTexture(int fmt, float r, float g, float b, float a);
};

#endif
