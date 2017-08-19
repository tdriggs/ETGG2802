#include "Boss.h"


Boss::Boss(vec3 pos) : Character(pos, "/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/Meshs/Robot/robot.ms3d.mesh", 2, vec3(0, 0, 0), vec4(0, 1, 0, 90)) {
	this->state = AIState::Idle;
	this->wanderState = WanderState::Standing;
	this->aggroState = AggroState::Idle;
	this->attackState = AttackState::Idle;
	this->aggroRange = 1.5;
	this->attackRange = 2;
	this->deaggroRange = 50;
	this->wanderCooldown = (rand() % 2000) / 1000.0;
	this->wanderTimer = 0;
	this->attackCooldown = 2;
	this->attackTimer = 0;
	this->health = 200;

	this->setAnimations();
	this->setAnimation("Idle");
}

void Boss::wander()
{
	switch (this->wanderState)
	{
	case Boss::WanderState::Standing:
	{
		if (this->animations[currentAnimation].name != "Idle")
			this->setAnimation("Idle");
		if (wanderTimer >= wanderCooldown) {
			this->wanderState = WanderState::Walking;
			this->wanderTimer = 0;
			this->wanderCooldown = (rand() % 2000) / 1000.0;
			this->lookVector = normalize(vec3(((rand() % 2000) / 1000.0) - 1, 0, ((rand() % 2000) / 1000.0) - 1));
		}
		break;
	}

	case Boss::WanderState::Walking:
	{
		if (this->animations[currentAnimation].name != "Walk")
			this->setAnimation("Walk");
		this->moveForward();
		if (wanderTimer >= wanderCooldown) {
			this->wanderState = WanderState::Standing;
			this->wanderTimer = 0;
			this->wanderCooldown = (rand() % 2000) / 1000.0;
		}
		break;
	}
	default:
		break;
	}
}

bool Boss::targetInRange(float range)
{
	float distance;
	distance = length(((vec3(this->target->position.x, 0, this->target->position.z)) - vec3(this->position.x, 0, this->position.z)));
	return (distance <= range);
}

void Boss::getTarget()
{
	this->target = Player::getInstance();
}

void Boss::moveForward()
{
	this->velocity = this->lookVector;
}

void Boss::rotateTowards(vec3 destination) {
	this->lookVector = normalize(vec3(destination.x, 0, destination.z) - vec3(this->position.x, 0, this->position.z));
}

void Boss::attack(float elapsed)
{
	switch (this->attackState)
	{
	case Boss::AttackState::Idle:
	{
		this->attackTimer += elapsed;
		if (this->attackTimer >= attackCooldown && !Player::getInstance()->isDead)
		{
			this->attackState = AttackState::Attacking;
			this->attackTimer = 0;
		}

		break;
	}
	case Boss::AttackState::Attacking:
	{
		if (this->animations[currentAnimation].name != "Idle")
			this->setAnimation("Idle");
		if (this->currentFrame >= this->animations[this->currentAnimation].end - 1)
		{
			this->attackState = AttackState::Attacked;
		}
		break;
	}
	case Boss::AttackState::Attacked:
	{
		this->attackState = AttackState::Idle;
		vec3 q = Player::getInstance()->position - this->position;
		float dist = length(q);
		if (dist <= this->attackRange + 1)
		{
			Player::getInstance()->health -= 20;
		}

		break;
	}
	default:
		break;
	}
}

void Boss::aggro()
{
	switch (this->aggroState)
	{
	case Boss::AggroState::Idle:
	{
		this->aggroState = AggroState::Aggroed;
		break;
	}
	default:
		break;
	}
}

void Boss::update(float elapsed)
{
	this->wanderTimer += elapsed;

	Character::update(elapsed);
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
		switch (this->state) {
		case AIState::Idle:
		{
			this->getTarget();
			this->wander();
			if (this->targetInRange(this->aggroRange)) {
				this->state = AIState::Aggro;
			}
			break;
		}
		case AIState::Aggro:
		{
			this->rotateTowards(this->target->position);
			this->aggro();
			if (this->aggroState == AggroState::Aggroed)
			{
				this->state = AIState::Approaching;
			}
			break;
		}
		case AIState::Approaching:
		{
			if (this->animations[currentAnimation].name != "Walk")
				this->setAnimation("Walk");
			this->rotateTowards(this->target->position);
			this->moveForward();
			if (this->targetInRange(this->attackRange)) {
				this->state = AIState::Attacking;
			}
			else if (!this->targetInRange(this->deaggroRange)) {
				this->state = AIState::Idle;
			}
			break;
		}
		case AIState::Attacking:
		{
			this->rotateTowards(this->target->position);
			this->attack(elapsed);
			if (!this->targetInRange(this->attackRange)) {
				this->state = AIState::Approaching;
			}
			else if (!this->targetInRange(this->deaggroRange)) {
				this->state = AIState::Idle;
			}
			break;
		}
		default:
			break;
		}
	}

}

void Boss::setAnimations()
{
	Animation a = Animation("Idle", 26, 38, 0.2f);
	this->animations.push_back(a);
	Animation a1 = Animation("Walk", 5, 21, 0.2f);
	this->animations.push_back(a1);
}
