#pragma once

struct Geometry;
struct Shader;
struct Framebuffer;

void s0_draw(const Framebuffer &f, const Shader &s, const Geometry &g);


void clearFrameBuffer(const Framebuffer &f, bool color = true, bool depth = true);

void setUniform(const Shader &shader, int location, float value);
void setUniform(const Shader &shader, int location, int value);
void setUniform(const Shader &shader, int location, double value);

void setUniform(const Shader &s, int location, const Texture &value, unsigned slot);

namespace __internal
{
	//set SOME uniforms
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);

	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat3 &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val);

}


//templates and variadics!
//you can put any number of things into a variadic.
template<typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val, U &&... uniforms)
{

	__internal::t_setUniform(s, loc_io, tex_io, val);

	//T parameter isn't part of this call
	//it instead is stealing a value from the uniforms variadic
	setUniforms(s, loc_io, tex_io, uniforms...);

	//so it goes through each member of U at a time until it's gone.
}


//This is the last thing to get called.  It is the final base case for when
//there is only one value of U left.
template<typename T>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
}

//Powers of Two
enum RenderFlag{
	NONE = 0,
	DEPTH = 1,
	ADDITIVE = 2,
	//NEXT = 4
};

void setFlags(int flags);