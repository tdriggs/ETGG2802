#ifndef AABBMESH_H
#define AABBMESH_H

#include "glfuncs.h"
#include "Program.h"
#include "Mesh.h"
#include "Texture.h"
#include "AABB.h"

class AABB;

class AABBMesh : public Mesh {
public:

	AABBMesh(AABB* box, Texture* tex);
};

#endif
