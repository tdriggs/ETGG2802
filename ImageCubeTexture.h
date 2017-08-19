#ifndef IMAGECUBETEXTURE_H
#define IMAGECUBETEXTURE_H

#include "ppng.h"
#include "util.h"
#include "CubeTexture.h"

class ImageCubeTexture : public CubeTexture {

public:
    
	ImageCubeTexture(const vector<string>& filenames);
};

#endif
