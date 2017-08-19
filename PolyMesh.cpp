#include "PolyMesh.h"

PolyMesh::PolyMesh(int width, int height, int depth) {
	vector<float> floorVdata = { };
	vector<float> ceilingVdata = { };
	vector<float> wallVdata = { };
	vector<float> tdata = { };
	vector<float> ndata = { };
	vector<unsigned short> idata = { };

	// Create the bottom of the PolyMesh
	for (int i = (-width / 2); i < (width / 2); i++) {
		for (int j = (-depth / 2); j < (depth / 2); j++) {
			// Bottom Left
			floorVdata.push_back(i);
			floorVdata.push_back(0);
			floorVdata.push_back(j);
			// Top Left
			floorVdata.push_back(i);
			floorVdata.push_back(0);
			floorVdata.push_back(j + 1);
			// Top Right
			floorVdata.push_back(i + 1);
			floorVdata.push_back(0);
			floorVdata.push_back(j + 1);
			// Bottom Right
			floorVdata.push_back(i + 1);
			floorVdata.push_back(0);
			floorVdata.push_back(j);

			// Add the texture coordinates for the square
			// Bottom Left
			tdata.push_back(0);
			tdata.push_back(1);
			// Top Left
			tdata.push_back(0);
			tdata.push_back(0);
			// Top Right
			tdata.push_back(1);
			tdata.push_back(0);
			// Bottom Right
			tdata.push_back(1);
			tdata.push_back(1);

			// Add the normal data for each vertex of the square
			// Bottom Left
			ndata.push_back(0);
			ndata.push_back(1);
			ndata.push_back(0);
			// Top Left
			ndata.push_back(0);
			ndata.push_back(1);
			ndata.push_back(0);
			// Top Right
			ndata.push_back(0);
			ndata.push_back(1);
			ndata.push_back(0);
			// Bottom Right
			ndata.push_back(0);
			ndata.push_back(1);
			ndata.push_back(0);
		}
	}

	int lastVertexIndex = floorVdata.size();
	// Add the traingle data for each square
	for (int i = 0; i < lastVertexIndex; i += 4) {
		// Triangle One
		idata.push_back(i);
		idata.push_back(i + 1);
		idata.push_back(i + 2);
		// Triangle Two
		idata.push_back(i);
		idata.push_back(i + 3);
		idata.push_back(i + 2);
	}

	float floorIndices = idata.size() / 3.0;

	// Create the top of the PolyMesh
	for (int i = (-width / 2); i < (width / 2); i++) {
		for (int j = (-depth / 2); j < (depth / 2); j++) {
			// Bottom Left
			ceilingVdata.push_back(i);
			ceilingVdata.push_back(height);
			ceilingVdata.push_back(j);
			// Top Left
			ceilingVdata.push_back(i);
			ceilingVdata.push_back(height);
			ceilingVdata.push_back(j + 1);
			// Top Right
			ceilingVdata.push_back(i + 1);
			ceilingVdata.push_back(height);
			ceilingVdata.push_back(j + 1);
			// Bottom Right
			ceilingVdata.push_back(i + 1);
			ceilingVdata.push_back(height);
			ceilingVdata.push_back(j);

			// Add the texture coordinates for the square
			// Bottom Left
			tdata.push_back(0);
			tdata.push_back(1);
			// Top Left
			tdata.push_back(0);
			tdata.push_back(0);
			// Top Right
			tdata.push_back(1);
			tdata.push_back(0);
			// Bottom Right
			tdata.push_back(1);
			tdata.push_back(1);

			// Add the normal data for each vertex of the square
			// Bottom Left
			ndata.push_back(0);
			ndata.push_back(-1);
			ndata.push_back(0);
			// Top Left
			ndata.push_back(0);
			ndata.push_back(-1);
			ndata.push_back(0);
			// Top Right
			ndata.push_back(0);
			ndata.push_back(-1);
			ndata.push_back(0);
			// Bottom Right
			ndata.push_back(0);
			ndata.push_back(-1);
			ndata.push_back(0);
		}
	}

	lastVertexIndex = ceilingVdata.size();
	// Add the traingle data for each square
	for (int i = 0; i < lastVertexIndex; i += 4) {
		// Triangle One
		idata.push_back(i);
		idata.push_back(i + 1);
		idata.push_back(i + 2);
		// Triangle Two
		idata.push_back(i);
		idata.push_back(i + 3);
		idata.push_back(i + 2);
	}

	float ceilingIndices = (idata.size() / 3.0) - floorIndices;

	// Create the walls for the PolyMesh
	for (int i = (-width / 2); i < (width / 2); i++) {
		for (int h = 0; h < height; h++) {
			// Add the lower wall
			// Bottom Left
			wallVdata.push_back(i);
			wallVdata.push_back(h);
			wallVdata.push_back(-depth / 2);
			// Top Left
			wallVdata.push_back(i + 1);
			wallVdata.push_back(h);
			wallVdata.push_back(-depth / 2);
			// Top Right
			wallVdata.push_back(i + 1);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(-depth / 2);
			// Bottom Right
			wallVdata.push_back(i);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(-depth / 2);

			// Bottom Left
			tdata.push_back(0);
			tdata.push_back(0);
			// Top Left
			tdata.push_back(1);
			tdata.push_back(0);
			// Top Right
			tdata.push_back(1);
			tdata.push_back(1);
			// Bottom Right
			tdata.push_back(0);
			tdata.push_back(1);

			// Bottom Left
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(1);
			// Top Left
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(1);
			// Top Right
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(1);
			// Bottom Right
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(1);

			// Add the upper wall
			// Bottom Left
			wallVdata.push_back(i);
			wallVdata.push_back(h);
			wallVdata.push_back(depth / 2);
			// Top Left
			wallVdata.push_back(i + 1);
			wallVdata.push_back(h);
			wallVdata.push_back(depth / 2);
			// Top Right
			wallVdata.push_back(i + 1);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(depth / 2);
			// Bottom Right
			wallVdata.push_back(i);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(depth / 2);

			// Bottom Left
			tdata.push_back(0);
			tdata.push_back(0);
			// Top Left
			tdata.push_back(1);
			tdata.push_back(0);
			// Top Right
			tdata.push_back(1);
			tdata.push_back(1);
			// Bottom Right
			tdata.push_back(0);
			tdata.push_back(1);

			// Bottom Left
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(-1);
			// Top Left
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(-1);
			// Top Right
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(-1);
			// Bottom Right
			ndata.push_back(0);
			ndata.push_back(0);
			ndata.push_back(-1);
		}
	}

	// Create the walls for the PolyMesh
	for (int j = (-depth / 2); j < (depth / 2); j++) {
		for (int h = 0; h < height; h++) {
			// Add the left wall
			// Bottom Left
			wallVdata.push_back(-width / 2);
			wallVdata.push_back(h);
			wallVdata.push_back(j);
			// Top Left
			wallVdata.push_back(-width / 2);
			wallVdata.push_back(h);
			wallVdata.push_back(j + 1);
			// Top Right
			wallVdata.push_back(-width / 2);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(j + 1);
			// Bottom Right
			wallVdata.push_back(-width / 2);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(j);

			// Bottom Left
			tdata.push_back(0);
			tdata.push_back(0);
			// Top Left
			tdata.push_back(1);
			tdata.push_back(0);
			// Top Right
			tdata.push_back(1);
			tdata.push_back(1);
			// Bottom Right
			tdata.push_back(0);
			tdata.push_back(1);

			// Bottom Left
			ndata.push_back(1);
			ndata.push_back(0);
			ndata.push_back(0);
			// Top Left
			ndata.push_back(1);
			ndata.push_back(0);
			ndata.push_back(0);
			// Top Right
			ndata.push_back(1);
			ndata.push_back(0);
			ndata.push_back(0);
			// Bottom Right
			ndata.push_back(1);
			ndata.push_back(0);
			ndata.push_back(0);

			// Add the upper wall
			// Bottom Left
			wallVdata.push_back(width / 2);
			wallVdata.push_back(h);
			wallVdata.push_back(j);
			// Top Left
			wallVdata.push_back(width / 2);
			wallVdata.push_back(h);
			wallVdata.push_back(j + 1);
			// Top Right
			wallVdata.push_back(width / 2);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(j + 1);
			// Bottom Right
			wallVdata.push_back(width / 2);
			wallVdata.push_back(h + 1);
			wallVdata.push_back(j);

			// Bottom Left
			tdata.push_back(0);
			tdata.push_back(0);
			// Top Left
			tdata.push_back(1);
			tdata.push_back(0);
			// Top Right
			tdata.push_back(1);
			tdata.push_back(1);
			// Bottom Right
			tdata.push_back(0);
			tdata.push_back(1);

			// Bottom Left
			ndata.push_back(-1);
			ndata.push_back(0);
			ndata.push_back(0);
			// Top Left
			ndata.push_back(-1);
			ndata.push_back(0);
			ndata.push_back(0);
			// Top Right
			ndata.push_back(-1);
			ndata.push_back(0);
			ndata.push_back(0);
			// Bottom Right
			ndata.push_back(-1);
			ndata.push_back(0);
			ndata.push_back(0);
		}
	}

	// Add the traingle data for each square
	for (int i = 0; i < wallVdata.size(); i += 4) {
		// Triangle One
		idata.push_back(i);
		idata.push_back(i + 1);
		idata.push_back(i + 2);
		// Triangle Two
		idata.push_back(i);
		idata.push_back(i + 3);
		idata.push_back(i + 2);
	}

	vector<float> vdata = vector<float>();
	for (float num : floorVdata)
		vdata.push_back(num);
	for (float num : ceilingVdata)
		vdata.push_back(num);
	for (float num : wallVdata)
		vdata.push_back(num);


	VertexAttrib pos = VertexAttrib();
	pos.location = Program::POSITION_INDEX;
	pos.stride = 3 * 4;
	pos.size = 3;
	pos.data.resize(vdata.size() * 4);
	memcpy(&pos.data[0], &vdata[0], pos.data.size());
	this->vertexAttribs.push_back(pos);

	VertexAttrib tex = VertexAttrib();
	tex.location = Program::TEXCOORD_INDEX;
	tex.stride = 2 * 4;
	tex.size = 2;
	tex.data.resize(tdata.size() * 4);
	memcpy(&tex.data[0], &tdata[0], tex.data.size());
	this->vertexAttribs.push_back(tex);

	VertexAttrib nor = VertexAttrib();
	nor.location = Program::NORMAL_INDEX;
	nor.stride = 3 * 4;
	nor.size = 3;
	nor.data.resize(ndata.size() * 4);
	memcpy(&nor.data[0], &ndata[0], nor.data.size());
	this->vertexAttribs.push_back(nor);

	VertexElementAttrib ind = VertexElementAttrib();
	ind.data.resize(idata.size() * 2);
	memcpy(&ind.data[0], &idata[0], ind.data.size());
	this->vertexElementAttribs.push_back(ind);

	this->numindices = idata.size() - ceilingIndices;

	this->init();

	this->createMaterial("floor", new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/World Textures/Floor.png"), new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/World Textures/FloorS.png"), NULL, NULL, 0, floorIndices);
	this->createMaterial("ceiling", new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/World Textures/Ceiling.png"), NULL, new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/World Textures/CeilingE.png"), NULL, floorIndices, ceilingIndices);
	this->createMaterial("walls", new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/World Textures/Walls.png"), new ImageTexture("/home/tdriggs/Code/CLionWorkspace/ETGG2802/Resources/World Textures/WallsS.png"), NULL, NULL, ceilingIndices, numindices);
}
