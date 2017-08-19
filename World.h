#ifndef WORLD_H
#define WORLD_H

#include "Program.h"
#include "Floor.h"

class Floor;
class Room;
class Teleporter;
class Enemy;

class World {
private:

	Floor* floor;
	static World* world;

	World();

public:

	static World* getInstance();
	void draw(Program* pProgram);
	void update(float elapsed);
	vec3 getSpawnPoint();
	Room* getCurrentRoom();
	void setCurrentRoom(Room* newCurrentRoom);
	bool isBossDead();
	vector<Character*> getActiveEnemies();
	vector<Teleporter*> getActiveTeleporters();
	vec3 getActiveLightPos();
};

#endif
