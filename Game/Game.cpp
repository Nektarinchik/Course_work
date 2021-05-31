#include <glut.h>

#include "Constants.h"
#include "Snake.h"
#include "Fruit.h"
#include "GlFunctions.h"

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZE_W, WINDOWSIZE_H);
	glutCreateWindow("SNAKE");
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutSpecialFunc(input);
	glutMainLoop();
	return 0;
}

