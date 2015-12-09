#include <gl\glut.h>
void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glEnd();
        glColor3f(0.0,0.0,0.0);
        glVertex2f(100, 100.0);
        glVertex2f(150, 150.0);
        glFlush();
}

int main(int argc, char **argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 740);
        glutCreateWindow("Hello world!");
        glClearColor(1.0,1.0,1.0,1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 240.0, 0.0, 240.0, -1.0, 1.0);
        glutDisplayFunc(display);
        glutMainLoop();

        return 0;
}

#include <gl\glut.h>

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(0,0,1);
        glutSolidSphere(0.5,45,15);
        glFlush();
}

int main(int argc, char **argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(100, 143);
        glutCreateWindow("Круг");
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
        glutDisplayFunc(display);
        glutMainLoop();
}
