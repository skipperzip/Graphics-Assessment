#include "..\include\graphics\Context.h"

#include "glincl.h"

//wtf is this
#ifdef _DEBUG
#include <iostream>
void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	std::cerr << message << std::endl;
}

#endif // _DEBUG

bool Context::init(size_t width, size_t height, const char * title)
{
	glfwInit();

	handle = glfwCreateWindow(width, height, title, 0, 0);
	glfwMakeContextCurrent(handle);

	glewExperimental = true;
	glewInit();

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	
	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif // DEBUG

	return true;
}

bool Context::step()
{
	glfwPollEvents();
	glfwSwapBuffers(handle);

	return true;
}

bool Context::term()
{
	glfwTerminate();
	handle = nullptr;

	return true;
}

bool Context::getKey(int key)
{
	return glfwGetKey(handle, key);
}

bool Context::getMouseButton(int button)
{
	return glfwGetMouseButton(handle, button);
}

void Context::getMousePosition(double & x_out, double & y_out)
{
	glfwGetCursorPos(handle, &x_out, &y_out);
}

double Context::getTime()
{
	return glfwGetTime();
}

//more stuff

//void Context::setTime(double time)
//{
//	glfwSetTime(time);
//}
//
//uint64_t Context::getTimerValue()
//{
//	return glfwGetTimerValue();
//}
//
//uint64_t Context::getTimerFrequency()
//{
//	return glfwGetTimerFrequency();
//}
//
//int Context::getInputMode(int mode)
//{
//	return glfwGetInputMode(handle, mode);
//}
//
//void Context::setInputMode(int mode, int value)
//{
//	glfwSetInputMode(handle, mode, value);
//}
//
////const char * Context::getKeyName(int key, int scancode)
////{
////	return glfwGetKeyName(key, scancode);
////}
//
//void Context::setCursorPos(double xpos, double ypos)
//{
//	glfwSetCursorPos(handle, xpos, ypos);
//}
//
////GLFWcursor * Context::createCursor(const GLFWimage * img, int xhot, int yhot)
////{
////	return nullptr;
////}
////
////GLFWcursor * Context::createStandardCursor(int shape)
////{
////	return glfwCreateStandardCursor(shape);
////}
//
////void Context::destroyCursor(GLFWcursor * cursor)
////{
////	glfwDestroyCursor(cursor);
////}
////
////void Context::setCursor(GLFWcursor * cursor)
////{
////	glfwSetCursor(handle, cursor);
////}
//
//GLFWkeyfun Context::setKeyCallback(GLFWkeyfun cbfun)
//{
//	return glfwSetKeyCallback(handle, cbfun);
//}
//
//GLFWcharfun Context::setCharCallback(GLFWcharfun cbfun)
//{
//	return glfwSetCharCallback(handle, cbfun);
//}
//
//GLFWcharmodsfun Context::setCharModsCallback(GLFWcharmodsfun cbfun)
//{
//	return glfwSetCharModsCallback(handle, cbfun);
//}
//
//GLFWmousebuttonfun Context::setMouseButtonCallback(GLFWmousebuttonfun cbfun)
//{
//	return glfwSetMouseButtonCallback(handle, cbfun);
//}
//
//GLFWcursorposfun Context::setCursorPosCallback(GLFWcursorposfun cbfun)
//{
//	return glfwSetCursorPosCallback(handle, cbfun);
//}
//
//GLFWcursorenterfun Context::setCursorEnterCallback(GLFWcursorenterfun cbfun)
//{
//	return glfwSetCursorEnterCallback(handle, cbfun);
//}
//
//GLFWscrollfun Context::setScrollCallback(GLFWscrollfun cbfun)
//{
//	return glfwSetScrollCallback(handle, cbfun);
//}
//
//GLFWdropfun Context::setDropCallback(GLFWdropfun cbfun)
//{
//	return glfwSetDropCallback(handle, cbfun);
//}
//
//bool Context::joystickPresent(int joy)
//{
//	return glfwJoystickPresent(joy);
//}
//
////const float * Context::getJoystickAxes(int joy, int * count)
////{
////	return glfwGetJoystickAxes(joy, count);
////}
//
////const unsigned char * Context::getJoystickButtons(int joy, int * count)
////{
////	return glfwGetJoystickButtons(joy, count);
////}
//
////const char * Context::getJoystickName(int joy)
////{
////	return glfwGetJoystickName(joy);
////}
//
//GLFWjoystickfun Context::setJoystickCallback(GLFWjoystickfun cbfun)
//{
//	return glfwSetJoystickCallback(cbfun);
//}
//
//void Context::setClipboardString(const char * string)
//{
//	glfwSetClipboardString(handle, string);
//}
//
////const char * Context::getClipboardString()
////{
////	return glfwGetClipboardString(handle);
////}
