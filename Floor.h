#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Program.h"
#include "Room.h"
#include "Boss.h"

using namespace std;

class Room;
class Teleporter;
class Enemy;
class Boss;

class Floor {
public:

	int width, height;
	vector<Room*> rooms;
	Boss* boss;
	Room* pBossRoom;
	Room* pActive;

	Floor(int numberRooms, int minWidth, int maxWidth, int minHeight, int maxHeight);

	void draw(Program* pProgram);
	void update(float elapsed);
	vec3 getSpawnPoint();
	bool isBossDead();
	vector<Character*> getActiveEnemies();
	vector<Teleporter*> getActiveTeleporters();
	vec3 getActiveLightPos();

private:

	void generateRooms(int numberRooms);
	Room * getGoodRoom(string roomName);
	void generateConnections();
	vec3 getTeleporterPosition(Room * room);
	Room * getTeleporterDestination(Room * room);
};

#endif
