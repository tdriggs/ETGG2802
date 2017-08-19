#ifndef MAIN_H
#define MAIN_H

#include "glfuncs.h"
#include <SDL.h>
#include <iostream>
#include "math3d.h"

// Back Side / Graphics
#include "ppng.h"
#include "Texture.h"
#include "Texture2D.h"
#include "ImageTexture.h"
#include "Texture2DArray.h"
#include "ImageTextureArray.h"
#include "SolidTexture.h"
#include "Program.h"
#include "Camera.h"
#include "PolyMesh.h"
#include "Player.h"

// Front Side / Game

#include "Room.h"
#include "Floor.h"
#include "World.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
using namespace std;

void APIENTRY debugcallback(GLenum source, GLenum typ,
	GLuint id_, GLenum severity, GLsizei length,
	const GLchar* message, const void* obj);

#endif
