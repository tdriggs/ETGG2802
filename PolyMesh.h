#ifndef POLYMESH_H
#define POLYMESH_H

#include "glfuncs.h"
#include "Program.h"
#include "Mesh.h"
#include "ImageTexture.h"

class PolyMesh : public Mesh {
public:

	PolyMesh(int width, int height, int depth);
};

#endif
