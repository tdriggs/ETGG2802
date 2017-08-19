#include "Weapon.h"
#include "Player.h"

Weapon::Weapon() { }

bool Weapon::canAttack()
{
	return attackCooldownTimer >= attackSpeed;
}

void Weapon::update(float elapsed)
{
	this->attackCooldownTimer += elapsed;
}
