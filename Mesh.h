#ifndef MESH_H
#define MESH_H

#include "Program.h"
#include "SolidTexture.h"
#include "ImageTexture.h"
#include "DataTexture.h"

class Mesh {

public:

    struct Material {
    public:

        string name;
        Texture* texture = NULL;
        Texture* emitmap = NULL;
        Texture* specularmap = NULL;
        Texture* reflmap = NULL;
        Texture* bumpmap = NULL;
		int start, count;
    };

	struct VertexAttrib {
	public:

		vector<char> data;
		int location;
		int size;
		int stride;
	};

	struct VertexElementAttrib {
	public:

		vector<char> data;
	};

    vector<Material> materials;
    int numvertices;
    int numindices;
    GLuint vao;
	vector<GLuint> attribBuffers;
	vector<VertexAttrib> vertexAttribs;
	vector<VertexElementAttrib> vertexElementAttribs;
	GLenum dataType = GL_UNSIGNED_SHORT;
    
	Mesh();

	void init();
	void initVAO();
	void addVertexAttrib(VertexAttrib attrib);
	void addVertexElementAttrib(VertexElementAttrib attrib);
	void createMaterial(string name, Texture * texture, Texture * emitMap, Texture * specMap, Texture * bumpMap, int start, int count);
    void draw(Program* prog);
};

#endif
