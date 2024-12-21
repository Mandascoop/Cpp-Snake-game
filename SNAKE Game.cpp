#include <iostream>
#include <conio.h>
#include <thread>  
#include <Windows.h> 

using namespace std;

bool gameOver;
bool wallsKill = false;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int speed = 100;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

//first need to setup 4 functions: 
// 1. setup
void Menu() {
	cout << "####################################" << endl;
	cout << "#          S  N  A  K  E           #" << endl;
	cout << "#               v1.0               #" << endl;
	cout << "####################################" << endl;
	cout << endl;
	cout << "Choose the game speed (ms between console prints): ";
	cin >> speed;

	cout << "Turn off EAZY MODE ? (Walls kill, 1 for yes 0 for no): ";
	int choice;
	cin >> choice;
	wallsKill = (choice == 1);

	cout << "\nGame starting with speed " << speed << " ms and wallskill = " << (wallsKill ? "Enabled" : "Disabled") << endl;
	cout << "\nPress enter to start the game..." << endl;
	system("cls");
}
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

//2. draw

void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
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
				

			if (j == width - 1)
				cout << '#';
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
//3. input

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
//4. logic

void Logic()
{
	for (int i = nTail; i > 0; i--)
	{
		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	}
	tailX[0] = x;
	tailY[0] = y;

	switch (dir)
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
	if (wallsKill) {
		if (x > width || x < 0 || y > height || y < 0)
			gameOver = true;
	}	else {
		if (x >= width) x = 0; else if (x < 0) x = width - 1;
		if (y >= height) y = 0; else if (y < 0) y = height - 1;

	}

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}


int main() {
		
	Menu();
	Setup();
	while (!gameOver){
			Draw();
			Input();
			Logic();
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		}
	return 0;
	}
