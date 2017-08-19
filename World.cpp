#include "World.h"

World* World::world = NULL;

World::World() {
	this->floor = new Floor(5, 0, 10000, 0, 10000);
}

World * World::getInstance()
{
	if (World::world == NULL) {
		World::world = new World();
	}
	return World::world;
}

void World::draw(Program* pProgram) {
	this->floor->draw(pProgram);
}

void World::update(float elapsed)
{
	this->floor->update(elapsed);
}

vec3 World::getSpawnPoint() {
	return this->floor->getSpawnPoint();
}

Room* World::getCurrentRoom() {
	return this->floor->pActive;
}

void World::setCurrentRoom(Room* newCurrentRoom)
{
	this->floor->pActive = newCurrentRoom;
}

bool World::isBossDead()
{
	return this->floor->isBossDead();
}

vector<Character*> World::getActiveEnemies()
{
	return this->floor->getActiveEnemies();
}

vector<Teleporter*> World::getActiveTeleporters()
{
	return this->floor->getActiveTeleporters();
}

vec3 World::getActiveLightPos()
{
	return this->floor->getActiveLightPos();
}