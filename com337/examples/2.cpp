// opengl-02.c   --   keyboard handling and initial window configuration

#include <stdlib.h>
#include <stdio.h>
#include <glut.h>

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)  // exit when user hits <esc>
		exit(EXIT_SUCCESS);
	else
		printf("You pressed key %c at (%d,%d)\n", key, x, y);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(200, 126);
	glutInitWindowPosition(10, 100);
	glutCreateWindow(argv[0]);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return EXIT_SUCCESS;
}
