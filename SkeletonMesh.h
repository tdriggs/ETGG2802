#ifndef SKELETONMESH_H
#define SKELETONMESH_H

#include "Mesh.h"

class SkeletonMesh : public Mesh {

public:

	string filename;

	Texture* boneparents = 0;
	Texture* boneheads = 0;
	Texture* bonequats = 0;
	int numframes;
	int numbones;
	float frame;

	SkeletonMesh(string filename);

	void draw(Program * prog);

};

#endif
