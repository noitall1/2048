// Mark Morra
// 2019

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

	while ((choice = toupper(_getch())) != 'Y' && choice != 'N'); //gets user input

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
	setDefaultColour(0x07); //sets the default console colour in colour.h library
	return true;
}

void runGame()
{

	int height = 0, width = 0;

	system("cls"); //gets board height and width from user
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

	Grid grid = Grid(width, height); //sets up game
	grid.colours.getsetEmptyC("&07"); //sets up colours for game
	grid.colours.getsetDefaultC("&E0");
	string colours[] = { "&8F","&9F","&2F","&A0","&3F","&B0","&C0","&D0","&F0","&1B","&2D"};
	grid.colours.getsetColours(colours, 11);

	while (true) //the main loop that runs the game
	{
		grid.addTile(((rand() % 4) == 0) ? (2) : (1)); //adds a new tile to the board
		if (grid.noMoreMoves() == true) { break; } //checks if it is possible to make a move

		system("cls"); //displays the game board
		pct("&&Use the arrow keys to choose a direction to slide the tiles\n\n");
		pct(grid.renderScore() + "\n\n");
		pct(grid.renderGrid());
		while (grid.slideBoard(getKeyboardDirection()) == false); //if the move the user selected results in no tiles moving grid.slideBoard returns false, this loop waits till the user makes a selection that results in the tiles moving
	}

	system("cls"); //displays the game over screen
	pct("&&Game over\n\n");
	pct(grid.renderScore() + "\n\n");
	pct(grid.renderGrid() + "\n\n");
	pct("Press enter to return to main menu...");

	while (_getch() != 13); //waits for user to press enter

}

char getKeyboardDirection() //gets arrow key input from keyboard
{

	//A arrow key is two characters in the input stream character 224 (ARROW_CONTROL) followed by 72,77,80 or 75, the second number indicates the direction

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

void pct(string str) //this function from colour.h is used a lot so this is just so the name isnt as long
{
	printColoredText(str);
}
