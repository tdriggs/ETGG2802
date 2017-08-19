#include "Enemy.h"


Enemy::Enemy(vec3 pos) : Character(pos, "/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/Meshs/Sinbad/Sinbad-mod.blend.ms3d.mesh", 0.2, vec3(0, 0, 0), vec4(0, 1, 0, 90)) {
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

	this->meshs.push_back(new SkeletonMesh("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/Meshs/Sinbad/Sinbad-mod-swords.blend.ms3d.mesh"));

	this->setAnimations();
	this->setAnimation("Idle");
}

void Enemy::wander()
{
	switch (this->wanderState)
	{
	case Enemy::WanderState::Standing:
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
		
	case Enemy::WanderState::Walking:
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

bool Enemy::targetInRange(float range)
{
	float distance;
	distance = length(((vec3(this->target->position.x, 0, this->target->position.z)) - vec3(this->position.x, 0 , this->position.z)));
	return (distance <= range);
}

void Enemy::getTarget()
{
	this->target = Player::getInstance();
}

void Enemy::moveForward()
{
	this->velocity = this->lookVector;
}

void Enemy::rotateTowards(vec3 destination) {
	this->lookVector = normalize(vec3(destination.x, 0, destination.z) - vec3(this->position.x, 0, this->position.z));
}

void Enemy::attack(float elapsed)
{
	switch (this->attackState)
	{
	case Enemy::AttackState::Idle:
	{
		this->attackTimer += elapsed;
		if (this->attackTimer >= attackCooldown  &&  !Player::getInstance()->isDead) 
		{
			this->attackState = AttackState::Attacking;
			this->attackTimer = 0;
		}
		
		break;
	}
	case Enemy::AttackState::Attacking:
	{
		if (this->animations[currentAnimation].name != "Attack 1")
			this->setAnimation("Attack 1");
		if (this->currentFrame >= this->animations[this->currentAnimation].end - 1)
		{
			this->attackState = AttackState::Attacked;
		}
		break;
	}
	case Enemy::AttackState::Attacked:
	{
		this->attackState = AttackState::Idle;
		vec3 q = Player::getInstance()->position - this->position;
		float dist = length(q);
		if (dist <= this->attackRange+1) 
		{
			Player::getInstance()->health -= 10;
		}
		
		break;
	}
	default:
		break;
	}
}

void Enemy::aggro()
{
	switch (this->aggroState)
	{
	case Enemy::AggroState::Idle:
	{	
		if(this->currentMesh != 1)
			this->aggroState = AggroState::Reaching;
		break;
	}
	case Enemy::AggroState::Reaching:
	{
		if (this->animations[currentAnimation].name != "Grab Weapon")
			this->setAnimation("Grab Weapon");
		if (this->currentFrame >= this->animations[this->currentAnimation].end - 1)
		{
			this->aggroState = AggroState::Drawing;
		}
		break;
	}
	case Enemy::AggroState::Drawing:
	{
		if (this->animations[currentAnimation].name != "Draw Weapon")
		{
			this->setAnimation("Draw Weapon");
			this->currentMesh = 1;
		}
		if (this->currentFrame >= this->animations[this->currentAnimation].end - 1)
		{
			this->aggroState = AggroState::Aggroed;
		}
		break;
	}
	default:
		break;
	}
}

void Enemy::update(float elapsed)
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

void Enemy::setAnimations()
{
	Animation a = Animation("Walk", 299, 319, 0.45f);
	this->animations.push_back(a);
	Animation a1 = Animation("Idle", 125, 181, 0.2f);
	this->animations.push_back(a1);
	Animation a2 = Animation("Draw Weapon", 76, 83, 0.4f);
	this->animations.push_back(a2);
	Animation a3 = Animation("Grab Weapon", 71, 76, 0.4f);
	this->animations.push_back(a3);
	Animation a4 = Animation("Attack 1", 267, 282, 0.4f);
	this->animations.push_back(a4);
	Animation a5 = Animation("Attack 2", 282, 298, 0.4f);
	this->animations.push_back(a5);
	Animation a6 = Animation("Death", 4, 56, 0.5f);
	this->animations.push_back(a6);
}
