#include "SkeletonMesh.h"

SkeletonMesh::SkeletonMesh(string filename) : Mesh()
{
	this->filename = filename;
	this->dataType = GL_UNSIGNED_INT;
	this->frame = 0;

	ifstream fp(filename, ios::binary);
	if (!fp)
		throw runtime_error("Cannot open file " + filename);

	string line;

	getline(fp, line);

	if (line != "mesh_01sbr")
		throw runtime_error("Incorrect mesh format: " + line + "; expected mesh_01sbr");

	while (true) {
		getline(fp, line);
		if (fp.fail()) {
			assert(0);
		}
		istringstream iss(line);
		string word;
		iss >> word;

		if (iss.fail()) {
		}
		else if (word == "num_vertices")
			iss >> this->numvertices;
		else if (word == "num_indices")
			iss >> this->numindices;
		else if (word == "positions") {
			VertexAttrib v;
			v.location = Program::POSITION_INDEX;
			v.stride = 3 * 4;
			v.size = 3;
			v.data.resize(this->numvertices * v.stride);

			fp.read(&v.data[0], v.data.size());

			this->vertexAttribs.push_back(v);
		}
		else if (word == "texcoords") {
			VertexAttrib v;
			v.location = Program::TEXCOORD_INDEX;
			v.stride = 2 * 4;
			v.size = 2;
			v.data.resize(this->numvertices * v.stride);

			fp.read(&v.data[0], v.data.size());

			this->vertexAttribs.push_back(v);
		}
		else if (word == "normals") {
			VertexAttrib v;
			v.location = Program::NORMAL_INDEX;
			v.stride = 3 * 4;
			v.size = 3;
			v.data.resize(this->numvertices * v.stride);

			fp.read(&v.data[0], v.data.size());

			this->vertexAttribs.push_back(v);
		}
		else if (word == "tangents") {
			fp.seekg(this->numvertices * 4 * 3, ios::cur);
		}
		else if (word == "bitangents") {
			fp.seekg(this->numvertices * 4 * 3, ios::cur);
		}
		else if (word == "indices") {
			VertexElementAttrib v;
			v.data.resize(this->numindices * 4);

			fp.read(&v.data[0], v.data.size());

			this->vertexElementAttribs.push_back(v);
		}
		else if (word == "boneowner") {
			VertexAttrib v;
			v.location = Program::BONE_INDEX;
			v.stride = 4;
			v.size = 3;
			v.data.resize(this->numvertices * v.stride);

			fp.read(&v.data[0], v.data.size());

			this->vertexAttribs.push_back(v);
		}
		else if (word == "boneheads") {
			vector<vec3> bdata;
			bdata.resize(this->numbones);
			fp.read((char*)&bdata[0], bdata.size() * sizeof(bdata[0]));
			boneheads = new DataTexture(bdata, numbones, 1);
		}
		else if (word == "numbones") {
			iss >> this->numbones;
		}
		else if (word == "boneparents") {
			vector<float> bdata;
			bdata.resize(this->numbones);
			fp.read((char*)&bdata[0], bdata.size() * sizeof(bdata[0]));
			boneparents = new DataTexture(bdata, numbones, 1);
		}
		else if (word == "numframes") {
			iss >> numframes;
		}
		else if (word == "rotations") {
			vector<vec4> bdata;
			bdata.resize(numbones*numframes);
			fp.read((char*)&bdata[0], bdata.size() * sizeof(bdata[0]));
		}
		else if (word == "translations") {
			vector<vec4> bdata;
			bdata.resize(numbones*numframes);
			fp.read((char*)&bdata[0], bdata.size() * sizeof(bdata[0]));
		}
		else if (word == "matrices") {
			vector<vec4> bdata;
			bdata.resize(numbones*numframes * 4);
			fp.read((char*)&bdata[0], bdata.size() * sizeof(bdata[0]));
		}
		else if (word == "quaternions") {
			vector<vec4> bdata;
			bdata.resize(numbones*numframes);
			fp.read((char*)&bdata[0], bdata.size() * sizeof(bdata[0]));
			bonequats = new DataTexture(bdata, numframes, numbones);
		}
		else if (word == "material") {
			int start, num;
			string mtlname;
			float Kdr, Kdg, Kdb;
			iss >> start >> num >> mtlname >> Kdr >> Kdg >> Kdb;
			Material m;
			m.name = mtlname;
			while (1) {
				string key, value;
				iss >> key >> value;

				if (iss.fail())
					break;

				if (key == "map_Kd")
					m.texture = new ImageTexture(value);
				else if (key == "map_Ks")
					m.specularmap = new ImageTexture(value);
				else if (key == "map_Ke")
					m.emitmap = new ImageTexture(value);
				else if (key == "refl")
					m.reflmap = new ImageTexture(value);
				else if (key == "map_Bump")
					m.bumpmap = new ImageTexture(value);
			}

			this->createMaterial(m.name, m.texture, m.emitmap, m.specularmap, m.bumpmap, start, num);
		}
		else if (word == "end")
			break;
		else {
			cerr << "Unknown word: " << word << "\n" << filename << "\n";
			assert(0);
		}
	}

	glBindVertexArray(0);

	this->init();
}

void SkeletonMesh::draw(Program * prog)
{
	glBindVertexArray(this->vao);

	if (boneparents)
		prog->setUniform("boneparents", boneparents);
	if (boneheads)
		prog->setUniform("boneheads", boneheads);
	if (bonequats)
		prog->setUniform("bonequats", bonequats);

	prog->setUniform("frame", this->frame);

	Mesh::draw(prog);
}
