#pragma once
#include "stdafx.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "classes.h"
#include "colour.h"
#include "math.h"

using namespace std;

#define ARROW_CONTROL 224
#define ARROW_UP 72
#define ARROW_RIGHT 77
#define ARROW_DOWN 80
#define ARROW_LEFT 75

bool start();
void runGame();
char getKeyboardDirection();
void pct(string str);

int main()
{
	char choice;
	start();

	system("cls");
	pct("&&Would you like to play? Y/N");

	while ((choice = toupper(_getch())) != 'Y' && choice != 'N');

	while (choice == 'Y')
	{

		runGame();

		system("cls");
		pct("&&Would you like to play? Y/N");

		while ((choice = toupper(_getch())) != 'Y' && choice != 'N');

	}
	
    return EXIT_SUCCESS;
}

bool start()
{
	srand(time(NULL));
	setDefaultColour(0x07);
	return true;
}

void runGame()
{

	int height = 0, width = 0;

	system("cls");
	pct("&&Board width: ");
	cin >> width;
	while (width < 2)
	{
		system("cls");
		pct("&&Error, width must be grater then 1\nBoard width: ");
		cin >> width;
	}

	system("cls");
	pct("&&Board height: ");
	cin >> height;
	while (height < 2)
	{
		system("cls");
		pct("&&Error, height must be grater then 1\nBoard height: ");
		cin >> height;
	}

	Grid grid = Grid(width, height);

	while (true)
	{
		grid.addTile(((rand() % 4) == 0) ? (2) : (1));
		if (grid.noMoreMoves() == true) { break; }

		system("cls");
		pct("&&Use the arrow keys to choose a direction to slide the tiles\n\n");
		pct(grid.renderScore() + "\n\n");
		pct(grid.renderGrid());
		while (grid.slideBoard(getKeyboardDirection()) == false);
	}

	system("cls");
	pct("&&Game over\n\n");
	pct(grid.renderScore() + "\n\n");
	pct(grid.renderGrid() + "\n\n");
	pct("Press enter to return to main menu...");

	while (_getch() != 13);

}

char getKeyboardDirection()
{
	while (true)
	{
		while (_getch() != ARROW_CONTROL);
		switch (_getch())
		{
		case ARROW_UP:
			return 'U';
		case ARROW_RIGHT:
			return 'R';
		case ARROW_DOWN:
			return 'D';
		case ARROW_LEFT:
			return 'L';
		default:
			break;
		}
	}
}

void pct(string str)
{
	printColoredText(str);
}
