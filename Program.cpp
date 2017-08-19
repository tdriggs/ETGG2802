#include "Program.h"

Program* Program::active = NULL;

Program::Setter::Setter(string n, int lo) {
	name = n;
	loc = lo;
}

Program::Setter::Setter() { }

void Program::Setter::set(float value) {
	throw runtime_error("Trying to set uniform " + name + " to a float");
}

void Program::Setter::set(const vec2& value) {
	throw runtime_error("Trying to set uniform " + name + " to a vec2");
}

void Program::Setter::set(const ivec2& value) {
	throw runtime_error("Trying to set uniform " + name + " to an ivec2");
}

void Program::Setter::set(const vec3& value) {
	throw runtime_error("Trying to set uniform " + name + " to a vec3");
}

void Program::Setter::set(const vec4& value) {
	throw runtime_error("Trying to set uniform " + name + " to a vec4");
}

void Program::Setter::set(const vector<float>& value) {
	throw runtime_error("Trying to set uniform " + name + " to a float array");
}

void Program::Setter::set(const vector<vec2>& value) {
	throw runtime_error("Trying to set uniform " + name + " to a vec2 array");
}

void Program::Setter::set(const vector<vec3>& value) {
	throw runtime_error("Trying to set uniform " + name + " to a vec3 array");
}

void Program::Setter::set(const vector<vec4>& value) {
	throw runtime_error("Trying to set uniform " + name + " to a vec4 array");
}

void Program::Setter::set(const vector<mat4>& value) {
	throw runtime_error("Trying to set uniform " + name + " to a mat4 array");
}

void Program::Setter::set(const mat4& value) {
	throw runtime_error("Trying to set uniform " + name + " to a mat4");
}

void Program::Setter::set(Texture* value) {
	throw runtime_error("Trying to set uniform " + name + " to a Texture");
}

Program::FloatSetter::FloatSetter(string name, int loc) : Setter(name, loc) {}

void Program::FloatSetter::set(float v) {
	glUniform1f(this->loc, v);
}

Program::IntSetter::IntSetter(string name, int loc) : Setter(name, loc) { }

void Program::IntSetter::set(float v) {
	glUniform1i(this->loc, (int)v);
}

Program::UIntSetter::UIntSetter(string name, int loc) : Setter(name, loc) { }

void Program::UIntSetter::set(float v) {
	glUniform1ui(this->loc, (unsigned)v);
}

Program::Vec2Setter::Vec2Setter(string name, int loc) : Setter(name, loc) { }

void Program::Vec2Setter::set(const vec2& v) {
	glUniform2f(this->loc, v.x, v.y);
}

Program::IVec2Setter::IVec2Setter(string name, int loc) : Setter(name, loc) { }

void Program::IVec2Setter::set(const ivec2& v) {
	glUniform2i(this->loc, v.x, v.y);
}

Program::Vec3Setter::Vec3Setter(string name, int loc) : Setter(name, loc) { }

void Program::Vec3Setter::set(const vec3& v) {
	glUniform3f(this->loc, v.x, v.y, v.z);
}

Program::Vec4Setter::Vec4Setter(string name, int loc) : Setter(name, loc) { }

void Program::Vec4Setter::set(const vec4& v)  {
	glUniform4f(this->loc, v.x, v.y, v.z, v.w);
}

Program::FloatArraySetter::FloatArraySetter(string name, int loc, int sz) : Setter(name, loc), size(sz) { }

void Program::FloatArraySetter::set(const vector<float>& v) {
	if (v.size() != size)
		throw runtime_error("Bad size: Got " + str(v.size()) + " but expected " + str(size));
	glUniform1fv(this->loc, size, (float*)&v[0]);
}

Program::Vec2ArraySetter::Vec2ArraySetter(string name, int loc, int sz) : Setter(name, loc), size(sz) { }

void Program::Vec2ArraySetter::set(const vector<vec2>& v) {
	if (v.size() != size)
		throw runtime_error("Bad size: Got " + str(v.size()) + " but expected " + str(size));
	glUniform2fv(this->loc, size, (float*)&v[0]);
}

Program::Vec3ArraySetter::Vec3ArraySetter(string name, int loc, int sz) : Setter(name, loc), size(sz) { }

void Program::Vec3ArraySetter::set(const vector<vec3>& v) {
	if (v.size() != size)
		throw runtime_error("Bad size: Got " + str(v.size()) + " but expected " + str(size));
	glUniform3fv(this->loc, size, (float*)&v[0]);
}

Program::Vec4ArraySetter::Vec4ArraySetter(string name, int loc, int sz) : Setter(name, loc), size(sz) { }

void Program::Vec4ArraySetter::set(const vector<vec4>& v) {
	if (v.size() != size)
		throw runtime_error("Bad size: Got " + str(v.size()) + " but expected " + str(size));
	glUniform4fv(this->loc, size, (float*)&v[0]);
}

Program::Mat4ArraySetter::Mat4ArraySetter(string name, int loc, int sz) : Setter(name, loc), size(sz) { }

void Program::Mat4ArraySetter::set(const vector<mat4>& v) {
	if (v.size() != size)
		throw runtime_error("Bad size: Got " + str(v.size()) + " but expected " + str(size));
	glUniformMatrix4fv(this->loc, size, true, (float*)&v[0]);
}

Program::Mat4Setter::Mat4Setter(string name, int loc) : Setter(name, loc) { }

void Program::Mat4Setter::set(const mat4& v) {
	glUniformMatrix4fv(this->loc, 1, true, (float*)v._m);
}

Program::Sampler2dSetter::Sampler2dSetter(string name, int loc, int unit) : Setter(name, loc)
{
	this->unit = unit;
}

void Program::Sampler2dSetter::set(Texture* v) {
	if (!dynamic_cast<Texture2D*>(v))
		throw runtime_error("Cannot convert to Texture2D");
	v->bind(this->unit);
	glUniform1i(this->loc, this->unit);
}

Program::Sampler2dArraySetter::Sampler2dArraySetter(string name, int loc, int unit) : Setter(name, loc)
{
	this->unit = unit;
}

void Program::Sampler2dArraySetter::set(Texture* v) {
	if (!dynamic_cast<Texture2DArray*>(v))
		throw runtime_error("Cannot convert to Texture2DArray");
	v->bind(this->unit);
	glUniform1i(this->loc, this->unit);
}

Program::SamplerCubeSetter::SamplerCubeSetter(string name, int loc, int unit) : Setter(name, loc)
{
	this->unit = unit;
}

void Program::SamplerCubeSetter::set(Texture* v) {
	if (!dynamic_cast<CubeTexture*>(v))
		throw runtime_error("Texture is not a cube texture");
	v->bind(this->unit);
	glUniform1i(this->loc, this->unit);
}

Program::Program(string csfname) {
	init("", "", "", csfname, {});
}

Program::Program(string vsfname, string fsfname) {
	init(vsfname, "", fsfname, "", { "color" });
}

Program::Program(string vsfname, string gsfname, string fsfname, const vector<string>& outputs) {
	init(vsfname, gsfname, fsfname, "", outputs);
}

void Program::init(string vsfname, string gsfname, string fsfname, string csfname, const vector<string>& outputs) {

	if (csfname.length() > 0)
		is_compute_shader = true;
	else
		is_compute_shader = false;

	this->name = vsfname + " " + gsfname + " " + fsfname + " " + csfname;

	GLint tmp[1];

	GLuint vs = 0;
	if (vsfname.length() > 0)
		vs = this->make_shader(vsfname, GL_VERTEX_SHADER);
	GLuint gs = 0;
	if (gsfname.length() > 0)
		gs = this->make_shader(gsfname, GL_GEOMETRY_SHADER);
	GLuint fs = 0;
	if (fsfname.length() > 0)
		fs = this->make_shader(fsfname, GL_FRAGMENT_SHADER);
	GLuint cs = 0;
	if (csfname.length() > 0)
		cs = this->make_shader(csfname, GL_COMPUTE_SHADER);

	prog = glCreateProgram();
	if (vs)
		glAttachShader(prog, vs);
	if (gs)
		glAttachShader(prog, gs);
	if (fs)
		glAttachShader(prog, fs);
	if (cs)
		glAttachShader(prog, cs);

	glBindAttribLocation(prog, Program::POSITION_INDEX, "a_position");
	glBindAttribLocation(prog, Program::TEXCOORD_INDEX, "a_texcoord");
	glBindAttribLocation(prog, Program::NORMAL_INDEX, "a_normal");
	glBindAttribLocation(prog, Program::TANGENT_INDEX, "a_tangent");
	glBindAttribLocation(prog, Program::BONE_INDEX, "a_boneidx");

	for (unsigned i = 0; i<outputs.size(); ++i)
		glBindFragDataLocation(prog, i, outputs[i].c_str());

	glLinkProgram(prog);
	char infolog[4096];
	GLsizei isize;
	glGetProgramInfoLog(prog, sizeof(infolog), &isize, infolog);
	if (isize > 0) {
		cout << "Linking " << this->name << ":\n";
		cout << infolog;
	}

	glGetProgramiv(prog, GL_LINK_STATUS, tmp);
	if (!tmp[0])
		throw runtime_error("Could not link shaders");

	for (string x : outputs) {
		int loc = glGetFragDataLocation(prog, x.c_str());
		if (loc == -1)
			throw runtime_error("Shader " + fsfname + " does not have output " + x);
	}

	int texcounter = 0;
	glGetProgramiv(prog, GL_ACTIVE_UNIFORMS, tmp);
	GLuint numuniforms = tmp[0];
	for (GLuint i = 0; i<numuniforms; ++i) {
		GLint type_[1];
		GLint size[1];
		GLint le[1];
		char namea[256];
		glGetActiveUniformsiv(prog, 1, &i, GL_UNIFORM_TYPE, type_);
		glGetActiveUniformsiv(prog, 1, &i, GL_UNIFORM_SIZE, size);
		glGetActiveUniformName(prog, i, sizeof(namea), le, namea);
		string name = namea;
		int loc = glGetUniformLocation(prog, name.c_str());
		uninitialized.insert(name);
		if (size[0] == 1) {
			switch (type_[0]) {
			case GL_INT:
				setters[name] = new IntSetter(name, loc);
				break;
			case GL_UNSIGNED_INT:
				setters[name] = new UIntSetter(name, loc);
				break;
			case GL_FLOAT:
				setters[name] = new FloatSetter(name, loc);
				break;
			case GL_INT_VEC2:
				setters[name] = new IVec2Setter(name, loc);
				break;
			case GL_FLOAT_VEC2:
				setters[name] = new Vec2Setter(name, loc);
				break;
			case GL_FLOAT_VEC3:
				setters[name] = new Vec3Setter(name, loc);
				break;
			case GL_FLOAT_VEC4:
				setters[name] = new Vec4Setter(name, loc);
				break;
			case GL_SAMPLER_2D:
				setters[name] = new Sampler2dSetter(name, loc, texcounter);
				texcounter += 1;
				break;
			case GL_SAMPLER_2D_ARRAY:
				setters[name] = new Sampler2dArraySetter(name, loc, texcounter);
				texcounter += 1;
				break;
			case GL_SAMPLER_CUBE:
				setters[name] = new SamplerCubeSetter(name, loc, texcounter);
				texcounter += 1;
				break;
			case GL_FLOAT_MAT4:
				setters[name] = new Mat4Setter(name, loc);
				break;
			default:
				throw runtime_error(string("Don't know about type of ") + name);
			}
		}
		else {
			switch (type_[0]) {
			case GL_FLOAT:
				setters[name] = new FloatArraySetter(name, loc, size[0]);
				break;
			case GL_FLOAT_VEC2:
				setters[name] = new Vec2ArraySetter(name, loc, size[0]);
				break;
			case GL_FLOAT_VEC3:
				setters[name] = new Vec3ArraySetter(name, loc, size[0]);
				break;
			case GL_FLOAT_VEC4:
				setters[name] = new Vec4ArraySetter(name, loc, size[0]);
				break;
			case GL_FLOAT_MAT4:
				setters[name] = new Mat4ArraySetter(name, loc, size[0]);
				break;
			default:
				throw runtime_error(string("Don't know about type of ") + name);
			}
		}
	}
}

void Program::checkUninitialized() {
	for (const string& s : uninitialized) {
	  //cout << "Uninitialized uniform: " << s << "\n";
	}
}

void Program::use() {
	glUseProgram(this->prog);
	Program::active = this;
}

void Program::dispatch(int xs, int ys, int zs) {
	if (active != this)
		throw runtime_error("Cannot dispatch() a non-active program");
	if (!is_compute_shader)
		throw runtime_error("Cannot dispatch() a non-compute shader");
	glDispatchCompute(xs, ys, zs);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

GLuint Program::make_shader(string filename, GLenum shadertype) {
	ifstream in(filename.c_str());
	if (!in) {
		throw runtime_error("Cannot open file " + filename);
	}
	string shaderdata;
	getline(in, shaderdata, '\0');
	GLuint s = glCreateShader(shadertype);
	const char* x[] = { shaderdata.c_str() };
	glShaderSource(s, 1, x, NULL);
	glCompileShader(s);
	char infolog[4096];
	GLint tmp[1];
	glGetShaderInfoLog(s, sizeof(infolog), tmp, infolog);
	if (tmp[0] > 0) {
		cout << "When compiling " << filename << ":";
		cout << infolog;
	}
	glGetShaderiv(s, GL_COMPILE_STATUS, tmp);
	if (!tmp[0])
		throw runtime_error("Cannot compile " + filename);
	return s;
}
