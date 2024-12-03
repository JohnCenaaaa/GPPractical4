
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"
#define PIE 3.1415926

float color = 0.1f;
// cube variable
float cubeX = 0.0f;
float cubeY = 0.0f;
float cubeZ = 0.0f;

float cubeRotX = 0.0f;
float cubeRotZ2 = 0.0f;
float cubeRotY = 0.0f;
float cubeRotZ = 0.0f;

float movementSpeed = 0.01;
float rotationSpeed = 10;

int questionToShow;
const float numOfTriangle = 100;
const float angle = PIE * 2.f / numOfTriangle;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case 'X':
				//rotate on  X axis
				cubeRotX += rotationSpeed;
				break;
			case 'Y':
				//rotate on  Y axis
				cubeRotY += rotationSpeed;
				break;
			case 'Z':
				//rotate on  Z axis
				cubeRotZ += rotationSpeed;
				break;
			case 'W':
				//rotate on  X axis
				cubeRotX -= rotationSpeed;
				break;
			case 'S':
				//rotate on  X axis
				cubeRotX += rotationSpeed;
				break;
			case 'A':
				//rotate on  Y axis
				cubeRotY -= rotationSpeed;
				break;
			case 'D':
				//rotate on  Y axis
				cubeRotY += rotationSpeed;
				break;
			case VK_UP:
				cubeRotZ2 += rotationSpeed;
				break;
			case VK_DOWN:
				cubeRotZ2 -= rotationSpeed;
				break;
			case VK_LEFT:
				cubeRotY -= rotationSpeed;
				break;
			case VK_RIGHT:
				cubeRotY += rotationSpeed;
				break;
			case VK_SPACE:
				cubeRotX = 0.0f;
				cubeRotY = 0.0f;
				cubeRotZ = 0.0f;
				cubeRotZ2 = 0.0f;
				break;
			case 0x31:
				questionToShow = 1;
				break;
			case 0x32:
				questionToShow = 2;
				break;
			case 0x33:
				questionToShow = 3;
				break;
			case 0x34:
				questionToShow = 4;
				break;
			case 0x35:
				questionToShow = 5;
				break;
			case 0x36:
				questionToShow = 6;
				break;
			case 0x37:
				questionToShow = 7;
				break;
			case 0x38:
				questionToShow = 8;
				break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	switch (questionToShow) {
	case 1:
		glClearColor(color, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		
		glTranslatef(cubeX, cubeY, cubeZ);
		glRotatef(cubeRotX, 1.0, 0.0f, 0.0f);
		glRotatef(cubeRotY, 0.0, 1.0f, 0.0f);
		glRotatef(cubeRotZ, 0.0, 0.0f, 1.0f);
		glBegin(GL_QUADS);//front
		glColor3f(1, 1, 1);
		glVertex3f(-0.5, 0.5,0.5);
		glVertex3f(-0.5, -0.5,0.5);
		glVertex3f(0.5, -0.5,0.5);
		glVertex3f(0.5, 0.5,0.5);
		glEnd();

		glBegin(GL_QUADS);//right
		glColor3f(1, 0, 0);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glEnd();

		glBegin(GL_QUADS);//back
		glColor3f(0, 0, 1);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glEnd();

		glBegin(GL_QUADS);//left
		glColor3f(0, 1, 0);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glEnd();

		glBegin(GL_QUADS);//bottom
		glColor3f(1, 1, 0);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glEnd();

		glBegin(GL_QUADS); //top
		glColor3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, -0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glVertex3f(0.5,0.5, -0.5);
		glEnd();
		
		break;
	case 2:
		glClearColor(color, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();

		glTranslatef(cubeX, cubeY, cubeZ);
		glRotatef(cubeRotX, 1.0, 0.0f, 0.0f);
		glRotatef(cubeRotY, 0.0, 1.0f, 0.0f);
		glRotatef(cubeRotZ, 0.0, 0.0f, 1.0f);

		glBegin(GL_LINE_LOOP); //front
		glColor3f(1, 1, 1);
		glVertex3f(0, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glEnd();

		glBegin(GL_LINE_LOOP); //right
		glColor3f(1, 1, 1);
		glVertex3f(0, 0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glEnd();

		glBegin(GL_LINE_LOOP); //back
		glColor3f(1, 1, 1);
		glVertex3f(0, 0.5, 0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();

		glBegin(GL_LINE_LOOP); //left
		glColor3f(1, 1, 1);
		glVertex3f(0, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glEnd();

		break;
	case 3: 
		glClearColor(color, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();

		glPushMatrix();
			glRotatef(cubeRotX, 1.0f, 0.0f, 0.0f);
			glRotatef(cubeRotY, 0.0, 1.0f, 0.0f);

			glPushMatrix();//left side 
				glBegin(GL_LINE_LOOP);//front
				glColor3f(1, 1, 1);
				glVertex3f(-0.5, 0.1, 0.2);
				glVertex3f(-0.5, -0.1, 0.2);
				glVertex3f(0, -0.1, 0.2);
				glVertex3f(0, 0.1, 0.2);
				glEnd();

				glBegin(GL_LINE_LOOP);//right
				glColor3f(1, 1, 1);
				glVertex3f(0, 0.1, 0.2);
				glVertex3f(0, -0.1, 0.2);
				glVertex3f(0, -0.1, 0);
				glVertex3f(0, 0.1, 0);
				glEnd();

				glBegin(GL_LINE_LOOP);//back
				glColor3f(1, 1, 1);
				glVertex3f(-0.5, 0.1,0);
				glVertex3f(0, 0.1, 0);
				glVertex3f(0, -0.1, 0);
				glVertex3f(-0.5, -0.1,0);
				glEnd();

				glBegin(GL_LINE_LOOP);//left
				glColor3f(1, 1, 1);
				glVertex3f(-0.5, 0.1, 0.2);
				glVertex3f(-0.5, -0.1, 0.2);
				glVertex3f(-0.5, -0.1, 0);
				glVertex3f(-0.5, 0.1, 0);
				glEnd();
			glPopMatrix();

			glPushMatrix();//right side
				glRotatef(cubeRotZ2, 0.0f, 0.0f, 1.0f);
				glBegin(GL_LINE_LOOP);//front
				glColor3f(1, 1, 1);
				glVertex3f(0, 0.1, 0.2);
				glVertex3f(0, -0.1, 0.2);
				glVertex3f(0.5, -0.1, 0.2);
				glVertex3f(0.5, 0.1, 0.2);
				glEnd();

				glBegin(GL_LINE_LOOP);//right
				glColor3f(1, 1, 1);
				glVertex3f(0.5, 0.1, 0.2);
				glVertex3f(0.5, -0.1, 0.2);
				glVertex3f(0.5, -0.1, 0);
				glVertex3f(0.5, 0.1, 0);
				glEnd();

				glBegin(GL_LINE_LOOP);//back
				glColor3f(1, 1, 1);
				glVertex3f(0, 0.1, 0);
				glVertex3f(0.5, 0.1, 0);
				glVertex3f(0.5, -0.1, 0);
				glVertex3f(0, -0.1, 0);
				glEnd();

				glBegin(GL_LINE_LOOP);//left
				glColor3f(1, 1, 1);
				glVertex3f(0, 0.1, 0.2);
				glVertex3f(0, -0.1, 0.2);
				glVertex3f(0, -0.1, 0);
				glVertex3f(0, 0.1, 0);
				glEnd();
			glPopMatrix();
		glPopMatrix();
		break;
	}
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	

	

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------


// hinstance hinst is something like provide an ID, like maybe i need to open 5 times the program, but they are in same program, then each of the program has an id
// histance hprevinst rarely use it, it is for security purpose
// lpstr cmdlineparam is command line parameter,OS pass command to program
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdlineparam, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); //zeromemory find address, get the size, and fill zero 

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL); //or put hInst, same result
	wc.lpfnWndProc = WindowProcedure; //window procedure incharge on capture input and process it, example is when user wan to close the program, then it will capture it and process
	wc.lpszClassName = WINDOW_TITLE; //classname, can put whatever u wan
	wc.style = CS_HREDRAW | CS_VREDRAW; // horizontal size and vertical size

	if (!RegisterClassEx(&wc)) return false; //define the class, check whether it is correct created or not, the above one

	HWND hWnd = CreateWindow(WINDOW_TITLE, // this one is ur window class name,
		WINDOW_TITLE, // this one is your window title, at left corner
		WS_OVERLAPPEDWINDOW, //style
		CW_USEDEFAULT, //size of the window location
		CW_USEDEFAULT, //size of the window location
		800, //width
		800, //height
		NULL,
		NULL, //menu paramenter, something like this vs 2022 top one punya menu, file,edit.....
		wc.hInstance, //the id
		NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true) // infinite loop, keep track user event
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // check if got message or not,
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------