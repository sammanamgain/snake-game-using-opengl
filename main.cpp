#include<windows.h>//include otherwise glut lib doesnot work 
#include<GL/gl.h> //header file for opengl
#include <GL/glut.h>  // opengl utility toolkit 
#include <iostream>
#include"Header.h"
#include<string>
#include<cstring>
#include<winuser.h>
#include<stdlib.h>
#define column 40
#define row 40
#define fps 10
#define MSGBOX(x) \
{ \
   std::ostringstream oss; \
   oss << x; \
   MessageBox(oss.str().c_str(), "Msg Title", MB_OK | MB_ICONQUESTION); \
}
int score = 0;
//using namespace std;
extern short sDirection;
bool gameover = false;
void display_callback ();
void init();
void reshape(int,int );
void timer_callback(int);
void keyboard_callback(int, int, int);
int main(int argc, char** argv)  // to initialize the glut libraray
{
	
	glutInit(&argc, argv);// initalize the glut // passing address

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //selecting display mode between rbg and index
	glutInitWindowSize(900, 900); //size of window
	glutCreateWindow("SNAKE_GAME_BY_SAMMAN");
	glutDisplayFunc(display_callback);//display has to be call back
	glutReshapeFunc(reshape);// to reset viewport
	glutTimerFunc(0,timer_callback,0);
	glutSpecialFunc(keyboard_callback);
	init();
									  
									  //glutInitWindowPosition();//to select window at particular postition
	glutMainLoop(); //after calling this function all subroutines will be called
	
	/*
	glutInit(&argc, argv);  // to initialize the glut libraray
	glutInitDisplayMode(GLUT_RGB);   // WINDOW WILL BE OPEN IN RGB MODE
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);
	
	glutCreateWindow("window title");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);  // for the defining the viwport
	glClearColor(0.0, 1.0, 1.0,1.0);   // for color mode
	glutMainLoop();  // after completion of this loop , window will terminate

	*/


	return 0;
}


void display_callback()
{
	int index = 0;

	
	glClear(GL_COLOR_BUFFER_BIT);	//clears the frame buffers
	drawGrid();
	drawsnake();
	drawfood();
	glutSwapBuffers();  //buffer will swap and next frame will be displayed
	
	if (gameover)
	{
		std::string s = std::to_string(score);
	//	char Score[10];
	//	_itoa_s(score, Score, 10);//convert int to string
//	std::string text = "your score :  ";
		/*char buff[100];
		std::string name = "stackoverflow";
		sprintf_s(buff, "name is:%s", name.c_str());
		std::cout << buff;
		MessageBox(NULL, buff, "Msgtitle", MB_OK | MB_ICONQUESTION);
		*/
	
	char text[100];
	
	std::string myString = "your score = ";
	//int width = 1024;
	myString += std::to_string(score);

	LPWSTR ws = new wchar_t[myString.size() + 1];
	copy(myString.begin(), myString.end(), ws);
	ws[myString.size()] = 0; // zero at the end

	MessageBox(NULL, ws, L"snake game", MB_ICONEXCLAMATION | MB_OK);
	/// <summary>
	/// 
	/// </summary>
	//sprintf_s(text, "the score is : %d", score);
	//MessageBox(NULL, text, "Msg title", MB_OK | MB_ICONQUESTION);
		//MessageBox(NULL,text, "",MB_OK
		/*	MB_OK | MB_ICONEXCLAMATION
		*/
		exit(0);
	}
	glLoadIdentity();// reset the coordinate system 






	glFlush();  //display the frame buffer

}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(column, row);
	
}
void reshape(int w, int h)  // this function when window is minimized or maximized or size change. 
{
	glViewport(0, 0,(GLsizei)w, (GLsizei)h);
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();//reset parameter of  matrix
	glOrtho(0.0,column,0.0,row,-1.0,1.0);//for the projection of the objects
	glMatrixMode(GL_MODELVIEW);

}
void timer_callback(int )
{

	glutPostRedisplay();//each time display function is called again
	glutTimerFunc(1000/fps,timer_callback,0);//we want 10 fps so
}
void keyboard_callback(int key, int, int)
{
	switch (key)
	{
	        case GLUT_KEY_UP:  //snake doesnot rotate 180 degree
				if (sDirection != down)
					sDirection = up;
				break;
			case GLUT_KEY_DOWN:
				if (sDirection != up)
					sDirection = down;
				break;

			case GLUT_KEY_RIGHT:
				if (sDirection !=left)
					sDirection = right;
				break;
			case GLUT_KEY_LEFT:
				if (sDirection !=right)
					sDirection = left;
				break;
	}
	
}
