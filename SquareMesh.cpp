#include "SquareMesh.h"

SquareMesh::SquareMesh(Texture * texture)
{
	vector<float> pdata = 
	{
		-1,1,0,
		1,1,0,
		1,-1,0,
		-1,-1,0
	};
	vector<float> tdata = 
	{
		0,1,1,1,1,0,0,0
	};
	vector<float> ndata =
	{
		0,0,1,
		0,0,1,
		0,0,1,
		0,0,1
	};
	vector<unsigned short> idata = 
	{
		0,1,2,
		0,3,2
	};

	this->numindices = idata.size();

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

	this->createMaterial("tex", texture, new SolidTexture(0, 0, 0, 1), NULL, NULL, 0, this->numindices);
}
