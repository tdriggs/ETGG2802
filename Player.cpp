#include "Player.h"

Player* Player::player = NULL;

Player::Player(vec3 pos) : Character(pos, "/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/Meshs/Ninja/ninja.ms3d.mesh", 0.15, vec3(0, 0, 0), vec4(0, 1, 0, 180)) {
	this->weaponIndex = 0;
	this->moveSpeed = 5;
	this->targetingOffset = 0.5;
	this->weaponInventory = vector<Weapon*>();
	this->weaponInventory.push_back(new Melee());

	this->cameraMode = CameraMode::ThirdPerson;
	switch (this->cameraMode)
	{
	case CameraMode::FirstPerson:
	{
		this->camOffset = vec3(0, 0, 0);
		this->camHeight = vec3(0, 1, 0);
		break;
	}
	case CameraMode::ThirdPerson:
	{
		this->camOffset = vec3(-1.5, 0, -1.5);
		this->camHeight = vec3(0, 2, 0);
		break;
	}
	default:
		break;
	}

	this->playerCam = new Camera(pos + (this->camOffset * this->lookVector) + this->camHeight);
	this->look_at(this->position + this->lookVector);
	this->setAnimations();
	this->setAnimation("Idle");
}

void Player::setAnimations()
{
	Animation a = Animation("Idle", 3, 3, 1.0f);
	this->animations.push_back(a);
	Animation a1 = Animation("Walk", 1, 13, 0.4f);
	this->animations.push_back(a1);
	Animation a2 = Animation("Attack", 60, 68, 0.3f);
	this->animations.push_back(a2);
	Animation a3 = Animation("Death", 174, 182, 0.1f);
	this->animations.push_back(a3);
}

Player* Player::getInstance()
{
	if (Player::player == NULL) {
		Player::player = new Player(World::getInstance()->getSpawnPoint());
	}
	return Player::player;
}

void Player::spawn(vec3 pos) {
	this->look_at(this->position + this->lookVector);
	this->position = pos;
}

void Player::drawCamera(Program* pProgram) {
	this->playerCam->draw(pProgram);
}

void Player::draw(Program* pProgram) {
	Character::draw(pProgram);
}

void Player::update(float elapsed) {
	if (this->health <= 0)
	{
		if (animations[currentAnimation].name != "Death")
		{
			this->setAnimation("Death");
		}
		if (currentFrame >= animations[currentAnimation].end - 1)
		{
			this->isDead = true;
		}
	}
	else 
	{
		if (velocity != vec3(0, 0, 0))
		{
			if (animations[currentAnimation].name != "Walk")
				this->setAnimation("Walk");
		}
		else
		{
			if (animations[currentAnimation].name != "Idle" && animations[currentAnimation].name != "Attack")
				this->setAnimation("Idle");
		}
		if (animations[currentAnimation].name == "Attack")
		{
			if (currentFrame >= animations[currentAnimation].end-1)
			{
				this->setAnimation("Idle");
			}
		}
		
	}
	Character::update(elapsed);
	quaternion rotationDirection = quaternion(vec3(this->euclidianRotations.x, 0, 0));
	this->lookVector = rotateVector(rotationDirection, vec3(0, 0, 1));
	this->playerCam->turn(this->euclidianRotations);
	this->updateCameraPosition();

	for (Weapon* weapon : this->weaponInventory)
	{
		weapon->update(elapsed);
	}
	
}

void Player::updateCameraPosition()
{
	playerCam->position = this->position + (this->camOffset * this->lookVector) + this->camHeight;
}

void Player::walk(float a) {
	this->velocity += lookVector * a;
}

void Player::strafe(float a) {
	this->velocity -= cross(this->lookVector, vec3(0, 1, 0)) * a;
}

void Player::rotate(double dx, double dy) {
	Character::rotate(dx);

	switch (this->cameraMode)
	{
	case CameraMode::FirstPerson:
	{
		this->euclidianRotations.y -= dy;
		break;
	}
	case CameraMode::ThirdPerson:
	{
		if ((dy <= 0 && this->camHeight.y < 2.5) || (dy >= 0 && this->camHeight.y > 1.5))
		{
			this->camHeight.y = this->camHeight.y - (dy / 40);
			this->euclidianRotations.y -= dy;
		}
		break;
	}
	default:
		break;
	}
}

void Player::look_at(vec3 coi) {
	this->playerCam->look_at(this->position + (this->camOffset * this->lookVector) + this->camHeight, coi, vec3(0, 1, 0));
	this->lookVector = normalize(coi);
}

void Player::toggleCameraMode()
{
	switch (this->cameraMode) {
	case CameraMode::FirstPerson:
	{
		this->cameraMode = CameraMode::ThirdPerson;
		this->camOffset = vec3(-2, 0, -2);
		this->camHeight = vec3(0, 1.5, 0);
		break;
	}
	case CameraMode::ThirdPerson:
	{
		this->cameraMode = CameraMode::FirstPerson;
		this->camOffset = vec3(0, 0, 0);
		this->camHeight = vec3(0, 1, 0);
		break;
	}
	default:
		break;
	}
}

void Player::attack()
{
	//if (this->animations[currentAnimation].name == "Death") 
	if (this->weaponInventory[weaponIndex]->canAttack()) 
	{
		this->weaponInventory[this->weaponIndex]->attack(this->target);

		this->setAnimation("Attack");
	}
	
}

void Player::getTarget(vector<Collidable*> possibleTargets)
{
	this->target = NULL;
	vec3 normLook = normalize(vec3(this->playerCam->negativeLook.x, 0, this->playerCam->negativeLook.z));
	
	for (int i = 0; i < possibleTargets.size(); i++)
	{
		vec3 playerToPossibleTarget = vec3(possibleTargets.at(i)->position.x, 0, possibleTargets.at(i)->position.z) - vec3(this->position.x, 0, this->position.z);

		float distance = 0;
		float direction = dot(normLook, playerToPossibleTarget);
		if (direction <= 0) {
			distance = length(playerToPossibleTarget - (normLook * direction));
		}
		else {
			distance = -length(playerToPossibleTarget - (normLook * direction));
		}

		if ((distance > 0) && (distance <= this->targetingOffset) && possibleTargets.at(i) != this->target) {
			if (this->target == NULL) {
				this->target = possibleTargets.at(i);
			}
			else {
				vec3 targetToPlayer = vec3(this->target->position.x, 0, this->target->position.z) - vec3(this->position.x, 0, this->position.z);
				float d = length(targetToPlayer - (normLook * dot(normLook, targetToPlayer)));
				if ((distance < d)) {
					this->target = possibleTargets.at(i);
				}
			}
		}
	}
}



