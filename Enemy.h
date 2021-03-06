#ifndef ENEMY_H
#define ENEMY_H

#include "math3d.h"
#include "Program.h"
#include "Character.h"
#include "Player.h"

class Enemy : public Character {
public:

	enum class AIState { Idle, Aggro, Approaching, Attacking };
	enum class WanderState { Standing, Walking };
	enum class AggroState { Idle, Reaching, Drawing, Aggroed };
	enum class AttackState { Idle, Attacking, Attacked };

	AIState state;
	WanderState wanderState;
	AggroState aggroState;
	AttackState attackState;
	float aggroRange;
	float attackRange;
	float deaggroRange;
	float wanderTimer;
	float wanderCooldown;
	float attackTimer;
	float attackCooldown;

	Enemy(vec3 pos);

	void wander();
	bool targetInRange(float range);
	void getTarget();
	void moveForward();
	void rotateTowards(vec3 destination);
	void attack(float elapsed);
	void aggro();
	void update(float elapsed);
	void setAnimations();
};

#endif
