#include "TeleporterMesh.h"

TeleporterMesh::TeleporterMesh(Texture* front, Texture* right, Texture* left, Texture* back, Texture* topAndBot) : Mesh()
{
	vector<float> pdata = 
	{
	//front
	-0.5,1,0.5,
	0.5,1,0.5,
	0.5,-1,0.5,
	-0.5,-1,0.5,
	//right
	0.5,1,0.5,
	0.5,1,-0.5,
	0.5,-1,-0.5,
	0.5,-1,0.5,
	//back
	0.5,1,-0.5,
	-0.5,1,-0.5,
	-0.5,-1,-0.5,
	0.5,-1,-0.5,
	//left
	-0.5,1,-0.5,
	-0.5,1,0.5,
	-0.5,-1,0.5,
	-0.5,-1,-0.5,
	//top
	-0.5,1,0.5,
	0.5,1,0.5,
	0.5,1,-0.5,
	-0.5,1,-0.5,
	//bot
	-0.5,-1,0.5,
	0.5,-1,0.5,
	0.5,-1,-0.5,
	-0.5,-1,-0.5
	};
	vector<float> tdata = 
	{
		//front
		0,1,1,1,1,0,0,0,
		//right
		0,1,1,1,1,0,0,0,
		//back
		0,1,1,1,1,0,0,0,
		//left
		0,1,1,1,1,0,0,0,
		//top
		0,1,1,1,1,0,0,0,
		//bot
		0,1,1,1,1,0,0,0
	};
	vector<float> ndata =
	{
		//front
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1,
		//right
		1,0,0,
		1,0,0,
		1,0,0,
		1,0,0,
		//back
		0,0,-1,
		0,0,-1,
		0,0,-1,
		0,0,-1,
		//left
		-1,0,0,
		-1,0,0,
		-1,0,0,
		-1,0,0,
		//top
		0,1,0,
		0,1,0,
		0,1,0,
		0,1,0,
		//bot
		0,-1,0,
		0,-1,0,
		0,-1,0,
		0,-1,0
	};
	vector<unsigned short> idata = 
	{
		//front
		0,1,2,
		0,3,2,
		//right
		4,5,6,
		4,7,6,
		//back
		8,9,10,
		8,11,10,
		//left
		12,13,14,
		12,15,14,
		//top
		19,18,17,
		19,16,17,
		//bot
		20,21,22,
		20,23,22
	};

	this->numindices = idata.size();
	this->numvertices = pdata.size() / 3;

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

	this->init(); 

	this->createMaterial("front", front, new SolidTexture(0, 0, 0, 1), NULL, NULL, 0, 6);
	this->createMaterial("right", right, new SolidTexture(0, 0, 0, 1), NULL, NULL, 6, 12);
	this->createMaterial("back", back, new SolidTexture(0, 0, 0, 1), NULL, NULL, 12, 18);
	this->createMaterial("left", left, new SolidTexture(0, 0, 0, 1), NULL, NULL, 18, 24);
	this->createMaterial("topAndBot", topAndBot, new SolidTexture(0, 0, 0, 1), NULL, NULL, 24, this->numindices);
}
