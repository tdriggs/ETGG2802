#ifndef AABB_H
#define AABB_H

#include "math3d.h"
#include "Program.h"
#include "AABBMesh.h"

using namespace std;

class Mesh;
class AABBMesh;

class AABB {
public:

	vec3 mins;
	vec3 maxs;
	vec3 widths;
	vec3 targetingOffset;
	bool isSolid;
	AABBMesh* mesh;

	AABB(Texture* tex, double minX, double minY, double minZ, double maxX, double maxY, double maxZ);
	AABB(Texture* tex, double minX, double minY, double minZ, double maxX, double maxY, double maxZ, vec3 targetingOffset, bool isSolid);

	void draw(Program* pProgram, vec3 position);
};

#endif
