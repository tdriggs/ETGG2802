#include "Mesh.h"

Mesh::Mesh() { }

void Mesh::init()
{
	this->initVAO();
	glBindVertexArray(this->vao);

	for (VertexAttrib v : this->vertexAttribs)
	{
		this->addVertexAttrib(v);
	}

	for (VertexElementAttrib v : this->vertexElementAttribs)
	{
		this->addVertexElementAttrib(v);
	}

	glBindVertexArray(0);
}

void Mesh::initVAO()
{
	GLuint tmp[1];
	glGenVertexArrays(1, tmp);
	this->vao = tmp[0];
}

void Mesh::addVertexAttrib(VertexAttrib attrib)
{
	glBindVertexArray(this->vao);

	GLuint tmp[1];
	glGenBuffers(1, tmp);
	GLuint buffer = tmp[0];
	this->attribBuffers.push_back(buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, attrib.data.size() * sizeof(attrib.data[0]), &attrib.data[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(attrib.location);
	glVertexAttribPointer(attrib.location, attrib.size, GL_FLOAT, false, attrib.stride, 0);

	glBindVertexArray(0);
}

void Mesh::addVertexElementAttrib(VertexElementAttrib attrib)
{
	glBindVertexArray(this->vao);

	GLuint tmp[1];
	glGenBuffers(1, tmp);
	GLuint buffer = tmp[0];
	this->attribBuffers.push_back(buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, attrib.data.size() * sizeof(attrib.data[0]), &attrib.data[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::createMaterial(string name, Texture * texture, Texture * specMap, Texture * emitMap, Texture * bumpMap, int start, int count)
{
	Material m = Material();

	m.name = name;
	if (texture)
		m.texture = texture;
	else
		m.texture = new SolidTexture(0, 0, 0, 1);
	if (emitMap)
		m.emitmap = emitMap;
	else
		m.emitmap = new SolidTexture(0, 0, 0, 0);
	if (specMap)
		m.specularmap = specMap;
	else
		m.specularmap = new SolidTexture(0, 0, 0, 0);
	if (bumpMap)
		m.bumpmap = bumpMap;
	else
		m.bumpmap = new SolidTexture(0, 0, 0, 1);
	m.reflmap = new SolidTexture(0, 0, 0, 1);
	m.start = start;
	m.count = count;

	this->materials.push_back(m);
}

void Mesh::draw(Program* prog) {
	glBindVertexArray(this->vao);

	for (unsigned i = 0; i < this->materials.size(); ++i) {
		prog->setUniform("tex", materials[i].texture);
		prog->setUniform("etex", materials[i].emitmap);
		prog->setUniform("stex", materials[i].specularmap);
		//prog->setUniform("rtex", materials[i].reflmap);
		//prog->setUniform("bumpmap", materials[i].bumpmap);
		glDrawElements(GL_TRIANGLES, materials[i].count, this->dataType,
			reinterpret_cast<GLvoid*>(materials[i].start * ((this->dataType == GL_UNSIGNED_SHORT) ? 2 : 4)));
	}

	prog->checkUninitialized();

	glBindVertexArray(0);
}
