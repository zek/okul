// opengl-09.c  --  rendering a sphere with lighting

#include <stdlib.h>
#ifdef __APPLE__

#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif


void init (void)
{
  GLfloat mat_spec[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat mat_shiny[] = {50.0};
  GLfloat light_pos[] = {5.0, 1.0, 1.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};

  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  // GL_FLAT, GL_SMOOTH

  glMaterialfv (GL_FRONT, GL_SPECULAR, mat_spec);
  glMaterialfv (GL_FRONT, GL_SHININESS, mat_shiny);
  glLightfv (GL_LIGHT0, GL_POSITION, light_pos);
  glLightfv (GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv (GL_LIGHT0, GL_SPECULAR, white_light);

  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_DEPTH_TEST);
}


void display (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSolidSphere (1.0, 40, 16);
  glFlush ();  
}


void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27: case 'q': case 'Q':
    exit (EXIT_SUCCESS);
    break;
  }
}

void reshape (int w, int h)
{
  GLfloat fac;

  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  if (w <= h) {
    fac = (GLfloat) h / (GLfloat) w;
    glOrtho (-1.5, 1.5, -1.5 * fac, 1.5 * fac, -10.0, 10.0);
  } else {
    fac = (GLfloat) w / (GLfloat) h;
    glOrtho (-1.5, 1.5, -1.5 * fac, 1.5 * fac, -10.0, 10.0);
  }
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}


int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (400, 400);
  glutInitWindowPosition (100, 10);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);
  glutReshapeFunc (reshape);
  glutMainLoop ();
  return 0;
}