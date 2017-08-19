#ifndef CHARACTER_H
#define CHARACTER_H

#include "math3d.h"
#include "Mesh.h"
#include "SkeletonMesh.h"
#include "Collidable.h"

class Character : public Collidable {
public:

	struct Animation
	{
		string name;
		int start;
		int end;
		float step;

		Animation(string name, int start, int end, float step)
		{
			this->name = name;
			this->start = start;
			this->end = end;
			this->step = step;
		}
	};
	
    vector<SkeletonMesh*> meshs;
	int currentMesh;
	Collidable* target;

	vec3 lookVector;
	vec3 euclidianRotations;
	vec3 velocity;
	int health;
	float moveSpeed;
	int strength;
	float scale;
	mat4 initialScaleAndRotationMat;
	int currentAnimation;
	float currentFrame;
	vector<Animation> animations;
	bool running;
	bool isDead;
	Character(vec3 pos, string meshName);
	Character(vec3 pos, string meshName, float scale, vec3 offset, vec4 axisRotation);

	virtual void setAnimations() = 0;
	void init(string meshName, float scale, vec3 offset, vec4 rotation);
	void rotate(double angle);
	void animate();
	void setAnimation(string name);
	void toggleRunning();
	void draw(Program* prog);
	void update(float elapsed);
	void onCollision(Collidable * other);
};

#endif  
