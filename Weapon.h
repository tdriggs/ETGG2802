#ifndef WEAPON_H
#define WEAPON_H

#include "Collidable.h"
#include "Program.h"
#include "Mesh.h"

class Weapon{
public:

	int baseDamage;
	float range;
	float attackSpeed;
	float attackCooldownTimer;

	Weapon();

	
	virtual void attack(Collidable* target) = 0;
	bool canAttack();
	void update(float elapsed);

};

#endif
