#include "AABB.h"

AABB::AABB(Texture* tex, double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
	this->mins = vec3(minX, minY, minZ);
	this->maxs = vec3(maxX, maxY, maxZ);
	this->widths = vec3(maxX - minX, maxY - minY, maxZ - minZ);
	this->targetingOffset = vec3(0, 0, 0);
	this->isSolid = true;
	this->mesh = new AABBMesh(this, tex);
}

AABB::AABB(Texture* tex, double minX, double minY, double minZ, double maxX, double maxY, double maxZ, vec3 targetingOffset, bool isSolid) {
	this->mins = vec3(minX, minY, minZ);
	this->maxs = vec3(maxX, maxY, maxZ);
	this->widths = vec3(maxX - minX, maxY - minY, maxZ - minZ);
	this->targetingOffset = targetingOffset;
	this->isSolid = isSolid;
	this->mesh = new AABBMesh(this, tex);
}

void AABB::draw(Program * pProgram, vec3 position)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	pProgram->setUniform("worldMatrix", translation(position + this->targetingOffset));
	this->mesh->draw(pProgram);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
