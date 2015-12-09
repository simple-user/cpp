#include <iostream>
#include <gl\glut.h>
#include <cmath>
const int COUNT = 200;
int r()
{
	
	int res = 0;
	for (int a(0); a < 200; a++)
		res += rand() % 2;

	return res;
}


void display()
{
	int arr[COUNT + 1] = {};

	for (int a(0); a < 100000; a++)
	{
		arr[r()]++;
	}

	int max = 0;
	for (auto a : arr)
	{
		if (max < a)
			max = a;
	}
	std::cout << max << std::endl;;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int a(0); a < 200; a++)
		glVertex2f(a, arr[a]*200/max);
	glEnd();
	glFlush();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 500);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Hello world!");
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200, -10, 200, -1.0, 1.0);
	glutDisplayFunc(display);
	glutMainLoop();



	return 0;
	

}


