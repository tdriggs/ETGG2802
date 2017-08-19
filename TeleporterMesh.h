#ifndef TELEPORTERMESH_H
#define TELEPORTERMESH_H

#include "Mesh.h"
#include "Texture.h"

class TeleporterMesh : public Mesh {
public:
	
	TeleporterMesh(Texture* front, Texture* right, Texture* left, Texture* back, Texture* topAndBot);
};

#endif
