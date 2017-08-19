#include "Collidable.h"

Collidable::Collidable(vec3 position) { 
	this->position = position;
	this->boundingBoxColor = vec3(randrange(0, 1), randrange(0, 1), randrange(0, 1));
}

void Collidable::setSimpleBoundingBox(Mesh* mesh, float scale, vec3 euclidianRotations) {
	this->boundingBoxes.clear();
	vector<vec3> floatVec = vector<vec3>();
	floatVec.resize(mesh->numvertices);
	memcpy(&floatVec[0], &(mesh->vertexAttribs[0].data)[0], mesh->numvertices * 3 * 4);

	mat4 rotationMat = mat4::identity();

	for (int i = 0; i < floatVec.size(); ++i)
	{
		vec4 v = vec4(floatVec[i], 0);
		v = v * rotationMat;
		floatVec[i] = vec3(v.x, v.y, v.z);
	}

	double maxX = 0, maxY = 0, maxZ = 0, minX = 0, minY = 0, minZ = 0;

	for (int i = 0; i < floatVec.size(); i += 3) {
		if (floatVec[i].x > maxX)
			maxX = floatVec[i].x;
		else if (floatVec[i].x < minX)
			minX = floatVec[i].x;
		if (floatVec[i].y > maxY)
			maxY = floatVec[i].y;
		else if (floatVec[i].y < minY)
			minY = floatVec[i].y;
		if (floatVec[i].z > maxZ)
			maxZ = floatVec[i].z;
		else if (floatVec[i].z < minZ)
			minZ = floatVec[i].z;
	}

	AABB* box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), scale * minX, scale * minY, scale * minZ, scale * maxX, scale * maxY, scale * maxZ);
	this->boundingBoxes.push_back(box);
}

void Collidable::setBorderBoundingBoxes(int width, int height, int depth)
{
	float halfWidth = width / 2.0;
	float halfHeight = height / 2.0;
	float halfDepth = depth / 2.0;
	// Left Box
	AABB* box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), -1, -halfHeight, -halfDepth, 1, halfHeight, halfDepth, vec3(-halfWidth - 1, halfHeight, 0), true);
	this->boundingBoxes.push_back(box);
	// Top Box
	box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), -halfWidth, -halfHeight, -1, halfWidth, halfHeight, 1, vec3(0, halfHeight, halfDepth + 1), true);
	this->boundingBoxes.push_back(box);
	// Right Box
	box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), -1, -halfHeight, -halfDepth, 1, halfHeight, halfDepth, vec3(halfWidth + 1, halfHeight, 0), true);
	this->boundingBoxes.push_back(box);
	// Bottom Box
	box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), -halfWidth, -halfHeight, -1, halfWidth, halfHeight, 1, vec3(0, halfHeight, -halfDepth - 1), true);
	this->boundingBoxes.push_back(box);
	// Floor Box
	box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), -halfWidth, -1, -halfDepth, halfWidth, 1, halfDepth, vec3(0, -1, 0), true);
	this->boundingBoxes.push_back(box);
	// Ceiling Box
	box = new AABB(new SolidTexture(this->boundingBoxColor.x, this->boundingBoxColor.y, this->boundingBoxColor.z, 1), -halfWidth, halfHeight, -halfDepth, halfWidth, halfHeight + 2, halfDepth, vec3(0, halfHeight, 0), true);
	this->boundingBoxes.push_back(box);
}

bool Collidable::detectCollision(Collidable* other) {
	bool result = false;

	for (AABB* box : this->boundingBoxes) {
		for (AABB* otherBox : other->boundingBoxes) {
			if (checkX(box, otherBox, other->position) && checkY(box, otherBox, other->position) && checkZ(box, otherBox, other->position)) {
				result = true;

				this->onCollision(other);
				other->onCollision(this);

				if (box->isSolid && otherBox->isSolid) {
					vector<vec3> normals = { vec3(1, 0, 0), vec3(-1, 0, 0), vec3(0, 1, 0), vec3(0, -1, 0), vec3(0, 0, 1), vec3(0, 0, -1) };
					float distances[6] = { ((other->position.x + otherBox->targetingOffset.x + otherBox->maxs.x) - (this->position.x + box->targetingOffset.x + box->mins.x)),
										   ((this->position.x + box->targetingOffset.x + box->maxs.x) - (other->position.x + otherBox->targetingOffset.x + otherBox->mins.x)),
										   ((other->position.y + otherBox->targetingOffset.y + otherBox->maxs.y) - (this->position.y + box->targetingOffset.y + box->mins.y)),
										   ((this->position.y + box->targetingOffset.y + box->maxs.y) - (other->position.y + otherBox->targetingOffset.y + otherBox->mins.y)),
										   ((other->position.z + otherBox->targetingOffset.z + otherBox->maxs.z) - (this->position.z + box->targetingOffset.z + box->mins.z)),
										   ((this->position.z + box->targetingOffset.z + box->maxs.z) - (other->position.z + otherBox->targetingOffset.z + otherBox->mins.z)) };

					int normalIndex = 0;
					for (int i = 1; i < 6; i++) {
						if (distances[i] >= 0) {
							if (distances[i] < distances[normalIndex]) {
								normalIndex = i;
							}
						}
					}

					this->position = this->position + (normals[normalIndex] * distances[normalIndex]) + (normals[normalIndex] * 0.001);
				}

			}
		}
	}

	return result;
}

void Collidable::toggleSolid()
{
	for (AABB* box : this->boundingBoxes)
		box->isSolid = !box->isSolid;
}

bool Collidable::checkX(AABB* box, AABB* otherBox, vec3 otherPosition)
{
	bool result = false;

	if (this->position.x + box->targetingOffset.x + box->mins.x <= otherPosition.x + otherBox->targetingOffset.x + otherBox->maxs.x &&
		this->position.x + box->targetingOffset.x + box->maxs.x >= otherPosition.x + otherBox->targetingOffset.x + otherBox->mins.x) {
		result = true;
	}

	return result;
}

bool Collidable::checkY(AABB* box, AABB* otherBox, vec3 otherPosition)
{
	bool result = false;

	if (this->position.y + box->targetingOffset.y + box->mins.y <= otherPosition.y + otherBox->targetingOffset.y + otherBox->maxs.y &&
		this->position.y + box->targetingOffset.y + box->maxs.y >= otherPosition.y + otherBox->targetingOffset.y + otherBox->mins.y) {
		result = true;
	}

	return result;
}

bool Collidable::checkZ(AABB* box, AABB* otherBox, vec3 otherPosition)
{
	bool result = false;

	if (this->position.z + box->targetingOffset.z + box->mins.z <= otherPosition.z + otherBox->targetingOffset.z + otherBox->maxs.z &&
		this->position.z + box->targetingOffset.z + box->maxs.z >= otherPosition.z + otherBox->targetingOffset.z + otherBox->mins.z) {
		result = true;
	}

	return result;
}
