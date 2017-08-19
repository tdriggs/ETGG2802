#include "AABBMesh.h"

AABBMesh::AABBMesh(AABB* box, Texture* texture) {
	vector<float> pdata = {
		//front
		box->mins.x,box->mins.y,box->maxs.z,    box->maxs.x,box->mins.y,box->maxs.z,     box->maxs.x,box->maxs.y,box->maxs.z,      box->mins.x,box->maxs.y,box->maxs.z,
		//left
		box->mins.x,box->mins.y,box->mins.z,    box->mins.x,box->mins.y,box->maxs.z,     box->mins.x,box->maxs.y,box->maxs.z,      box->mins.x,box->maxs.y,box->mins.z,
		//right
		box->maxs.x,box->mins.y,box->maxs.z,    box->maxs.x,box->mins.y,box->mins.z,     box->maxs.x,box->maxs.y,box->mins.z,      box->maxs.x,box->maxs.y,box->maxs.z,
		//back
		box->maxs.x,box->mins.y,box->mins.z,    box->mins.x,box->mins.y,box->mins.z,     box->mins.x,box->maxs.y,box->mins.z,      box->maxs.x,box->maxs.y,box->mins.z,
		//top
		box->mins.x,box->maxs.y,box->maxs.z,    box->maxs.x,box->maxs.y,box->maxs.z,     box->maxs.x,box->maxs.y,box->mins.z,      box->mins.x,box->maxs.y,box->mins.z,
		//bottom
		box->mins.x,box->mins.y,box->mins.z,    box->maxs.x,box->mins.y,box->mins.z,     box->maxs.x,box->mins.y,box->maxs.z,      box->mins.x,box->mins.y,box->maxs.z
	};

	vector<float> tdata = {
		0,0,    1,0,   1,1,   0,1,
		0,0,    1,0,   1,1,   0,1,
		0,0,    1,0,   1,1,   0,1,
		0,0,    1,0,   1,1,   0,1,
		0,0,    1,0,   1,1,   0,1,
		0,0,    1,0,   1,1,   0,1
	};

	vector<float> ndata = {
		0,0,1,  0,0,1,  0,0,1,  0,0,1,
		-1,0,0, -1,0,0, -1,0,0, -1,0,0,
		1,0,0,  1,0,0,  1,0,0,  1,0,0,
		0,0,-1, 0,0,-1, 0,0,-1, 0,0,-1,
		0,1,0,  0,1,0,  0,1,0,  0,1,0,
		0,-1,0, 0,-1,0, 0,-1,0, 0,-1,0
	};

	vector<unsigned short> idata = {
		0,1,2,      0,2,3,
		4,5,6,      4,6,7,
		8,9,10,     8,10,11,
		12,13,14,   12,14,15,
		16,17,18,   16,18,19,
		20,21,22,   20,22,23
	};

	VertexAttrib pos = VertexAttrib();
	pos.location = Program::POSITION_INDEX;
	pos.stride = 3 * 4;
	pos.size = 3;
	pos.data.resize(pdata.size() * 4);
	memcpy(&pos.data[0], &pdata[0], pos.data.size());
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

	this->numindices = idata.size();

	this->init();

	this->createMaterial("texture", texture, NULL, NULL, NULL, 0, numindices);
}
