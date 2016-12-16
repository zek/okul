// opengl-04.c   --   drawing a sphere

#include <stdlib.h>
#include <glut.h>

int slices = 20, stacks = 20;
float scale = 1.0;

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')
		exit(EXIT_SUCCESS);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glutWireSphere(scale, slices, stacks);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutCreateWindow(argv[0]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return EXIT_SUCCESS;
}
