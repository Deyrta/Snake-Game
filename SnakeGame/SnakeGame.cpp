#include "pch.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int k = 4;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton direction;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void cls()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Setup()
{
	srand(time(0));
	gameOver = false;
	direction = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	cls();
	SetConsoleTextAttribute(hConsole, 25);
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			SetConsoleTextAttribute(hConsole, 15);
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
			{
				SetConsoleTextAttribute(hConsole, 10);
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			SetConsoleTextAttribute(hConsole, 25);
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	SetConsoleTextAttribute(hConsole, 25);
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	SetConsoleTextAttribute(hConsole, 12);
	cout << "Score:" << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (direction != RIGHT || nTail == 0)direction = LEFT; break;
		case 'd':
			if (direction != LEFT || nTail == 0) direction = RIGHT; break;
		case 'w':
			if (direction != DOWN || nTail == 0) direction = UP; break;
		case 's':
			if (direction != UP || nTail == 0) direction = DOWN; break;
		case 'q':
			direction = STOP; break;
		case 'x':
			gameOver = true; break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (direction)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
	//  gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

int main()
{
	ShowConsoleCursor(FALSE);
	Setup();
	cout << "Hard - 1 \t Normal - 2 \t Easy - 3" << endl;
	int speed;
	cin >> speed;
	system("cls");
	switch (speed)
	{
	case 1:
		speed = 50;
		break;
	case 2:
		speed = 100;
		break;
	case 3:
		speed = 250;
		break;
	}
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(speed);//sleep(10);
	}
	system("cls");
	while (true)
		cout << " YOU LOST ";
	return 0;
}
