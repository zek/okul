// opengl-01.c   --   first example of an OpenGL program

#include <stdlib.h>
#include <glut.h>

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();
	return EXIT_SUCCESS;
}
