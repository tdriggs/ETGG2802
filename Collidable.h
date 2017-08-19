#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <vector>
#include "Mesh.h"
#include "AABB.h"
#include "math3d.h"

using namespace std;

class Mesh;

class Collidable {
public:

	vector<AABB*> boundingBoxes;
	vec3 position;
	vec3 boundingBoxColor;

	Collidable(vec3 position);

	void setSimpleBoundingBox(Mesh* mesh, float scale, vec3 euclidianRotations);
	void setBorderBoundingBoxes(int width, int height, int depth);
	bool detectCollision(Collidable* other);
	void toggleSolid();
	bool checkX(AABB * box, AABB * otherBox, vec3 otherPosition);
	bool checkY(AABB * box, AABB * otherBox, vec3 otherPosition);
	bool checkZ(AABB * box, AABB * otherBox, vec3 otherPosition);
	virtual void onCollision(Collidable * other) = 0;
	virtual void update(float elapsed) = 0;
};

#endif
