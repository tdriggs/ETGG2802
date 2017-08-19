#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "TeleporterMesh.h"
#include "Collidable.h"
#include "World.h"
#include "Player.h"
#include "Room.h"
#include "FrameBufferObject.h"
#include "SquareMesh.h"

class Room;

class Teleporter : public Collidable {
public:

	TeleporterMesh* pMesh;
	Framebuffer2D* fbo;
	Room* pDestination;
	vec4 border;
	float pulseSpeed;

	Teleporter(vec3 position, Room* pDestination);

	void draw(Program* pProgram);
	void update(float elapsed);
	void initializeMesh();
	void onCollision(Collidable* other);
};

#endif
