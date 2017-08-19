#include "Teleporter.h"

Teleporter::Teleporter(vec3 position, Room* pDestination) : Collidable(position) {
	this->pulseSpeed = randrange(0.05, 0.1);
	this->pDestination = pDestination;
	this->initializeMesh();
	this->setSimpleBoundingBox(this->pMesh, 1, vec3(0, 0, 0));
	this->toggleSolid();
	this->border = vec4(this->pDestination->boundingBoxColor, 0.15);
}

void Teleporter::draw(Program* pProgram) {
	pProgram->use();
	pProgram->setUniform("border", this->border);
	pProgram->setUniform("worldMatrix", translation(this->position));
	this->pMesh->draw(pProgram);
	pProgram->setUniform("border", vec4(0, 0, 0, 0));
	//for (AABB* box : this->boundingBoxes)
		//box->draw(pProgram, this->position);
}

void Teleporter::update(float elapsed)
{
	this->border.w += elapsed * this->pulseSpeed;
	if (this->border.w < 0.1) {
		this->border.w = 0.1;
		this->pulseSpeed = abs(this->pulseSpeed);
	}
	else if (this->border.w > 0.2) {
		this->border.w = 0.2;
		this->pulseSpeed = -abs(this->pulseSpeed);
	}
}

void Teleporter::initializeMesh()
{
	Camera* cam = new Camera(pDestination->getSpawnPoint() + vec3(0, 1, 0));
	Program* tempProgram = new Program("/home/tdriggs/Code/CLionWorkspace/ETGG2802/vs.txt", "/home/tdriggs/Code/CLionWorkspace/ETGG2802/fs.txt");
	Program* blurProgram = new Program("/home/tdriggs/Code/CLionWorkspace/ETGG2802/blurvs.txt", "/home/tdriggs/Code/CLionWorkspace/ETGG2802/blurfs.txt");
	tempProgram->use();
	tempProgram->setUniform("lightPos[0]", pDestination->lights);

	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam->look_at(cam->position, cam->position + vec3(0, 0, -1), vec3(0, 1, 0));
	cam->draw(tempProgram);
	pDestination->blurDraw(tempProgram);
	this->fbo->unbind();
	Texture* tempFront = fbo->texture;

	blurProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SquareMesh* square = new SquareMesh(tempFront);
	square->draw(blurProgram);
	this->fbo->unbind();
	tempFront = fbo->texture;

	tempProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam->look_at(cam->position, cam->position + vec3(0, 0, 1), vec3(0, 1, 0));
	cam->draw(tempProgram);
	pDestination->blurDraw(tempProgram);
	this->fbo->unbind();
	Texture* tempBack = fbo->texture;

	blurProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	square = new SquareMesh(tempBack);
	square->draw(blurProgram);
	this->fbo->unbind();
	tempBack = fbo->texture;

	tempProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam->look_at(cam->position, cam->position + vec3(1, 0, 0), vec3(0, 1, 0));
	cam->draw(tempProgram);
	pDestination->blurDraw(tempProgram);
	this->fbo->unbind();
	Texture* tempRight = fbo->texture;

	blurProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	square = new SquareMesh(tempRight);
	square->draw(blurProgram);
	this->fbo->unbind();
	tempRight = fbo->texture;

	tempProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cam->look_at(cam->position, cam->position + vec3(-1, 0, 0), vec3(0, 1, 0));
	cam->draw(tempProgram);
	pDestination->blurDraw(tempProgram);
	this->fbo->unbind();
	Texture* tempLeft = fbo->texture;

	blurProgram->use();
	this->fbo = new Framebuffer2D(256, 512);
	this->fbo->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	square = new SquareMesh(tempLeft);
	square->draw(blurProgram);
	this->fbo->unbind();
	tempLeft = fbo->texture;

	this->pMesh = new TeleporterMesh(tempFront, tempRight, tempLeft, tempBack, new SolidTexture(this->border.x, this->border.y, this->border.z, 1));
}

void Teleporter::onCollision(Collidable * other)
{
	if (World::getInstance()->getActiveEnemies().size() == 0)
	{
		World::getInstance()->setCurrentRoom(this->pDestination);
		Player::getInstance()->spawn(World::getInstance()->getSpawnPoint());
	}
}