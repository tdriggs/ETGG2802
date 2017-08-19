#ifndef TEXTURE_H
#define TEXTURE_H

#include "glfuncs.h"
#include "ppng.h"
#include "util.h"
#include <set>

using namespace std;

class Texture {

public:

    GLuint tex=0;
    GLenum type=0;
    set<int> on_units;
    bool part_of_active_fbo=false;
    static Texture* active_textures[128];   

	virtual ~Texture();
	static bool isPowerOf2(int x);
	void bind(int unit);
	void unbind(int unit);
	void unbind();
     
protected:

	Texture(GLenum ty);
};

#endif   
