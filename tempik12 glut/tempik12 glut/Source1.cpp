#include <iostream>
#include <gl\glut.h>
#include <Windows.h>


void display()
{
	int x=0, y=0, x1=0, y1=0;
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int a(0); a < 500000; a++)
	{
		glBegin(GL_LINES);
		x = rand() % 500;
		y = rand() % 500;
		x1 = rand() % 500;
		y1 = rand() % 500;
		glColor3f((x)/500.0, (y)/500.0, (x1)/500.0);
		glVertex2f(x, y);
		glVertex2f(x1, y1);
		glEnd();
		glFlush();
		//Sleep(100);
	}
}


int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("GL");
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 500, 0, 500, 0, 1);
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}

