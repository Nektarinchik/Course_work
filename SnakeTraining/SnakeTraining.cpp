#include <glut.h>
#include <ctime>

#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Constants.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\GlFunctions.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZE_W, WINDOWSIZE_H);
	glutCreateWindow("SNAKE");
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}

