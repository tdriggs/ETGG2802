#include "Camera.h"

Camera::Camera(vec3 pos) {
	this->fov_h = 45;
	this->hither = 0.1f;
	this->yon = 1000.0f;
	this->aspect_ratio = 1.0f;
	this->fov_v = 1.0f / aspect_ratio * fov_h;
	this->position = pos;
	
	this->right = vec3(1, 0, 0);
	this->up = vec3(0, 1, 0);
	this->negativeLook = vec3(0, 0, 1);

	this->projmatrix = calc_projMatrix();
}

void Camera::draw(Program* prog) {
	prog->setUniform("projMatrix", this->projmatrix);
	prog->setUniform("viewMatrix", calc_viewMatrix());
	prog->setUniform("eyePos", this->position);
}

void Camera::turn(vec3 euclidianRotations) {
	quaternion q = quaternion(euclidianRotations);
	this->right = rotateVector(q, vec3(1, 0, 0));
	this->negativeLook = rotateVector(q, vec3(0, 0, -1));
	this->up = rotateVector(q, vec3(0, 1, 0));
}

void Camera::look_at(vec3 pos, vec3 coi, vec3 upVec) {
	this->position = pos;
	this->negativeLook = normalize(this->position - coi);
	this->right = normalize(cross(upVec, this->negativeLook));
	this->up = normalize(cross(this->negativeLook, this->right));
}

mat4 Camera::calc_viewMatrix()
{
	return translation(-1 * this->position) *
		mat4(this->right.x, this->up.x, this->negativeLook.x, 0,
			this->right.y, this->up.y, this->negativeLook.y, 0,
			this->right.z, this->up.z, this->negativeLook.z, 0,
			0, 0, 0, 1);
}

mat4 Camera::calc_projMatrix()
{
	return mat4(
		1 / tan(radians(this->fov_h)), 0, 0, 0,
		0, 1 / tan(radians(this->fov_v)), 0, 0,
		0, 0, 1 + 2 * this->yon / (this->hither - this->yon), -1,
		0, 0, 2 * this->hither * this->yon / (this->hither - this->yon), 0);
}
