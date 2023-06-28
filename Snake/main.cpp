// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "curses.h"
#include <stdlib.h>
#include <time.h>

using namespace std;


enum Direction {
	UP, DOWN, LEFT, RIGHT
};

struct SingleNodeSnake {
	int x;
	int y;
	Direction dir;
	SingleNodeSnake* next;
};

SingleNodeSnake* head;
int Size = 1;
static int  Sizep = 20;//to initialize the length to 20

void inserthead(SingleNodeSnake& snake) {

	SingleNodeSnake* tmp = new SingleNodeSnake;
	tmp->x = snake.x;
	tmp->y = snake.y;
	tmp->next = head;
	head = tmp;
	mvaddch(snake.y, snake.x, '*');

}

void removetail() {
	SingleNodeSnake* index = new SingleNodeSnake;
	SingleNodeSnake* pre = NULL;

	index = head;
	while (index->next != NULL) {
		pre = index;
		index = index->next;
	}
	mvaddch(index->y, index->x, ' ');
	pre->next = NULL;
	
	delete index;
}
void Move(SingleNodeSnake& snake) {

	// Clear '*' at the previous position
	// Update snake's position
	switch (snake.dir) {
	case UP:
		snake.y--;
		break;
	case DOWN:
		snake.y++;
		break;
	case LEFT:
		snake.x--;
		break;
	case RIGHT:
		snake.x++;
		break;
	}

	// Draw '*' at the new position
	
	
		

	inserthead(snake);
	removetail();
}


int main() {
	int c, maxX, maxY;
	bool terminated = false;
	SingleNodeSnake snake;

	srand(time(NULL));

	// Set the initial position and moving direction
	snake.x = 1+rand()%120;//the random position
	snake.y = 1+rand()%30;//the random position
	snake.dir = RIGHT;
	head = new SingleNodeSnake;
	head = NULL;
	initscr();
	cbreak();						// Disable buffering, making input available to the program immediately
	timeout(500);					// Wait user's input for at most 1s
	keypad(stdscr, TRUE);			// Enable input from arrow keys
	curs_set(0); 					// Hide cursor
	getmaxyx(stdscr, maxY, maxX);	// Get max X and Y of the terminal
	printw("%d %d", maxX, maxY);

	// Draw the single headed snake
	for (int i = 0; i <20; i++) {

		SingleNodeSnake* tmp = new SingleNodeSnake;
		tmp->x = snake.x;
		tmp->y = snake.y;
		tmp->next = head;
		head = tmp;
		mvaddch(snake.y, snake.x, '*');
		snake.x++;
	}
	snake.x = snake.x-1;
	
		int a, b;
	string food[120][30];

	a = 1 + rand() % 120;
	b = 1 + rand() % 30;
	mvaddch(b, a, '$');

	while (!terminated) {

		c = getch();

		switch (c) {
		case KEY_UP:
			snake.dir = UP;
			break;
		case KEY_DOWN:
			snake.dir = DOWN;
			break;
		case KEY_LEFT:
			snake.dir = LEFT;
			break;
		case KEY_RIGHT:
			snake.dir = RIGHT;
			break;
		case 27: // ESC
		case 'q':
			terminated = true;
			break;
		default:
			break;
		}
		Move(snake);

		if (head->x == a && head->y == b) {
			removetail();
			SingleNodeSnake* examination = new SingleNodeSnake;
			examination = head;
			a = 1 + rand() % 120;
			b = 1 + rand() % 30;
			mvaddch(b, a, '$');
			Sizep--;
			while (examination->next != NULL ) {//to examine if the symbol of money overlapes with the body of snake
				examination = examination->next;
				if (a == examination->x && b == examination->y) {
					a = 1 + rand() % 120;
					b = 1 + rand() % 30;
					mvaddch(b, a, '$');
					break;
				}
			}

		}
		if (Sizep == 1) {
			cout << "The mission of loosing weight successed!" << endl;
			break;
		}


	}
	endwin();	// Restores the terminal after Curses activity
}
