#ifndef ROOM_H
#define ROOM_H

#include "PolyMesh.h"
#include "Collidable.h"
#include "Enemy.h"
#include "Player.h"
#include "World.h"
#include "Teleporter.h"

using namespace std;

class Teleporter;
class Enemy;

class Room : public Collidable {
public:

	string name;
	vector<Character*> enemies;
	PolyMesh* pMesh;
	int width, height;
	int spawnX, spawnY;
	vector<Teleporter*> teleporters;
	vector<vec3> lights;
	vector<vec3> lightDirections;
	vector<vec3> lightUps;

	Room(string name, int centerX, int centerY, int minWidth, int maxWidth, int minHeight, int maxHeight);

	void initEnemies();
	void onCollision(Collidable* other);
	void setTeleporter(Teleporter* newTeleporter);
	bool hasTeleporterPosition(vec3 position);
	bool hasTeleporter(Room* teleporter);
	void draw(Program* pProgram);
	void blurDraw(Program * pProgram);
	void update(float elapsed);
	vec3 getSpawnPoint();
	vector<Character*> getEnemies();
	vector<Teleporter*> getTeleporters();
};

#endif
