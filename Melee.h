#ifndef MELEE_H
#define MELEE_H

#include "Weapon.h"
#include "Player.h"
class Melee : public Weapon {
public:

	Melee();

	void attack(Collidable* target);
};

#endif
