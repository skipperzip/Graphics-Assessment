
#include "glincl.h"
#include "graphics\RenderObject.h"
#include "graphics\Draw.h"
#include <glm/gtc/type_ptr.hpp>

void s0_draw(const Framebuffer & f, const Shader & s, const Geometry & g)
{
	//things to use for draw
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	//area of framebuffer being drawn to
	glViewport(0, 0, f.width, f.height);

	//DRAW THINGS
	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);

	//unbind things (optional?)
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);

}

void clearFrameBuffer(const Framebuffer & f)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void clearFrameBuffer(const Framebuffer & f, bool color, bool depth)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glClear(GL_COLOR_BUFFER_BIT * color | GL_DEPTH_BUFFER_BIT * depth);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setUniform(const Shader & shader, int location, float value)
{
	glProgramUniform1f(shader.handle, location, value);
}

void setUniform(const Shader & shader, int location, int value)
{
	glProgramUniform1i(shader.handle, location, value);
}

void setUniform(const Shader & shader, int location, double value)
{
	glProgramUniform1d(shader.handle, location, value);
}

void setUniform(const Shader & s, int location, const Texture & value, unsigned slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);

	glProgramUniform1i(s.handle, location, slot);
}

void setFlags(int flags)
{

	if (flags & RenderFlag::DEPTH) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	if (flags & RenderFlag::ADDITIVE)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);	//https://i.stack.imgur.com/22m2l.jpg
	}
	else
	{
		glDisable(GL_BLEND);
	}

}

namespace __internal 
{
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, float val)
	{
		glProgramUniform1f(s.handle, loc_io++, val);
	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, int val)
	{
		glProgramUniform1i(s.handle, loc_io++, val);
	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Texture & val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_2D, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, int r, int g, int b)
	{
		glProgramUniform1i(s.handle, loc_io++, r);
		glProgramUniform1i(s.handle, loc_io++, g);
		glProgramUniform1i(s.handle, loc_io++, b);
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io,  const glm::vec3 &val)
	{
		glProgramUniform3fv(s.handle, loc_io++, 1, glm::value_ptr(val));
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec4 &val)
	{
		glProgramUniform4fv(s.handle, loc_io++, 1, glm::value_ptr(val));
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::mat3 &val)
	{
		glProgramUniformMatrix3fv(s.handle, loc_io++, 1, 0, glm::value_ptr(val));
	}
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::mat4 &val)
	{
		glProgramUniformMatrix4fv(s.handle, loc_io++, 1, 0, glm::value_ptr(val));
	}
}


