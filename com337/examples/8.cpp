// opengl-08.c  --  an articulated arm controlled by the keyboard

#include <stdlib.h>
#include <glut.h>

int shoulder = 0, elbow = 0, wrist = 0;

void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27: case 'q': case 'Q':
    exit (EXIT_SUCCESS);
    break;
  case 's':
    shoulder = (shoulder + 5) % 360;    
    break;
  case 'S':
    shoulder = (shoulder - 5) % 360;    
    break;
  case 'e':
    elbow = (elbow + 5) % 360;    
    break;
  case 'E':
    elbow = (elbow - 5) % 360;    
    break;
  case 'w':
	  wrist = (wrist + 5) % 360;
  break;
  case 'W':
	  wrist = (wrist - 5) % 360;
  break;
  }

  glutPostRedisplay();
}


void display (void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  glColor3f(0.0, 0.0, 1.0);

  glPushMatrix ();
	  glColor3f(0.0, 0.0, 1.0);
	  glTranslatef (-1.0, 0.0, 0.0);
	  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
	  glTranslatef (1.0, 0.0, 0.0);
		  glPushMatrix ();
			glScalef (2.0, 0.4, 1.0);
			glutSolidCube (1.0);
		  glPopMatrix ();

	  glColor3f(1.0, 0.0, 0.0);
	  glTranslatef (1.0, 0.0, 0.0);
	  glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
	  glTranslatef (1.0, 0.0, 0.0);
	  glPushMatrix ();
		glScalef (2.0, 0.4, 1.0);
		glutSolidCube (1.0);
	  glPopMatrix ();


	  glColor3f(0.0, 1.0, 0.0);
	  glTranslatef(1.0, 0.0, 0.0);
	  glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);
	  glTranslatef(1.0, 0.0, 0.0);
	  glPushMatrix();
	  glScalef(2.0, 0.4, 1.0);
	  glutSolidCube(1.0);
	  glPopMatrix();

  glPopMatrix ();


  glutSwapBuffers ();
}


void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (65.0, (GLfloat) w / (GLfloat) h, 1.0, 100);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glTranslatef (0.0, 0.0, -5.0);
}


int main (int argc, char *argv[])
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow (argv[0]);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode (GL_PROJECTION);
  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);
  glutReshapeFunc (reshape);
  glutMainLoop ();
  return EXIT_SUCCESS;
}