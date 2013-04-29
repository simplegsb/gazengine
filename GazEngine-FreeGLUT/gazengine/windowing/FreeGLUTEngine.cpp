#include <GL/freeglut.h>

#include "../input/FreeGLUTInputEvents.h"
#include "FreeGLUTEngine.h"

using namespace std;

FreeGLUTEngine::FreeGLUTEngine(const string& title, int width, int height) :
	height(height),
	width(width),
	title(title)
{
	int argc = 1;
	char* argv = new char;
	char* argvPtr(argv);

	glutInit(&argc, &argvPtr);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.data());

	glutKeyboardFunc(fireKeyboardButtonDownEvent);
	glutKeyboardUpFunc(fireKeyboardButtonUpEvent);
	glutMotionFunc(fireMouseMoveEvent);
	glutMouseFunc(fireMouseButtonEvent);
	glutPassiveMotionFunc(fireMouseMoveEvent);
	glutSpecialFunc(fireKeyboardSpecialButtonDownEvent);
	glutSpecialUpFunc(fireKeyboardSpecialButtonUpEvent);

	delete argv;
}

void FreeGLUTEngine::addEntity(Entity*)
{
}

void FreeGLUTEngine::advance()
{
	glutMainLoopEvent();
	glutSwapBuffers();
}

void FreeGLUTEngine::destroy()
{
}

int FreeGLUTEngine::getHeight() const
{
	return height;
}

int FreeGLUTEngine::getWidth() const
{
	return width;
}

void FreeGLUTEngine::init()
{
}

void FreeGLUTEngine::removeEntity(const Entity&)
{
}
