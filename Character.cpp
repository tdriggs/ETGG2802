#include "Character.h"

Character::Character(vec3 pos, string meshName) : Collidable(pos) {

	this->init(meshName, 1, vec3(0, 0, 0), vec4(0, 0, 0, 0));
}

Character::Character(vec3 pos, string meshName, float scale, vec3 offset, vec4 axisRotation) : Collidable(pos)
{
	this->init(meshName, scale, offset, axisRotation);
}

void Character::init(string meshName, float scale, vec3 offset, vec4 rotation) {
	this->meshs = { new SkeletonMesh(meshName) };
	this->currentMesh = 0;
	this->scale = scale;
	this->setSimpleBoundingBox(this->meshs[this->currentMesh], this->scale, vec3(0, 0, 0));
	this->target = NULL;

	this->velocity = vec3(0, 0, 0);
	this->lookVector = vec3(0, 0, 1);
	this->euclidianRotations = vec3(0, 0, 0);
	this->health = 100;
	this->moveSpeed = 2;
	this->running = false;
	this->isDead = false;
	this->strength = 10;
	this->currentAnimation = -1;
	this->currentFrame = 0;
	this->animations = vector<Animation>();

	this->initialScaleAndRotationMat = axisRotation(vec3(rotation.x, rotation.y, rotation.z), radians(rotation.w)) * scaling(scale, scale, scale) * translation(offset);
}

void Character::rotate(double angle)
{
	this->euclidianRotations.x += angle;
	//this->setSimpleBoundingBox(this->mesh, this->scale, this->euclidianRotations);
}

void Character::animate()
{
	if (currentAnimation >= 0)
	{
		currentFrame += animations[currentAnimation].step;
		if (currentFrame >= animations[currentAnimation].end)
			currentFrame = animations[currentAnimation].start;

		this->meshs[this->currentMesh]->frame = currentFrame;
	}
}

void Character::setAnimation(string name)
{
	for (int i = 0; i < this->animations.size(); ++i)
	{
		if (animations[i].name == name)
		{
			this->currentAnimation = i;
			this->currentFrame = animations[i].start;
			break;
		}
	}
}

void Character::toggleRunning()
{
	this->running = !this->running;
}

void Character::draw(Program* prog) {
	prog->setUniform("hasSkeleton", 1);
	prog->setUniform("worldMatrix", this->initialScaleAndRotationMat * vectorToRotationMat(this->lookVector, vec3(0, 1, 0)) * translation(this->position));

	this->meshs[currentMesh]->draw(prog);

	//for (AABB* box : this->boundingBoxes)
	//	box->draw(prog, this->position);

	prog->setUniform("hasSkeleton", 0);
}

void Character::update(float elapsed) {
	this->velocity = normalize(this->velocity);
	this->position += this->velocity * (this->moveSpeed * elapsed * (running ? 2 : 1));
	this->velocity = vec3(0, 0, 0);
	this->animate();
}

void Character::onCollision(Collidable * other) { 
	if(this->boundingBoxes[0]->isSolid)
		this->velocity = vec3(0, 0, 0);
}
