#ifndef DATATEXTURE_H
#define DATATEXTURE_H

#include "ppng.h"
#include "util.h"
#include <vector>
#include "math3d.h"
#include "Texture2D.h"


class DataTexture : public Texture2D{

public:

    GLenum ifmt,fmt;
    int w,h;
    int numcomponents;

	DataTexture(const vector<vec4>& data, int width, int height);
	DataTexture(const vector<vec3>& data, int width, int height);
	DataTexture(const vector<vec2>& data, int width, int height);
	DataTexture(const vector<float>& data, int width, int height);

	void init(int w, int h, const float* p, int numcomponents, int numitems);
    
	void update(const vector<float>& f);
	void update(const vector<vec2>& f);
	void update(const vector<vec3>& f);
	void update(const vector<vec4>& f);
	void update(const float* p, int numfloats);
};

#endif
