#ifndef FRAMEBUFFEROBJECT_H
#define FRAMEBUFFEROBJECT_H

#include "glfuncs.h"
#include "Texture2D.h"
#include <vector>
#include <cassert>
#include "CubeTexture.h"

using namespace std;

class RenderTarget {
public:

	RenderTarget(const RenderTarget&) = delete;
	static RenderTarget* active_target;

	template<typename T>
	string str(const T& v);

	static int saved_viewport[4];
	vector<Texture*> textures;
	Texture* texture;

protected:

	RenderTarget();

public:

	void checkOkToBind();
	void unbind();
};



class Framebuffer2D : public RenderTarget {
public:

	int width, height;
	int fbo;
	Texture2D* depthtexture;
	vector<GLuint> drawbuffers;

	Framebuffer2D(int width, int height);
	Framebuffer2D(int width, int height, int count);
	Framebuffer2D(int width, int height, int count, int format, int type);

	void init(int width, int height, int format, int type, int count);
	void bind();
};

class FramebufferCube : public RenderTarget {
public:

	int size;
	int fbos[6];
	Texture2D* depthtextures[6];

	FramebufferCube(int size);

	FramebufferCube(int width, int height, int format, int type);

	void init(int size, int format, int type);
	void bind(int face);
};

#endif

template<typename T>
string RenderTarget::str(const T& v) {
	std::ostringstream iss;
	iss << v;
	return iss.str();
}
