#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "ppng.h"
#include "util.h"
#include "Texture2D.h"

class ImageTexture: public Texture2D {

public:

    string filename;
    int depth;
    int planes;
    
	ImageTexture(string filename);
    
};

#endif
