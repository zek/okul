#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES

#include <cmath>

#ifdef __APPLE__

#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif
#define GLUT_KEY_ESC             27

using namespace std;


float anglecamera = 0.0;
float angleday = 0;
bool polygon_mode = false;

const int MAPZ = 17;
const int MAPX = 21;

const int distance_cam = MAPX * 20;
const int distance_light = MAPX * 20;

int map[MAPZ][MAPX] = {
        {14, 25, 45, 55, 68, 70, 84,  91,  97,  101, 105, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110},
        {5,  18, 43, 62, 73, 82, 88,  94,  99,  102, 105, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110},
        {5,  18, 38, 56, 69, 77, 86,  94,  99,  103, 106, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110},
        {5,  9,  31, 48, 60, 71, 81,  87,  95,  101, 106, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110},
        {5,  5,  18, 37, 49, 56, 62,  81,  91,  94,  101, 105, 105, 105, 110, 110, 110, 110, 110, 110, 110},
        {5,  5,  12, 23, 34, 40, 53,  66,  77,  82,  97,  103, 105, 105, 109, 110, 110, 110, 110, 115, 115},
        {4,  5,  8,  15, 20, 24, 35,  39,  40,  77,  92,  101, 104, 104, 105, 110, 110, 110, 115, 115, 115},
        {5,  7,  22, 36, 46, 48, 48,  44,  50,  58,  80,  96,  96,  97,  106, 110, 110, 115, 115, 115, 115},
        {4,  15, 31, 46, 61, 68, 69,  63,  53,  50,  67,  82,  84,  103, 108, 110, 110, 115, 115, 115, 115},
        {4,  12, 31, 46, 64, 78, 82,  80,  69,  54,  73,  71,  92,  105, 108, 110, 110, 115, 115, 115, 115},
        {6,  26, 35, 45, 63, 75, 84,  87,  84,  74,  77,  80,  96,  103, 108, 110, 110, 110, 115, 115, 115},
        {21, 30, 46, 57, 64, 76, 85,  92,  92,  87,  79,  80,  86,  102, 106, 110, 105, 110, 115, 115, 115},
        {27, 40, 48, 62, 75, 84, 92,  96,  97,  94,  88,  80,  80,  91,  104, 105, 105, 105, 110, 115, 115},
        {33, 43, 55, 65, 75, 87, 96,  101, 101, 101, 97,  92,  80,  80,  98,  105, 105, 105, 105, 110, 115},
        {45, 50, 58, 68, 80, 91, 99,  102, 105, 105, 105, 99,  90,  80,  80,  97,  105, 105, 105, 110, 100},
        {50, 60, 65, 71, 84, 95, 101, 105, 105, 107, 107, 106, 102, 101, 92,  80,  98,  104, 105, 100, 100},
        {60, 70, 76, 83, 88, 96, 103, 106, 107, 108, 110, 109, 108, 108, 106, 101, 90,  100, 100, 100, 100},
};

void idle(void) {
    if (angleday >= 180) {
        angleday = 0;
    } else {
        angleday += 0.2;
    }
    glutPostRedisplay();
}


void display() {

    double xc, zc, yc;
    double y, y1, y2, y3;

    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_spec[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shiny[] = {50.0};

    xc = distance_cam * cos(anglecamera / 180.0 * M_PI);
    zc = distance_cam * sin(anglecamera / 180.0 * M_PI);

    glLoadIdentity(); // reset matrix
    gluLookAt(xc, 370, zc, 0, 0, 0, 0.0, 1.0, 0.0);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat pos[] = {MAPX * 10, 0.0, MAPZ * 10, 1.0};

    glPushMatrix();

    glPushMatrix();
    glRotated((GLdouble) angleday, 1.0f, 1.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    /*glTranslated(MAPZ * 10, 0, MAPZ * 10);
    glDisable(GL_LIGHTING);
        glColor3f(0.0, 1.0, 1.0);
        glutSolidCube(1);
    glEnable(GL_LIGHTING);
     */
    glPopMatrix();
    //glTranslatef(0.0, -200.0f, 0);


    // switch between polygon modes
    if (polygon_mode) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    for (int z = 0; z < MAPZ - 1; z++) {
        for (int x = 0; x < MAPX - 1; x++) {

            /*
             * Draw Upper side of triangles
             */

            y1 = map[z][x];
            y2 = map[z][x + 1];
            y3 = map[z + 1][x];
            y = (y1 + y2 + y3) / 3;
            glColor3f(y >= 50, y < 80, 0.0);


            glBegin(GL_TRIANGLE_STRIP);

            glColor3f(y1 >= 50, y1 < 80, 0.0);
            glVertex3f(x * 20 - MAPX * 10, y1, z * 20 - MAPZ * 10);

            glColor3f(y2 >= 50, y2 < 80, 0.0);
            glVertex3f((x + 1) * 20 - MAPX * 10, y2, z * 20 - MAPZ * 10);

            glColor3f(y3 >= 50, y3 < 80, 0.0);
            glVertex3f(x * 20 - MAPX * 10, y3, (z + 1) * 20 - MAPZ * 10);
            glEnd();

            /*
             * Draw Lower side of triangles
             */

            y1 = map[z + 1][x];
            y2 = map[z][x + 1];
            y3 = map[z + 1][x + 1];
            y = (y1 + y2 + y3) / 3;

            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(y1 >= 50, y1 < 80, 0.0);
            glVertex3f(x * 20 - MAPX * 10, y1, (z + 1) * 20 - MAPZ * 10);

            glColor3f(y2 >= 50, y2 < 80, 0.0);
            glVertex3f((x + 1) * 20 - MAPX * 10, y2, z * 20 - MAPZ * 10);

            glColor3f(y3 >= 50, y3 < 80, 0.0);
            glVertex3f((x + 1) * 20 - MAPX * 10, y3, (z + 1) * 20 - MAPZ * 10);
            glEnd();
        }
    }
    glPopMatrix();
    glFlush();
    glutSwapBuffers(); // swap buffers

}

/*
 * Sol veya sağ tuşuna basınca kamerayı hareket ettir.
 */
void special(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        anglecamera = anglecamera + 5;
        if (anglecamera > 360.0)
            anglecamera = 0.0;
    } else if (key == GLUT_KEY_RIGHT) {
        anglecamera = anglecamera - 5;
        if (anglecamera > 360.0)
            anglecamera = 0.0;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == GLUT_KEY_ESC) { // Programı sonlandır
        exit(EXIT_SUCCESS);
    } else if (key == 'h' || key == 'H') { // Polygon modunu değiştir.
        polygon_mode = !polygon_mode;
    }
    glutPostRedisplay();
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST); // yumuşatmayı aktif et
    glEnable(GL_LIGHTING); // ışıklandırmayı aktif et
    glEnable(GL_LIGHT0); // light0 ı aktif et
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL); // renklendirmeyi aktif et
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/*
 * Pencere yeniden boyutlandırıldığında viewport ve perspektifi ayarla.
 */
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (double) w / (double) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    initGL();
    glMatrixMode(GL_PROJECTION);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;

}