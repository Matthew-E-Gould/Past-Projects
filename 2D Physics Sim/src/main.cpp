#include <gl/glut.h>

#include "app.h"
extern Application* getApplication();
Application* app;


void display(void)
{
	app->display();
}

// creates the window for the application to run in
void createWindow(const char* title, int h, int w)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);

}

// sets up how time will work and be used
void TimerFunc(int value)
{
	app->update();
	float  timeinterval = app->getTimeinterval();
	glutTimerFunc(timeinterval, TimerFunc, 1);
}

// allows resize of window
void resize(int width, int height)
{
	app->resize(width, height);
}

// setup of the application
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	app = getApplication();
	float  timeinterval = 10;// default: 10
	app->setTimeinterval(timeinterval);
	createWindow("Blob Demo - 15065456", app->getheight(), app->getwidth());
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(timeinterval, TimerFunc, 1);
	app->initGraphics();
	glutMainLoop();
	delete app;
	return 0;
}