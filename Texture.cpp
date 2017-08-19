#include "Texture.h"

Texture* Texture::active_textures[128];

Texture::~Texture() { }

bool Texture::isPowerOf2(int x) {
	return  ((x - 1)&x) == 0;
}

void Texture::bind(int unit) {
	assert(tex != 0);
	assert(type != 0);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, this->tex);
	if (active_textures[unit])
		active_textures[unit]->on_units.erase(unit);
	on_units.insert(unit);
	active_textures[unit] = this;
}

void Texture::unbind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, 0);
	on_units.erase(unit);
	active_textures[unit] = NULL;
}

void Texture::unbind() {
	for (int u : on_units) {
		glActiveTexture(GL_TEXTURE0 + u);
		glBindTexture(type, 0);
		active_textures[u] = NULL;
	}
	on_units.clear();
}

Texture::Texture(GLenum ty) : type(ty) {
	GLuint tmp[1];
	glGenTextures(1, tmp);
	this->tex = tmp[0];
}
