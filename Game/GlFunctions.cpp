#include <glut.h>
#include <cstdlib>

#include "Constants.h"
#include "GlFunctions.h"
#include "Directions.h"
#include "Board.h"

Board* board = new Board();

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawSnake();
	logic();
	drawFruit();
	glutSwapBuffers();
	if (board->GetSnake()->GetGameState()) {
		exit(0);
	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.5, WINDOWSIZE_W / PIXELSIZE, -0.5, WINDOWSIZE_H / PIXELSIZE);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

void drawSnake()
{
	for (int i = board->GetSnake()->GetSnakeLength() - 1; i > 0; --i) {
		board->GetSnake()->SetPartOfTailX(i, board->GetSnake()->GetPartOfTailX(i - 1));
		board->GetSnake()->SetPartOfTailY(i, board->GetSnake()->GetPartOfTailY(i - 1));
	}
	switch (board->GetSnake()->GetDirection())
	{
	case sDirection::UP:
		board->GetSnake()->SetHeadY(board->GetSnake()->GetHeadY() + 1);
		break;
	case sDirection::DOWN:
		board->GetSnake()->SetHeadY(board->GetSnake()->GetHeadY() - 1);
		break;
	case sDirection::RIGHT:
		board->GetSnake()->SetHeadX(board->GetSnake()->GetHeadX() + 1);
		break;
	case sDirection::LEFT:
		board->GetSnake()->SetHeadX(board->GetSnake()->GetHeadX() - 1);
		break;
	case sDirection::STOP:
		break;
	}

	glPointSize(PIXELSIZE);

	glBegin(GL_POINTS);

	glColor3f(0, 1, 0);

	for (int i = 0; i < board->GetSnake()->GetSnakeLength(); ++i) {
		glVertex2i(board->GetSnake()->GetPartOfTailX(i), board->GetSnake()->GetPartOfTailY(i));
	}

	glEnd();
}

void logic()
{
	if (board->GetSnake()->GetHeadX() == -1
		|| board->GetSnake()->GetHeadX() == WINDOWSIZE_W / PIXELSIZE
		|| board->GetSnake()->GetHeadY() == -1
		|| board->GetSnake()->GetHeadY() == WINDOWSIZE_H / PIXELSIZE)
		board->GetSnake()->SetGameState(true);
	for (int i = 1; i < board->GetSnake()->GetSnakeLength(); ++i) {
		if (board->GetSnake()->GetHeadX() == board->GetSnake()->GetPartOfTailX(i)
			&& board->GetSnake()->GetHeadY() == board->GetSnake()->GetPartOfTailY(i))
			board->GetSnake()->SetGameState(true);
	}
	if (board->GetSnake()->GetHeadX() == board->GetFruit()->GetX()
		&& board->GetSnake()->GetHeadY() == board->GetFruit()->GetY()) {
		board->GetSnake()->SetSnakeLength(board->GetSnake()->GetSnakeLength() + 1);
		if (board->GetSnake()->GetSnakeLength() > MAX)
			board->GetSnake()->SetSnakeLength(MAX);
		board->GetFruit()->SetReset(true);
	}
}

void drawFruit()
{
	if (board->GetFruit()->GetReset()) {
		board->GetFruit()->SetX();
		board->GetFruit()->SetY();
	}
	board->GetFruit()->SetReset(false);

	glPointSize(PIXELSIZE);

	glBegin(GL_POINTS);

	glColor3f(1, 0, 0);

	glVertex2i(board->GetFruit()->GetX(), board->GetFruit()->GetY());

	glEnd();
}

void input(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (Snake::GetDirection() != sDirection::DOWN)
			Snake::SetDirection(sDirection::UP);
		break;
	case GLUT_KEY_DOWN:
		if (Snake::GetDirection() != sDirection::UP)
			Snake::SetDirection(sDirection::DOWN);
		break;
	case GLUT_KEY_RIGHT:
		if (Snake::GetDirection() != sDirection::LEFT)
			Snake::SetDirection(sDirection::RIGHT);
		break;
	case GLUT_KEY_LEFT:
		if (Snake::GetDirection() != sDirection::RIGHT)
			Snake::SetDirection(sDirection::LEFT);
		break;
	}
}