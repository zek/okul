// opengl-05.c  --  looking around the teapot

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

float distance = 5.0, angle = 0.0;

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')
		exit(EXIT_SUCCESS);
}

void idle(void)
{
	float xc, zc;
	angle = angle + 0.05;
	if (angle > 360.0) 
		angle = 0.0;
	xc = distance * cos(angle / 180.0*M_PI);
	zc = distance * sin(angle / 180.0*M_PI);
	glLoadIdentity();
	gluLookAt(xc, 0.0, zc, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(1);
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow(argv[0]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 3.0, 7.0);
	glMatrixMode(GL_MODELVIEW);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return EXIT_SUCCESS;
}
