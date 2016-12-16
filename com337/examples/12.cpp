// opengl-12.c  --  displaying image data and text

#include <stdlib.h>
#include <glut.h>

#define WIDTH 64
#define HEIGHT 64

unsigned char image[WIDTH][HEIGHT][3];
char string[] = "Press <esc>";

void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27: case 'q': case 'Q':
    exit (EXIT_SUCCESS);
    break;
  }
}

void reshape (int width, int height)
{
  glViewport (0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0.0, (GLfloat) width, 0.0, (GLfloat) height, -1.0, 1.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

void display (void)
{
  char *c;

  glClear (GL_COLOR_BUFFER_BIT);
  glRasterPos2f (16.0, 16.0);
  glDrawPixels (WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, image);
  glColor3f (0.0, 1.0, 0.0);
  glRasterPos2f (16.0, 96.0);
  for (c = string; *c; c++) {
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, *c);
  }
  glFlush ();
}

void init (void)
{
  int i, j;

  for (j = 0; j < WIDTH; j++) {
    for (i = 0; i < HEIGHT; i++) {
      image[j][i][0] = image[j][i][1] = image[j][i][2] =
	(((i & 8) == 0) ^ ((j & 8) == 0)) * 255;
    }
  }
}

int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  init ();
  glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize (128, 128);
  glutCreateWindow (argv[0]);
  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);
  glutReshapeFunc (reshape);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
  glutMainLoop ();
  return EXIT_SUCCESS;
}