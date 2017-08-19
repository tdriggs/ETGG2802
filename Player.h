#ifndef PLAYER_H
#define PLAYER_H

#include "math3d.h"
#include "Character.h"
#include "Camera.h"
#include <string>
#include "World.h"
#include "Melee.h"

using namespace std;

class Weapon;

class Player : public Character {
private:
	int weaponIndex;

	enum class CameraMode { FirstPerson, ThirdPerson };

	static Player* player;
	Camera* playerCam;
	vec3 camOffset;
	vec3 camHeight;
	CameraMode cameraMode;
	float targetingOffset;
	vector<Weapon*> weaponInventory;

	Player(vec3 pos);

public:

	static Player* getInstance();
	void spawn(vec3 pos);
	void drawCamera(Program * pProgram);
	void draw(Program* prog);
	void update(float elapsed);
	void updateCameraPosition();
	void rotate(double dx, double dy);
	void walk(float a);
	void strafe(float a);
	void look_at(vec3 coi);
	void toggleCameraMode();
	void setAnimations();
	void attack();
	void getTarget(vector<Collidable*> possibleTargets);
};

#endif
