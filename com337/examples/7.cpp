// opengl-07.c  --  better keyboard and mouse interaction around a cube
//                  with hidden surface removal
//                          E                  H
//                         _*----------------_*
//                       _- :              _- |
//                     _-   :           _-    |
//                  A*----------------*D      |
//                   |      :         |       |
//                   |      :     *0  |       |
//                   |      :         |       |
//                   |     F*- - - - -|- - -_-*G
//                   |   .            |   _-
//                   | .              | _-
//                  B*----------------*C

#define A glVertex3f (-0.5,  0.5, -0.5)
#define B glVertex3f (-0.5, -0.5, -0.5)
#define C glVertex3f ( 0.5, -0.5, -0.5)
#define D glVertex3f ( 0.5,  0.5, -0.5)
#define E glVertex3f (-0.5,  0.5,  0.5)
#define F glVertex3f (-0.5, -0.5,  0.5)
#define G glVertex3f ( 0.5, -0.5,  0.5)
#define H glVertex3f ( 0.5,  0.5,  0.5)

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <glut.h>

float distance = 5.0;
int longitude = 0, latitude = 0, ainc = 5;
int lastx = -1, lasty = -1;

void display (void)
{
  float xc, yc, zc;
  int type = GL_POLYGON;   // or GL_LINE_LOOP
  xc = distance * cos (latitude /180.0*M_PI) * cos (longitude/180.0*M_PI);
  yc = distance * sin (latitude /180.0*M_PI);
  zc = distance * cos (latitude /180.0*M_PI) * sin (longitude/180.0*M_PI);
  glLoadIdentity ();
  gluLookAt (xc, yc, zc,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Sides of the cube as loops or polygons, in anti-clockwise order.
  glColor3f (1.0, 0.0, 0.0);
  glBegin (type);  A; B; C; D;  glEnd();  // front
  glColor3f (0.0, 1.0, 0.0);
  glBegin (type);  H; E; F; G;  glEnd();  // back
  glColor3f (0.0, 0.0, 1.0);
  glBegin (type);  B; C; G; F;  glEnd();  // bottom
  glColor3f (1.0, 0.0, 1.0);
  glBegin (type);  A; D; H; E;  glEnd();  // top
  glColor3f (0.0, 1.0, 1.0);
  glBegin (type);  A; E; F; B;  glEnd();  // left
  glColor3f (1.0, 1.0, 0.0);
  glBegin (type);  D; C; G; H;  glEnd();  // right
  glutSwapBuffers ();
}

void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27: case 'q': case 'Q':
    exit (EXIT_SUCCESS);
    break;
  }
}

void special (int key, int x, int y)
{
  switch (key) {
  case GLUT_KEY_UP:
    distance *= 1.1;
    break;
  case GLUT_KEY_DOWN:
    distance /= 1.1;
    break;
  }
  glutPostRedisplay ();
}

void click (int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    lastx = x;
    lasty = y;
  }
}

void mouse (int x, int y)
{
  if (x > lastx) {
    longitude = (longitude + ainc) % 360;
  } else if (x < lastx) {
    longitude = (longitude - ainc) % 360;
  }
  if (y > lasty) {
    latitude = (latitude + ainc) % 360;
  } else if (y < lasty) {
    latitude = (latitude - ainc) % 360;
  }
  lastx = x;
  lasty = y;
  glutPostRedisplay ();
}

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glTranslatef (0.0, 0.0, -5.0);
}


int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow (argv[0]);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(50.0, 1.0, 3.0, 7.0);
  glMatrixMode (GL_MODELVIEW);
  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);
  glutSpecialFunc (special);
  glutMouseFunc (click);
  glutMotionFunc (mouse);
  glutReshapeFunc (reshape);
  glEnable (GL_DEPTH_TEST);
  glutMainLoop ();
  return EXIT_SUCCESS;
}