#pragma once

#include "Texture2D.h"
#include "Texture2DArray.h"
#include "math3d.h"
#include "util.h"
#include "CubeTexture.h"
#include <fstream>
#include "glfuncs.h"

using namespace std;

class Program{

public:

    static const int POSITION_INDEX = 0;
    static const int TEXCOORD_INDEX = 1;
    static const int NORMAL_INDEX = 2;
    static const int TANGENT_INDEX = 3;
    static const int BONE_INDEX = 4;
    
    static Program* active;
    
    Program(const Program&) = delete;
    
    class Setter {
    
	public:

        string name;
        int loc;

		Setter(string n, int lo);
		Setter();
        
		virtual void set(float value);
		virtual void set(const vec2& value);
		virtual void set(const ivec2& value);
		virtual void set(const vec3& value);
		virtual void set(const vec4& value);
		virtual void set(const vector<float>& value);
		virtual void set(const vector<vec2>& value);
		virtual void set(const vector<vec3>& value);
		virtual void set(const vector<vec4>& value);
		virtual void set(const vector<mat4>& value);
		virtual void set(const mat4& value);
		virtual void set(Texture* value);
    };
    
    class FloatSetter : public Setter {

    public:

		FloatSetter(string name, int loc);

		void set(float v) override;
    };
    
    class IntSetter : public Setter {

    public:

		IntSetter(string name, int loc);

		void set(float v) override;
    };

    class UIntSetter : public Setter {

    public:

		UIntSetter(string name, int loc);

		void set(float v) override;
    };

    class Vec2Setter : public Setter {

    public:

		Vec2Setter(string name, int loc);

		void set(const vec2& v) override;
    };
    
    class IVec2Setter : public Setter {

    public:

		IVec2Setter(string name, int loc);

		void set(const ivec2& v) override;
    };
    
    class Vec3Setter : public Setter {

    public:

		Vec3Setter(string name, int loc);

		void set(const vec3& v) override;
    };
    
    class Vec4Setter : public Setter {

    public:

		Vec4Setter(string name, int loc);

		void set(const vec4& v) override;
    };

    class FloatArraySetter : public Setter {

     public:

        unsigned size;

		FloatArraySetter(string name, int loc, int sz);

		void set(const vector<float>& v) override;
    };

    class Vec2ArraySetter : public Setter {

    public:

        unsigned size;

		Vec2ArraySetter(string name, int loc, int sz);

		void set(const vector<vec2>& v) override;
    };

    class Vec3ArraySetter : public Setter {

    public:

        unsigned size;

		Vec3ArraySetter(string name, int loc, int sz);

		void set(const vector<vec3>& v) override;
    };


    class Vec4ArraySetter : public Setter {

    public:

        unsigned size;

		Vec4ArraySetter(string name, int loc, int sz);

		void set(const vector<vec4>& v) override;
    };
    
    class Mat4ArraySetter : public Setter {

    public:

        unsigned size;

		Mat4ArraySetter(string name, int loc, int sz);

		void set(const vector<mat4>& v) override;
    };
    
    class Mat4Setter : public Setter {

    public:

		Mat4Setter(string name, int loc);

		void set(const mat4& v) override;
    };
    
    class Sampler2dSetter: public Setter {

    public:

        int unit;

		Sampler2dSetter(string name, int loc, int unit);

		void set(Texture* v) override;
    };

    class Sampler2dArraySetter: public Setter {

    public:

        int unit;

		Sampler2dArraySetter(string name, int loc, int unit);

		void set(Texture* v) override;
    };
    
    class SamplerCubeSetter: public Setter {

    public:

        int unit;

		SamplerCubeSetter(string name, int loc, int unit);

		void set(Texture* v) override;
    };
    
    map<string,Setter*> setters;
    GLuint prog;
    string name;
    bool is_compute_shader;
	set<string> warned;
	set<string> uninitialized;
    
	Program(string csfname);
	Program(string vsfname, string fsfname);
	Program(string vsfname, string gsfname, string fsfname, const vector<string>& outputs);

	void init(string vsfname, string gsfname, string fsfname, string csfname, const vector<string>& outputs);
  	void checkUninitialized();
	void use();
	void dispatch(int xs, int ys, int zs);
	GLuint make_shader(string filename, GLenum shadertype);

	template<typename T>
	void setUniform(string name, T value) {
		if (Program::active != this)
			throw runtime_error("Cannot set uniform on non-active program");

		uninitialized.erase(name);

		if (this->setters.find(name) != setters.end()) {
			this->setters[name]->set(value);
		}
		else {
			if (warned.find(name) == warned.end()) {
				if (this->setters.find(name + "[0]") != this->setters.end())
					throw runtime_error("It looks like you should use " + name + "[0]");
				warned.insert(name);
			}
		}
	}
};
