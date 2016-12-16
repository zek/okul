// opengl-11.c  --  moving a light source with modelling transformations

#include <stdlib.h>
#ifdef __APPLE__

#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif

int spin = 0;

void keyboard (unsigned char key, int x, int y)
{
  if (key == 27 || key == 'q' || key == 'Q')
    exit (EXIT_SUCCESS);
  else if (key == 's' || key == 'S') {
    spin = (spin + 5) % 360;
    glutPostRedisplay ();
  }
}

void display (void)
{
  GLfloat pos[] = {0.0, 0.0, 500, 1.0};

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix ();
	  glTranslatef (0.0, 0.0, -5.0);

	  glPushMatrix ();
		  glRotated ((GLdouble) spin, 1.0, 0.0, 0.0);
		  glLightfv (GL_LIGHT0, GL_POSITION, pos);

		  glTranslated (0.0, 0.0, 1.5);
		  glDisable (GL_LIGHTING);
		  glColor3f (0.0, 1.0, 1.0);
		  glutSolidCube (0.5);
		  glEnable (GL_LIGHTING);
	  glPopMatrix ();

	  glutSolidTorus (0.275, 0.85, 30, 60);
  glPopMatrix ();
  glFlush ();
}

void init (void)
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_DEPTH_TEST);
}

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (400, 400);
  glutInitWindowPosition (10, 10);
  glutCreateWindow (argv[0]);
  init ();
  glutKeyboardFunc (keyboard);
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutMainLoop ();
  return EXIT_SUCCESS;
}