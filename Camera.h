#ifndef CAMERA_H
#define CAMERA_H

#include "Program.h"

class Camera {
public:

	float fov_h;
	float hither;
	float yon;
	float aspect_ratio;
	float fov_v;

	vec3 position;
	vec3 right, up, negativeLook;
	mat4 projmatrix;

	Camera(vec3 pos);

	void draw(Program* prog);
	void turn(vec3 euclidianRotations);
	void look_at(vec3 pos, vec3 coi, vec3 up);
	mat4 calc_viewMatrix();
	mat4 calc_projMatrix();
};

#endif
