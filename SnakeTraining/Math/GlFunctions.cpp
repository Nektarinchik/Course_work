#include <glut.h>
#include <cstdlib>

#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Constants.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\GlFunctions.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Directions.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Board.h"
#include "C:\Users\MSI\Desktop\SnakeTraining\Headers\Universe.h"

Universe* universe;

bool isFirst = true;

void draw()
{
	if (isFirst) {
		universe = new Universe();
		isFirst = false;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	universe->Step();
	drawSnake();
	logic();
	drawFruit();
	glutSwapBuffers();
	bool isAlive = false;
	for (int i = 0; i < universe->GetWorlds(); ++i) {
		if (!universe->GetBoard(i)->GetSnake()->GetGameState()) {
			isAlive = true;
			break;
		}
	}
	if (!isAlive) {
		universe->SpawnNextGeneration();
	}
	system("cls");
	std::cout << universe->GetBestSnake()->Report() << "\r\nGeneration: " << universe->GetGeneration();
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
	for (int i = 0; i < universe->GetWorlds(); ++i) {
		if (!universe->GetBoard(i)->GetSnake()->GetGameState()) {
			for (int j = universe->GetBoard(i)->GetSnake()->GetSnakeLength() - 1; j > 0; --j) {
				universe->GetBoard(i)->GetSnake()->SetPartOfTailX(j, universe->GetBoard(i)->GetSnake()->GetPartOfTailX(j - 1));
				universe->GetBoard(i)->GetSnake()->SetPartOfTailY(j, universe->GetBoard(i)->GetSnake()->GetPartOfTailY(j - 1));
			}
			switch (universe->GetBoard(i)->GetSnake()->GetDirection())
			{
			case sDirection::UP:
				universe->GetBoard(i)->GetSnake()->SetHeadY(universe->GetBoard(i)->GetSnake()->GetHeadY() + 1);
				break;
			case sDirection::DOWN:
				universe->GetBoard(i)->GetSnake()->SetHeadY(universe->GetBoard(i)->GetSnake()->GetHeadY() - 1);
				break;
			case sDirection::RIGHT:
				universe->GetBoard(i)->GetSnake()->SetHeadX(universe->GetBoard(i)->GetSnake()->GetHeadX() + 1);
				break;
			case sDirection::LEFT:
				universe->GetBoard(i)->GetSnake()->SetHeadX(universe->GetBoard(i)->GetSnake()->GetHeadX() - 1);
				break;
			case sDirection::STOP:
				break;
			}

			glPointSize(PIXELSIZE);

			glBegin(GL_POINTS);

			glColor3f(0, 1, 0);

			for (int k = 0; k < universe->GetBoard(i)->GetSnake()->GetSnakeLength(); ++k) {
				glVertex2i(universe->GetBoard(i)->GetSnake()->GetPartOfTailX(k), universe->GetBoard(i)->GetSnake()->GetPartOfTailY(k));
			}

			glEnd();
		}
	}
}

void logic()
{
	for (int i = 0; i < universe->GetWorlds(); ++i) {
		if (!universe->GetBoard(i)->GetSnake()->GetGameState()) {
			Snake* snake = universe->GetBoard(i)->GetSnake();
			if (!universe->GetBoard(i)->Contains(Position(snake->GetHeadX(), snake->GetHeadY()))
				|| !snake->GetTimeRemaining())
				snake->SetGameState(true);
			if (snake->GetDirection() != sDirection::STOP) {
				for (int j = 1; j < snake->GetSnakeLength(); ++j) {
					if (snake->GetHeadX() == snake->GetPartOfTailX(j)
						&& snake->GetHeadY() == snake->GetPartOfTailY(j)) {
						snake->SetGameState(true);
						break;
					}
				}
			}
			snake->SetLifeTime(snake->GetLifeTime() + 1);
			snake->SetTimeRemaining(snake->GetTimeRemaining() - 1);
			if (snake->GetHeadX() == universe->GetBoard(i)->GetFruit()->GetX()
				&& snake->GetHeadY() == universe->GetBoard(i)->GetFruit()->GetY()) {
				snake->SetSnakeLength(snake->GetSnakeLength() + 1);
				snake->SetFruits(snake->GetFruits() + 1);
				snake->SetTimeRemaining(snake->GetTimeRemaining() + snake->GetBonusPerApple());
				if (snake->GetSnakeLength() > MAX)
					snake->SetSnakeLength(MAX);
				universe->GetBoard(i)->GetFruit()->SetReset(true);
			}
			snake->ResetScore();
		}
	}
}

void drawFruit()
{
	for (int i = 0; i < universe->GetWorlds(); ++i) {
		if (!universe->GetBoard(i)->GetSnake()->GetGameState()) {
			if (universe->GetBoard(i)->GetFruit()->GetReset()) {
				universe->GetBoard(i)->GetFruit()->SetX();
				universe->GetBoard(i)->GetFruit()->SetY();
			}
			universe->GetBoard(i)->GetFruit()->SetReset(false);

			glPointSize(PIXELSIZE);

			glBegin(GL_POINTS);

			glColor3f(1, 0, 0);

			glVertex2i(universe->GetBoard(i)->GetFruit()->GetX(), universe->GetBoard(i)->GetFruit()->GetY());

			glEnd();
		}
	}
}

