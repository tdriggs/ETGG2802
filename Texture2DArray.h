#ifndef TEXTURE2DARRAY_H
#define TEXTURE2DARRAY_H

#include "ppng.h"
#include "util.h"
#include "Texture.h"

class Texture2DArray : public Texture {
 
public:

    int w,h;
    int numslices;

protected:

	Texture2DArray();

};

#endif
