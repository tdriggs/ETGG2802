#include "Melee.h"

Melee::Melee():Weapon(){ 

	this->baseDamage = 25;
	this->range = 2.0;
	this->attackSpeed = 0.5;
	this->attackCooldownTimer = 0;
}

void Melee::attack(Collidable* target)
{
	if (dynamic_cast<Character*>(target)) 
	{
		vec3 q = target->position - Player::getInstance()->position;
		float d = length(q);
		if (d <= this->range)
		{
			Character* e = (Character*)target;
			e->health -= this->baseDamage;
		}
	}
	attackCooldownTimer = 0;
}
