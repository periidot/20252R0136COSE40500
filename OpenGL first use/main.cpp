/*
 * Skeleton code for COSE436 Interactive Visualization
 * 
 * Won-Ki Jeong, wkjeong@korea.ac.kr
 */

#include <stdio.h>
#include <GL/glut.h>

void reshape(int w, int h)
{
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(0, 0, 0, 50);
	glOrtho(0, 100, 0, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}

int objc = 0;
void keyz(unsigned char key, int x, int y) {

	switch (key) {
	case 'm':
		if (objc <= 2) {
			objc++;

			if (objc > 2) {
				objc = 0;
			}
		}
		break;
	case 'M':
		if (objc <= 2) {
			objc++;
			if (objc > 2) {
				objc = 0;
			}
		}
	}
	

}


void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw something here!
	glColor3f(0, 0, 1);
	//glRectf(30, 30, 70, 70);

	switch (objc) {
	case 0:
		glutWireTeapot(10);
		glutPostRedisplay();
		break;
	case 1:
		glutWireCube(50);
		glutPostRedisplay();
	case 2:
		glutWireIcosahedron();
		glutPostRedisplay();
	}

	
	//glColor3f(1,0,1);
	//glRectf(40,40,60,60);	

    glutSwapBuffers();
}

int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Hello World");

	// register callbacks
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyz);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}