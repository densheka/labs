/**
*	Source.cpp
*	Purpose: creates a nongram game with 3 levels
*/

#include <GL/glut.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
//checks if left mouse button is clicked
bool click = false;
//tracks the position of the mouse
int x, y;
//are responsible for moving in arrays
int i, j;
//Responsible for level playing
int a[6][6], b[6][6], c[6][6];
//An array that plays the role of a game field
int g[6][6];
//A variable that starts the game from the beginning
bool game = true;
//Responsible for recording from file in game arrays
bool abc = true;
//The variable responsible for winning the game
bool win;

/**
*	Function for displaying text on the screen
*	
*	@brief drawString
*	@param font
*	@param string
*/
void drawString(void *font, const char* string) {
	while (*string)
		glutBitmapCharacter(font, *string++);
}

/**
*	Function that reads the coordinates of the cursor
*
*	@brief motion
*	@param ax
*	@param ay
*/
void motion(int ax, int ay) {
	x = ax;
	y = 500 - ay;
}


/**
*	Reads a click with the left mouse button
*	
*	@brief mouse
*	@param button
*	@param state
*	@param ax
*	@param ay
*/
void mouse(int button, int state, int ax, int ay) {
	if (button == GLUT_LEFT_BUTTON) click = state == GLUT_DOWN;
}


/**
*	A function that sets the refresh rate of the screen
*	
*	@brief update
*/
void update(int) {
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

/**
*	The function that nulls the playing field
*
*	@brief Game
*/
void Game() {
	for (int m = 0; m <= 5; m++) {
		for (int n = 0; n <= 5; n++) {
			g[m][n] = 0;
		}
	}
}
/**
*	This function contains a game menu
*
*	@brief Menu
*/
void Menu();
/**
*	The function that is responsible for the choice of game levels
*
*	@brief Level
*/
void Level();

/**
*	The function that is responsible for the game process in 1 level
*
*	@brief Level1
*/
void Level1() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (game) {
		Game();
		game = false;
	}
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.05, 0.05);

	glVertex2f(0.06, 0.06);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.06, 0.06);
	glEnd();

	for (i = 1; i <= 9; i++) {
		glBegin(GL_LINES);
		glVertex2f(0.1 + (i - 1)*0.1, 0.1);
		glVertex2f(0.1 + (i - 1)*0.1, 0.9);
		glVertex2f(0.1, 0.1 + (i - 1)*0.1);
		glVertex2f(0.9, 0.1 + (i - 1)*0.1);
		glEnd();
	}
	//
	win = true;
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			if (g[i][j] != a[i][j]) { win = false; }
		}
	}
	//
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			if (g[i][j] == 1) {
				glColor3f(0.0, 0.0, 0.0);
			}
			else {
				glColor3f(0.0, 0.6, 0.6);
			}
			glBegin(GL_QUADS);
			glVertex2f(0.41 + (j - 1)*0.1, 0.69 - (i - 1)*0.1);
			glVertex2f(0.49 + (j - 1)*0.1, 0.69 - (i - 1)*0.1);
			glVertex2f(0.49 + (j - 1)*0.1, 0.61 - (i - 1)*0.1);
			glVertex2f(0.41 + (j - 1)*0.1, 0.61 - (i - 1)*0.1);
			glEnd();
			if (!win) {
				if ((x > (200 + (j - 1) * 50) && x < (250 + (j - 1) * 50)) && (y > (300 - (i - 1) * 50) && y < (350 - (i - 1) * 50))) {
					if (click) {
						if (click) click = false;
						if (g[i][j] == 0) {
							g[i][j] = 1;
						}
						else { g[i][j] = 0; }
					}
				}
			}
		}
	}
	glColor3f(0.0, 0.0, 0.0);
	//
	glRasterPos3f(0.84, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	glRasterPos3f(0.74, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.74, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.64, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "4");
	glRasterPos3f(0.54, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.54, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.44, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	glRasterPos3f(0.34, 0.63, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	glRasterPos3f(0.34, 0.53, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "5");
	glRasterPos3f(0.34, 0.43, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.24, 0.43, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.14, 0.43, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.34, 0.33, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "5");
	glRasterPos3f(0.34, 0.23, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.24, 0.23, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	//
	if (win) {
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(0.14, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Y");
		glRasterPos3f(0.24, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "O");
		glRasterPos3f(0.34, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "U");
		glRasterPos3f(0.54, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "W");
		glRasterPos3f(0.64, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "I");
		glRasterPos3f(0.74, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "N");
		glRasterPos3f(0.84, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "!");
	}
	//
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.06, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.94);
	glEnd();
	if ((x > 30 && x < 50) && (y > 445 && y < 470)) {
		glColor3f(1.0, 0.0, 0.0);
		if (click) {
			if (click) click = false;
			game = true;
			glutDisplayFunc(Level);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.061, 0.9, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "X");
	glutSwapBuffers();
}

/**
*	The function that is responsible for the game process in 2 level
*
*	@brief Level2
*/
void Level2() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (game) {
		Game();
		game = false;
	}
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.05, 0.05);

	glVertex2f(0.06, 0.06);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.06, 0.06);
	glEnd();

	for (i = 1; i <= 9; i++) {
		glBegin(GL_LINES);
		glVertex2f(0.1 + (i - 1)*0.1, 0.1);
		glVertex2f(0.1 + (i - 1)*0.1, 0.9);
		glVertex2f(0.1, 0.1 + (i - 1)*0.1);
		glVertex2f(0.9, 0.1 + (i - 1)*0.1);
		glEnd();
	}
	//
	win = true;
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			if (g[i][j] != b[i][j]) { win = false; }
		}
	}
	//
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			if (g[i][j] == 1) {
				glColor3f(0.0, 0.0, 0.0);
			}
			else {
				glColor3f(0.0, 0.6, 0.6);
			}
			glBegin(GL_QUADS);
			glVertex2f(0.41 + (j - 1)*0.1, 0.69 - (i - 1)*0.1);
			glVertex2f(0.49 + (j - 1)*0.1, 0.69 - (i - 1)*0.1);
			glVertex2f(0.49 + (j - 1)*0.1, 0.61 - (i - 1)*0.1);
			glVertex2f(0.41 + (j - 1)*0.1, 0.61 - (i - 1)*0.1);
			glEnd();
			if (!win) {
				if ((x > (200 + (j - 1) * 50) && x < (250 + (j - 1) * 50)) && (y > (300 - (i - 1) * 50) && y < (350 - (i - 1) * 50))) {
					if (click) {
						if (click) click = false;
						if (g[i][j] == 0) {
							g[i][j] = 1;
						}
						else { g[i][j] = 0; }
					}
				}
			}
		}
	}
	//
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3f(0.84, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	glRasterPos3f(0.74, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.74, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.64, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.64, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.54, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.54, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.44, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	glRasterPos3f(0.34, 0.63, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	glRasterPos3f(0.34, 0.53, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.24, 0.53, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.34, 0.43, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.24, 0.43, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.34, 0.33, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.24, 0.33, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.34, 0.23, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	//
	if (win) {
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(0.14, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Y");
		glRasterPos3f(0.24, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "O");
		glRasterPos3f(0.34, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "U");
		glRasterPos3f(0.54, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "W");
		glRasterPos3f(0.64, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "I");
		glRasterPos3f(0.74, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "N");
		glRasterPos3f(0.84, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "!");
	}
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.06, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.94);
	glEnd();
	if ((x > 30 && x < 50) && (y > 445 && y < 470)) {
		glColor3f(1.0, 0.0, 0.0);
		if (click) {
			if (click) click = false;
			game = true;
			glutDisplayFunc(Level);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.061, 0.9, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "X");
	glutSwapBuffers();
}

/**
*	The function that is responsible for the game process in 3 level
*
*	@brief Level3
*/
void Level3() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (game) {
		Game();
		game = false;
	}
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.05, 0.05);

	glVertex2f(0.06, 0.06);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.06, 0.06);
	glEnd();
	//
	for (i = 1; i <= 9; i++) {
		glBegin(GL_LINES);
		glVertex2f(0.1 + (i - 1)*0.1, 0.1);
		glVertex2f(0.1 + (i - 1)*0.1, 0.9);
		glVertex2f(0.1, 0.1 + (i - 1)*0.1);
		glVertex2f(0.9, 0.1 + (i - 1)*0.1);
		glEnd();
	}
	//
	win = true;
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			if (g[i][j] != c[i][j]) { win = false; }
		}
	}
	//
	for (i = 1; i <= 5; i++) {
		for (j = 1; j <= 5; j++) {
			if (g[i][j] == 1) {
				glColor3f(0.0, 0.0, 0.0);
			}
			else {
				glColor3f(0.0, 0.6, 0.6);
			}
			glBegin(GL_QUADS);
			glVertex2f(0.41 + (j - 1)*0.1, 0.69 - (i - 1)*0.1);
			glVertex2f(0.49 + (j - 1)*0.1, 0.69 - (i - 1)*0.1);
			glVertex2f(0.49 + (j - 1)*0.1, 0.61 - (i - 1)*0.1);
			glVertex2f(0.41 + (j - 1)*0.1, 0.61 - (i - 1)*0.1);
			glEnd();
			if (!win) {
				if ((x > (200 + (j - 1) * 50) && x < (250 + (j - 1) * 50)) && (y > (300 - (i - 1) * 50) && y < (350 - (i - 1) * 50))) {
					if (click) {
						if (click) click = false;
						if (g[i][j] == 0) {
							g[i][j] = 1;
						}
						else { g[i][j] = 0; }
					}
				}
			}
		}
	}
	//
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3f(0.84, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.84, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.74, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.74, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.64, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.54, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.54, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.44, 0.83, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.44, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.24, 0.63, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.34, 0.63, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.24, 0.53, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.34, 0.53, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "2");
	glRasterPos3f(0.24, 0.33, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.34, 0.33, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "1");
	glRasterPos3f(0.34, 0.23, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "3");
	//
	if (win) {
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos3f(0.14, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Y");
		glRasterPos3f(0.24, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "O");
		glRasterPos3f(0.34, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "U");
		glRasterPos3f(0.54, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "W");
		glRasterPos3f(0.64, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "I");
		glRasterPos3f(0.74, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "N");
		glRasterPos3f(0.84, 0.13, 0.0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, "!");
	}
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.06, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.94);
	glEnd();
	if ((x > 30 && x < 50) && (y > 445 && y < 470)) {
		glColor3f(1.0, 0.0, 0.0);
		if (click) {
			if (click) click = false;
			game = true;
			glutDisplayFunc(Level);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.061, 0.9, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "X");
	glutSwapBuffers();
}

//The function that is responsible for the choice of game levels
void Level() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.05, 0.05);

	glVertex2f(0.06, 0.06);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.06, 0.06);

	//level1
	glVertex2f(0.35, 0.8);
	glVertex2f(0.65, 0.8);
	glVertex2f(0.65, 0.8);
	glVertex2f(0.65, 0.7);
	glVertex2f(0.65, 0.7);
	glVertex2f(0.35, 0.7);
	glVertex2f(0.35, 0.7);
	glVertex2f(0.35, 0.8);

	//level2
	glVertex2f(0.35, 0.55);
	glVertex2f(0.65, 0.55);
	glVertex2f(0.65, 0.55);
	glVertex2f(0.65, 0.45);
	glVertex2f(0.65, 0.45);
	glVertex2f(0.35, 0.45);
	glVertex2f(0.35, 0.45);
	glVertex2f(0.35, 0.55);

	//level3
	glVertex2f(0.35, 0.3);
	glVertex2f(0.65, 0.3);
	glVertex2f(0.65, 0.3);
	glVertex2f(0.65, 0.2);
	glVertex2f(0.65, 0.2);
	glVertex2f(0.35, 0.2);
	glVertex2f(0.35, 0.2);
	glVertex2f(0.35, 0.3);
	glEnd();
	//level1
	if ((x > 175 && x < 325) && (y > 350 && y < 400)) {
		glBegin(GL_LINES);
		glVertex2f(0.34, 0.81);
		glVertex2f(0.66, 0.81);
		glVertex2f(0.66, 0.81);
		glVertex2f(0.66, 0.69);
		glVertex2f(0.66, 0.69);
		glVertex2f(0.34, 0.69);
		glVertex2f(0.34, 0.69);
		glVertex2f(0.34, 0.81);
		glEnd();
		if (click) {
			if (click) click = false;
			glutDisplayFunc(Level1);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.41, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL1");
	//level2
	if ((x > 175 && x < 325) && (y > 225 && y < 275)) {
		glBegin(GL_LINES);
		glVertex2f(0.34, 0.56);
		glVertex2f(0.66, 0.56);
		glVertex2f(0.66, 0.56);
		glVertex2f(0.66, 0.44);
		glVertex2f(0.66, 0.44);
		glVertex2f(0.34, 0.44);
		glVertex2f(0.34, 0.44);
		glVertex2f(0.34, 0.56);
		glEnd();
		if (click) {
			if (click) click = false;
			glutDisplayFunc(Level2);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.41, 0.48, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL2");
	//LEVEL3
	if ((x > 175 && x < 325) && (y > 100 && y < 150)) {
		glBegin(GL_LINES);
		glVertex2f(0.34, 0.31);
		glVertex2f(0.66, 0.31);
		glVertex2f(0.66, 0.31);
		glVertex2f(0.66, 0.19);
		glVertex2f(0.66, 0.19);
		glVertex2f(0.34, 0.19);
		glVertex2f(0.34, 0.19);
		glVertex2f(0.34, 0.31);
		glEnd();
		if (click) {
			if (click) click = false;
			glutDisplayFunc(Level3);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.41, 0.23, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL3");
	//click X
	glBegin(GL_LINES);
	glVertex2f(0.06, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.94);
	glEnd();
	if ((x > 30 && x < 50) && (y > 445 && y < 470)) {
		glColor3f(1.0, 0.0, 0.0);
		if (click) {
			if (click) click = false;
			glutDisplayFunc(Menu);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.061, 0.9, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "X");
	glutSwapBuffers();
}


/**
*	Here is information about the game
*
*	@brief About
*/
void About() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.05, 0.05);

	glVertex2f(0.06, 0.06);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.06, 0.06);
	glEnd();
	glRasterPos3f(0.1, 0.8, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Created by Shesternyak D.M.");
	glRasterPos3f(0.1, 0.7, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "Nonogram are picture logic puzzles in");
	glRasterPos3f(0.1, 0.6, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, " which cells in a grid must be colored or");
	glRasterPos3f(0.1, 0.5, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, " left blank according to numbers at the");
	glRasterPos3f(0.1, 0.4, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, " side of the grid to reveal a hidden picture.");
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.06, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.89);
	glVertex2f(0.1, 0.94);
	glEnd();
	if ((x > 30 && x < 50) && (y > 445 && y < 470)) {
		glColor3f(1.0, 0.0, 0.0);
		if (click) {
			if (click) click = false;
			glutDisplayFunc(Menu);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.061, 0.9, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "X");
	glutSwapBuffers();
}

//This function contains a game menu
void Menu() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.05, 0.05);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.05, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.95);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.95, 0.05);
	glVertex2f(0.05, 0.05);

	glVertex2f(0.06, 0.06);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.06, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.94);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.94, 0.06);
	glVertex2f(0.06, 0.06);

	//play
	glVertex2f(0.35, 0.8);
	glVertex2f(0.65, 0.8);
	glVertex2f(0.65, 0.8);
	glVertex2f(0.65, 0.7);
	glVertex2f(0.65, 0.7);
	glVertex2f(0.35, 0.7);
	glVertex2f(0.35, 0.7);
	glVertex2f(0.35, 0.8);

	//about
	glVertex2f(0.35, 0.55);
	glVertex2f(0.65, 0.55);
	glVertex2f(0.65, 0.55);
	glVertex2f(0.65, 0.45);
	glVertex2f(0.65, 0.45);
	glVertex2f(0.35, 0.45);
	glVertex2f(0.35, 0.45);
	glVertex2f(0.35, 0.55);

	//exit
	glVertex2f(0.35, 0.3);
	glVertex2f(0.65, 0.3);
	glVertex2f(0.65, 0.3);
	glVertex2f(0.65, 0.2);
	glVertex2f(0.65, 0.2);
	glVertex2f(0.35, 0.2);
	glVertex2f(0.35, 0.2);
	glVertex2f(0.35, 0.3);
	glEnd();
	//play
	if ((x > 175 && x < 325) && (y > 350 && y < 400)) {
		glBegin(GL_LINES);
		glVertex2f(0.34, 0.81);
		glVertex2f(0.66, 0.81);
		glVertex2f(0.66, 0.81);
		glVertex2f(0.66, 0.69);
		glVertex2f(0.66, 0.69);
		glVertex2f(0.34, 0.69);
		glVertex2f(0.34, 0.69);
		glVertex2f(0.34, 0.81);
		glEnd();
		if (click) {
			if (click) click = false;
			glutDisplayFunc(Level);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.44, 0.73, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "PLAY");
	//about
	if ((x > 175 && x < 325) && (y > 225 && y < 275)) {
		glBegin(GL_LINES);
		glVertex2f(0.34, 0.56);
		glVertex2f(0.66, 0.56);
		glVertex2f(0.66, 0.56);
		glVertex2f(0.66, 0.44);
		glVertex2f(0.66, 0.44);
		glVertex2f(0.34, 0.44);
		glVertex2f(0.34, 0.44);
		glVertex2f(0.34, 0.56);
		glEnd();
		if (click) {
			if (click) click = false;
			glutDisplayFunc(About);
			glutPostRedisplay();
		}
	}
	glRasterPos3f(0.415, 0.48, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "ABOUT");
	//exit
	if ((x > 175 && x < 325) && (y > 100 && y < 150)) {
		glBegin(GL_LINES);
		glVertex2f(0.34, 0.31);
		glVertex2f(0.66, 0.31);
		glVertex2f(0.66, 0.31);
		glVertex2f(0.66, 0.19);
		glVertex2f(0.66, 0.19);
		glVertex2f(0.34, 0.19);
		glVertex2f(0.34, 0.19);
		glVertex2f(0.34, 0.31);
		glEnd();
		if (click) {
			if (click) click = false;
			exit(1);
		}
	}
	glRasterPos3f(0.44, 0.23, 0.0);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "EXIT");
	if (abc) {
		ifstream aa("a.txt");
		for (i = 0; i <= 5; i++) {
			for (j = 0; j <= 5; j++) {
				aa >> a[i][j];
			}
		}
		ifstream bb("b.txt");
		for (i = 0; i <= 5; i++) {
			for (j = 0; j <= 5; j++) {
				bb >> b[i][j];
			}
		}
		ifstream cc("c.txt");
		for (i = 0; i <= 5; i++) {
			for (j = 0; j <= 5; j++) {
				cc >> c[i][j];
			}
		}
		abc = false;
	}
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Nonogram");
	glClearColor(0.0, 0.6, 0.6, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(Menu);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}