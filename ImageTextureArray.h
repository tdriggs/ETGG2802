#ifndef IMAGETEXTUREARRAY_H
#define IMAGETEXTUREARRAY_H

#include "ppng.h"
#include "util.h"
#include "Texture2DArray.h"
#include "ImageTexture.h"

class ImageTextureArray: public Texture2DArray {

public:

	ImageTextureArray(const vector<string>& filenames);

};

#endif
