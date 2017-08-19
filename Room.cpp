#include "Room.h"

Room::Room(string name, int centerX, int centerY, int minWidth, int maxWidth, int minHeight, int maxHeight) : Collidable(vec3(centerX, 0, centerY))
{
	this->name = name;
	this->width = ((rand() % (maxWidth - minWidth) + minWidth) / 2) * 2;
	if (this->width % 2 != 0)
		this->width++;
	this->height = ((rand() % (maxHeight - minHeight) + minHeight) / 2) * 2;
	if (this->height % 2 != 0)
		this->height++;
	this->pMesh = new PolyMesh(width, 3, height);
	this->setBorderBoundingBoxes(width, 3, height);
	this->spawnX = ((rand() % (this->width - 2)) - (this->width / 2)) / 2;
	this->spawnY = ((rand() % (this->height - 2)) - (this->height / 2)) / 2;
	this->lights = vector<vec3>(5);
	this->lightDirections = vector<vec3>(5);
	this->lightUps = vector<vec3>(5);

	float lightHeight = 2.5;
	lights[0] = vec3(this->position.x, this->position.y + lightHeight, this->position.z);
	lightDirections[0] = lights[0] + vec3(0, -1, 0);
	lightUps[0] =  vec3(0, 0, 1);
	lights[1] = vec3(this->position.x, this->position.y + lightHeight, this->position.z);
	lightDirections[1] = lights[1] + vec3(0, 0, 1);
	lightUps[1] = vec3(0, 1, 0);
	lights[2] = vec3(this->position.x, this->position.y + lightHeight, this->position.z);
	lightDirections[2] = lights[2] + vec3(0, 0, -1);
	lightUps[2] = vec3(0, 1, 0);
	lights[3] = vec3(this->position.x, this->position.y + lightHeight, this->position.z);
	lightDirections[3] = lights[3] + vec3(1, 0, 0);
	lightUps[3] = vec3(0, 1, 0);
	lights[4] = vec3(this->position.x, this->position.y + lightHeight, this->position.z);
	lightDirections[4] = lights[4] + vec3(-1, 0, 0);
	lightUps[4] = vec3(0, 1, 0);
}

void Room::initEnemies()
{
	int numEnemies = (int)(rand() % 5);
	for (int i = 0; i < numEnemies; i++) {
		this->enemies.push_back(new Enemy(this->position + vec3(((rand() % (this->width - 2)) - (this->width / 2)) / 2, 0, ((rand() % (this->height - 2)) - (this->height / 2)) / 2)));
	}
}

void Room::onCollision(Collidable* other) { }

void Room::setTeleporter(Teleporter* newTeleporter)
{
	this->teleporters.push_back(newTeleporter);
}

bool Room::hasTeleporterPosition(vec3 position)
{
	bool result = false;

	for (Teleporter* teleporter : this->teleporters)
		if (teleporter->position == position)
			result = true;

	return result;
}

bool Room::hasTeleporter(Room* destination)
{
	bool result = false;

	for (Teleporter* teleporter : this->teleporters)
		if (teleporter->pDestination == destination)
			result = true;

	return result;
}

void Room::draw(Program* pProgram) 
{
	pProgram->setUniform("worldMatrix", translation(this->position));
	this->pMesh->draw(pProgram);

	//for (AABB* box : this->boundingBoxes)
		//box->draw(pProgram, this->position);

	if (this->enemies.size() == 0)
	{
		for (Teleporter* teleporter : this->teleporters)
			teleporter->draw(pProgram);
	}

	for (Character* enemy : enemies)
		enemy->draw(pProgram);

}

void Room::blurDraw(Program * pProgram)
{
	pProgram->use();
	pProgram->setUniform("worldMatrix", translation(this->position));
	this->pMesh->draw(pProgram);
}

void Room::update(float elapsed)
{
	for (int i = 0; i<this->enemies.size(); i+=1) 
	{
		this->enemies[i]->update(elapsed);
		if (this->enemies[i]->isDead)
		{
			this->enemies.erase(this->enemies.begin()+i);
		}
	}

	for (Teleporter* teleporter : this->teleporters)
		teleporter->update(elapsed);
}

vec3 Room::getSpawnPoint()
{
	return this->position + vec3(this->spawnX, 0, this->spawnY);
}

vector<Character*> Room::getEnemies()
{
	return this->enemies;
}

vector<Teleporter*> Room::getTeleporters()
{
	return this->teleporters;
}
