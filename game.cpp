#include <iostream>
#include<windows.h>//include otherwise glut lib doesnot work 
#include<GL/gl.h> //header file for opengl
#include <GL/glut.h>  // opengl utility toolkit 
#include"Header.h"
#include<ctime>
int gridX, gridY;
bool food = true;
short sDirection = right;
extern bool gameover;
extern int score;
int foodX, foodY;
int snakelength = 5;
int postX[60]={20,20,20,20,20}, postY[60]={20,19,18,17,16};

void unit(int, int);
void initGrid(int x, int y)  // to draw grid (rectangular box)
{
	gridX = x;
	gridY = y;
}
void drawGrid()
{
	for (int x = 0; x < gridX; x++) {
		for (int y = 0; y < gridY; y++)
		{
			unit(x,y);
		}
	}
}
void unit(int x, int y) // used to draw unit square
{

	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
	{
		glLineWidth(3.0);
		glColor3f(1.0, 0.0, 0.0);
	}
	else
	{
		glLineWidth(1.0);
		glColor3f(0.0, 0.0, 0.0);
	}
//	glLineWidth(1.0);
//	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);  //first and last vertices will connectd

	glVertex2f(x, y);
	glVertex2f(x+1, y);
	//glVertex2f(x+1, y);
	glVertex2f(x+1, y+1);
	glVertex2f(x, y+1);
	

	glEnd();
}
void drawfood()
{
	if (food)
	        random(foodX, foodY);
		food = false; 
		glRectf(foodX, foodY, foodX + 1, foodY + 1);
		glColor3f(1.0, 0.0, 0.0);

	
}
void drawsnake()
{
	for (int i = snakelength - 1; i >0;i--)
	{
		postX[i] = postX[i - 1];
		postY[i] = postY[i - 1];
	}
	if (sDirection == up)
	{
		postY[0]++;
	}
	else if(sDirection == down)
	{
		postY[0]--;

	}
	else if (sDirection == right)
	{
		postX[0]++;
	}
	else if (sDirection == left)
	{
		postX[0]--;
	}
	for (int i = 0; i < snakelength; i++)
	{
		if (i == 0)
		{
			glColor3f(0.0, 1.0, 0.0);
		}
		else
		{
			glColor3f(0.0, 0.0, 1.0);
			glRectd(postX[i], postY[i], postX[i] + 1, postY[i] + 1);
		}
	}
	glColor3f(0.0, 1.0, 0.0);
	//glRectd(postX, postY, postX + 1, postY + 1);
	/*glRectd(index, 20, index + 2, 22);
	index++;
	if (index > 40)
	{
		index = 0;
	}*/
	//checking collision  for head element only
	 if (postX[0] == 0 || postX[0] == gridX - 1 || postY[0] == 0 || postY[0] == gridY - 1)  //game end condition

	{
		gameover = true;
	}
	if (postX[0] == foodX && postY[0] == foodY)

	{
		score++;
		snakelength++;
		if (snakelength > max)
		{
			snakelength = max;
		}
		food = true;
	}
	for (int j = 1; j < snakelength; j++)
	{
		if (postX[j] == postX[0] && postY[j] == postY[0])
			gameover = true;
	}
}


void random(int &x, int &y)
{
	int maxX = gridX - 2;
	int  maxY = gridY - 2;
	int min = 1;
	srand(time(NULL));
	x=min+rand()%(maxX-min);  //for food at random places
	y = min + rand() % (maxY - min);
}