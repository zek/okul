// opengl-13.c  --  texture mapping

#include <stdlib.h>
#include <glut.h>

#define WIDTH 64
#define HEIGHT 64

GLubyte image[HEIGHT][WIDTH][4];
GLuint texname;

void keyboard (unsigned char key, int x, int y)
{
  if (key == 27 || key == 'q' || key == 'Q')
    exit (EXIT_SUCCESS);
}

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 30.0);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glTranslatef (0.0, 0.0, -3.6);
}

void display (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable (GL_TEXTURE_2D);
  glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture (GL_TEXTURE_2D, texname);
  glBegin (GL_QUADS);
  glTexCoord2f (0.0, 0.0); glVertex3f (-2.0, -1.0, 0.0);
  glTexCoord2f (0.0, 1.0); glVertex3f (-2.0,  1.0, 0.0);
  glTexCoord2f (1.0, 1.0); glVertex3f ( 0.0,  1.0, 0.0);
  glTexCoord2f (1.0, 0.0); glVertex3f ( 0.0, -1.0, 0.0);

  glTexCoord2f (0.0, 0.0); glVertex3f (1.0, -1.0, 0.0);
  glTexCoord2f (0.0, 1.0); glVertex3f (1.0,  1.0, 0.0);
  glTexCoord2f (1.0, 1.0); glVertex3f (2.41421,  1.0, -1.41421);
  glTexCoord2f (1.0, 0.0); glVertex3f (2.41421, -1.0, -1.41421);
  glEnd ();
  glFlush ();
  glDisable (GL_TEXTURE_2D);
}

void init (void)
{
  int i, j;

  for (i = 0; i < HEIGHT; i++) {
    for ( j = 0; j < WIDTH; j++) {
      image[i][j][0] = image[i][j][1] = image[i][j][2] =
        (GLubyte) (((i & 8) == 0) ^ ((j & 8) == 0)) * 255;
      image[i][j][3] = 255;
    }
  }
  glClearColor (0.0, 1.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
  glEnable (GL_DEPTH_TEST);
  glPixelStorei (GL_PACK_ALIGNMENT, 1);
  glGenTextures (1, &texname);
  glBindTexture (GL_TEXTURE_2D, texname);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}

int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);
  glutReshapeFunc (reshape);
  glutMainLoop ();
  return EXIT_SUCCESS;
}