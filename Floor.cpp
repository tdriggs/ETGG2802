#include "Floor.h"

Floor::Floor(int numberRooms, int minWidth, int maxWidth, int minHeight, int maxHeight) {
	this->width = (int)rand() % (maxWidth - minWidth) + minWidth;
	this->height = (int)rand() % (maxHeight - minHeight) + minHeight;
	this->generateRooms(numberRooms);
	this->generateConnections();

	this->boss = new Boss((pBossRoom->position + vec3(((rand() % (pBossRoom->width - 2)) - (pBossRoom->width / 2)) / 2, 0,
		((rand() % (pBossRoom->height - 2)) - (pBossRoom->height / 2)) / 2)));

	this->pBossRoom->enemies.push_back(this->boss);
}

void Floor::draw(Program* pProgram) {
	this->pActive->draw(pProgram);

	//for (Room* room : rooms)
		//room->draw(pProgram);

	//this->pBossRoom->draw(pProgram);
}

void Floor::update(float elapsed)
{
	this->pActive->update(elapsed);
}

vec3 Floor::getSpawnPoint()
{
	return this->pActive->getSpawnPoint();
}

bool Floor::isBossDead()
{
	return this->boss->isDead;
}

vector<Character*> Floor::getActiveEnemies()
{
	return this->pActive->getEnemies();
}

vector<Teleporter*> Floor::getActiveTeleporters()
{
	return this->pActive->getTeleporters();
}

vec3 Floor::getActiveLightPos()
{
	return this->pActive->position;
}

void Floor::generateRooms(int numberRooms) {
	for (int i = 0; i < numberRooms; ++i)
	{
		this->rooms.push_back(getGoodRoom(string(1, 65 + i)));
		this->rooms.at(i)->initEnemies();
	}

	this->pActive = this->rooms[0];
	this->pBossRoom = getGoodRoom("Boss Room");
}

Room * Floor::getGoodRoom(string roomName)
{
	bool isValidRoom = false;
	Room * result;
	while (!isValidRoom)
	{
		cout << "Room Generated!\n";
		isValidRoom = true;
		int centerX = (int)rand() % this->width;
		int centerY = (int)rand() % this->height;
		result = new Room(roomName, centerX, centerY, 15, 30, 15, 30);

		for (Room* room : this->rooms)
		{
			if (result->detectCollision(room))
			{
				isValidRoom = false;
				cout << "Room was bad...\n";
				break;
			}
		}
	}

	return result;
}

void Floor::generateConnections() {
	vector<set<Room*>> reach = {};
	for (int i = 0; i < this->rooms.size(); ++i) {
		set<Room*> ptrs = {};
		ptrs.insert(this->rooms.at(i));
		reach.push_back(ptrs);
	}
	
	bool validConn = false;
	int roomDex = 0;
	while (!validConn) {
		Room * tDes = this->getTeleporterDestination(this->rooms.at(roomDex));
		this->rooms.at(roomDex)->setTeleporter(new Teleporter(this->getTeleporterPosition(this->rooms.at(roomDex)), tDes));

		int desIndex = 0;
		for (int i = 0; i < this->rooms.size(); ++i) {
			if (this->rooms.at(i) == tDes) {
				desIndex = i;
			}
		}

		for (int k = 0; k < reach.size(); k++) {
		  if (reach.at(k).find(this->rooms.at(roomDex)) != reach.at(k).end()) {
				reach.at(k).insert(reach.at(desIndex).begin(), reach.at(desIndex).end());
			}
		}

		cout << "Teleporter from " << this->rooms.at(roomDex)->name << " to " << this->rooms.at(desIndex)->name << " created!\n";

		validConn = true;
		for (set<Room*> s : reach) {
		  if (s.size() != this->rooms.size()) {
				validConn = false;
			}
		}

		roomDex = (++roomDex) % this->rooms.size();
	}

	this->rooms.at(roomDex)->setTeleporter(new Teleporter(this->getTeleporterPosition(this->rooms.at(roomDex)), this->pBossRoom));
	cout << "Teleporter from " << this->rooms.at(roomDex)->name << " to " << this->pBossRoom->name << " created!\n";
}

vec3 Floor::getTeleporterPosition(Room* room) {
	bool validTele = false;
	vec3 checkPosition = vec3(0, 0, 0);
	while (!validTele) {
		validTele = true;
		int x = (rand() % room->width) - (room->width) / 2;
		int z = (rand() % room->height) - (room->height) / 2;
		checkPosition = vec3(x, 1, z);
		for (Teleporter* t : room->getTeleporters()) {
			if (checkPosition == t->position) {
				validTele = false;
			}
		}
		for (Character* e : room->getEnemies()) {
			if (checkPosition == e->position) {
				validTele = false;
			}
		}
		if (checkPosition == vec3(room->spawnX, 1, room->spawnY)) {
			validTele = false;
		}
	}
	return checkPosition + room->position;
	
}

Room* Floor::getTeleporterDestination(Room* room) {
	bool validDes = false;
	Room* checkDes = this->pActive;
	while (!validDes) {
		validDes = true;
		checkDes = this->rooms.at((int)rand() % this->rooms.size());
		if (checkDes == room) {
			validDes = false;
		}
		for (Teleporter* t : room->getTeleporters()) {
			if (checkDes == t->pDestination) {
				validDes = false;
			}
		}
	}
	return checkDes;
}
