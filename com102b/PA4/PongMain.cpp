#include <time.h>
#include <GL/glut.h>   // also included gl.h, glu.h

#include "Ball.h"
#include "Racket.h"


#define BALL_COUNT 3
#define WINDOWX 400
#define WINDOWY 400

int g_racketsize;
int g_ballsize;

float g_lineThickness;
float g_gameBase;
Vector2D g_racketOffset;

float g_windowWidth = WINDOWX;
float g_windowHeight = WINDOWY;


Ball	g_ballList[BALL_COUNT];
Racket	g_racket;


//------------------------------------

void Initialize()
{
	srand ( time(NULL) );
	// some display parameters
	g_gameBase = 10.0f;
	g_racketOffset = Vector2D(0,0);
	g_racketsize = 100.0f;
	// racket related
	g_lineThickness = 4.0f;
	g_racket.setSize(g_racketsize);
	Vector2D p = Vector2D(WINDOWX/2-g_racket.getSize()/2,g_gameBase);
	g_racket.setPosition(p);
	
	// ball related
	g_ballsize = 10.0f;
	for (size_t i= 0; i<BALL_COUNT; i++)
	{
		float x = rand()%10/10.0f;
		float y = rand()%10/10.0f;
		
		int dx = rand()%2;
		int dy = rand()%2;

		x *= dx?1:-1;
		y *= dy?1:-1;
		Vector2D d = Vector2D(x,y);
		float R = rand()%100/100.0f;
		float G = rand()%100/100.0f;
		float B = rand()%100/100.0f;
		g_ballList[i].setRadious(g_ballsize);
		g_ballList[i].setPosition(Vector2D(g_windowWidth/2+i,g_windowHeight/2+i));
		g_ballList[i].setDirection(d);
		g_ballList[i].setVelocity(0.3f);
		g_ballList[i].setColor(R,G,B);
	}
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
}
//-------------------------------------
void updateObjects()
{
	// update racket position
	Vector2D newpos = g_racket.getPosition()+g_racketOffset;

	if(newpos.x<0)
		newpos.x = 0;
	if(newpos.x+g_racket.getSize()>g_windowWidth)
		newpos.x = g_windowWidth-g_racket.getSize();

	g_racket.setPosition(newpos);


	for (size_t i= 0; i<BALL_COUNT; i++)
	{
	
		// set ball position
		g_ballList[i].updatePosition();
		Vector2D currpos = g_ballList[i].getPosition();
		Vector2D currdir = g_ballList[i].getDirection();
		if(currpos.x<0)
		{
			currpos.x=0;
			currdir.x*=-1;
		}
		else if(currpos.x+g_ballList[i].getRadious()>g_windowWidth)
		{
			currpos.x=g_windowWidth-g_ballList[i].getRadious();
			currdir.x*=-1;
		}

		if(currpos.y<g_gameBase)
		{
			
			float minpos = g_racket.getPosition().x;
			float maxpos = g_racket.getPosition().x+g_racket.getSize();
			if(currpos.x>=minpos && currpos.x<=maxpos)
				currdir.y *= -1;
			else // REAL termination point, but ignore it for a while..
				g_ballList[i].setVelocity(0);
		}
		if(currpos.y<0)
		{
			currpos.y=0;
			currdir.y*=-1;
		}


		if(currpos.y+g_ballList[i].getRadious()>g_windowHeight)
		{
			currpos.y=g_windowHeight-g_ballList[i].getRadious();
			currdir.y*=-1;
		}

		g_ballList[i].setPosition(currpos);
		g_ballList[i].setDirection(currdir);
	}
}

//------------------------------------
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w<=h)
	{
		g_windowHeight = WINDOWY*h/w;
		g_windowWidth = WINDOWX;
	}
	else
	{
		g_windowHeight = WINDOWY;
		g_windowWidth = WINDOWX*w/h;
	}

	glOrtho(0.0f, g_windowWidth, 0.0f, g_windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//------------------------------------
void processNormalKeys(unsigned char key, int x, int y) 
{

	if (key == 'q')
		exit(0);
	if(key=='r')
		Initialize();
}
//------------------------------------
void processSpecialKeys(int key, int x, int y) 
{

	switch(key) {
		case GLUT_KEY_LEFT :
			g_racketOffset.x = -0.2f;
			break;
		case GLUT_KEY_RIGHT :
			g_racketOffset.x = 0.2;
			break;
		case GLUT_KEY_UP:
			for (size_t i= 0; i<BALL_COUNT; i++)
			{
				g_ballList[i].setRadious(g_ballList[i].getRadious()+0.5f);
			}
			break;
		case GLUT_KEY_DOWN:
			for (size_t i= 0; i<BALL_COUNT; i++)
			{
				g_ballList[i].setRadious(g_ballList[i].getRadious()-0.5f);
			}
			break;
	}

	
}

//-------------------------------------
void display() {

	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer

	updateObjects();

	Vector2D pos = g_racket.getPosition();
	unsigned int rsize = g_racket.getSize();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//render racket
	glLineWidth(g_lineThickness);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x+rsize, pos.y);
	glEnd();

	

	for (size_t i= 0; i<BALL_COUNT; i++)
	{
		pos = g_ballList[i].getPosition();
		rsize = g_ballList[i].getRadious();
		
		// render ball		
		glColor3f(g_ballList[i].getRed(),g_ballList[i].getGreen(),g_ballList[i].getBlue());	
		glBegin(GL_QUADS);
		glVertex2f(pos.x, pos.y);
		glVertex2f(pos.x+rsize, pos.y);
		glVertex2f(pos.x+rsize, pos.y+rsize);
		glVertex2f(pos.x, pos.y+rsize);
		glEnd();
	}

	glutSwapBuffers();
}
//------------------------------------
int main(int argc, char* argv[])
{	

	glutInit(&argc, argv);          // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WINDOWX, WINDOWY);
	
	

	glutCreateWindow("COM102B - Pong Game");  
	

	// Register callback handler for window re-paint
	glutDisplayFunc(display);       
	glutReshapeFunc(ChangeSize);

	// here is the idle func registration
	glutIdleFunc(display);

	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	Initialize();

	
	glutMainLoop();                 // Enter infinitely event-processing loop

	return 0;
}
