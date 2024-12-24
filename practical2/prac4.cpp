
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <gl/GLU.h>
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

GLUquadricObj* var = NULL;
GLUquadricObj* sphere = NULL;
GLUquadricObj* cylinder = NULL;

int slices = 5;
int stacks = 5;

float camX = 0;
float camY = 0;
float camZ = 0;
float cameraSpeed = 1;

//camera properties
float camLeft = -2;
float camRight = 2;
float camBottom = -2;
float camTop = 2;
float camNear = -2;
float camFar = 2;
float cameraModifier = 1;
bool isPerspective = true;

//bridge
float leftConnectorRotationAngle = 0.0f;
float rightConnectorRotationAngle = 0.0f;
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
		case 'N': 
			isPerspective = !isPerspective;
			break;
		case 'W':
			camZ += cameraSpeed;
			break;
		case 'A':
			camX -= cameraSpeed;
			break;
		case 'S':
			camZ -= cameraSpeed;
			break;
		case 'D':
			camX += cameraSpeed;
			break;
		case 'Q':
			camY -= cameraSpeed;
			break;
		case 'E':
			camY += cameraSpeed;
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
			case 'O': 
				if (leftConnectorRotationAngle < 45.0f) {
					leftConnectorRotationAngle += 1.0f;
				}
				if (rightConnectorRotationAngle > -45.0f) {
					rightConnectorRotationAngle -= 1.0f; 
				}
				break;

			case 'P': // Lower connectors
				if (leftConnectorRotationAngle > 0.0f) {
					leftConnectorRotationAngle -= 1.0f; 
				}
				if (rightConnectorRotationAngle < 0.0f) {
					rightConnectorRotationAngle += 1.0f; 
				}
				break;
			case VK_UP:
				cubeRotZ += rotationSpeed;
				break;
			case VK_DOWN:
				cubeRotZ -= rotationSpeed;
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

void drawSingleCylinder(float x, float y, float z) {
	glPushMatrix();
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	glColor3f(0, 0, 0);
	glTranslatef(x, y, z);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 0.01f, 100, 100);
	glPopMatrix();
}

void drawCylinderSeperateLine() {
	//right zhuzhi
	drawSingleCylinder(5.0f, 1.0f, 0.0f);
	drawSingleCylinder(5.0f, 1.5f, 0.0f);
	drawSingleCylinder(5.0f, 3.0f, 0.0f);
	drawSingleCylinder(5.0f, 3.5f, 0.0f);
	drawSingleCylinder(5.0f, 5.0f, 0.0f);

	drawSingleCylinder(7.0f, 1.0f, 0.0f);
	drawSingleCylinder(7.0f, 1.5f, 0.0f);
	drawSingleCylinder(7.0f, 3.0f, 0.0f);
	drawSingleCylinder(7.0f, 3.5f, 0.0f);
	drawSingleCylinder(7.0f, 5.0f, 0.0f);

	drawSingleCylinder(5.0f, 1.0f, -2.0f);
	drawSingleCylinder(5.0f, 1.5f, -2.0f);
	drawSingleCylinder(5.0f, 3.0f, -2.0f);
	drawSingleCylinder(5.0f, 3.5f, -2.0f);
	drawSingleCylinder(5.0f, 5.0f, -2.0f);

	drawSingleCylinder(7.0f, 1.0f, -2.0f);
	drawSingleCylinder(7.0f, 1.5f, -2.0f);
	drawSingleCylinder(7.0f, 3.0f, -2.0f);
	drawSingleCylinder(7.0f, 3.5f, -2.0f);
	drawSingleCylinder(7.0f, 5.0f, -2.0f);

	//left zhuzhi
	drawSingleCylinder(-5.0f, 1.0f, 0.0f);
	drawSingleCylinder(-5.0f, 1.5f, 0.0f);
	drawSingleCylinder(-5.0f, 3.0f, 0.0f);
	drawSingleCylinder(-5.0f, 3.5f, 0.0f);
	drawSingleCylinder(-5.0f, 5.0f, 0.0f);

	drawSingleCylinder(-7.0f, 1.0f, 0.0f);
	drawSingleCylinder(-7.0f, 1.5f, 0.0f);
	drawSingleCylinder(-7.0f, 3.0f, 0.0f);
	drawSingleCylinder(-7.0f, 3.5f, 0.0f);
	drawSingleCylinder(-7.0f, 5.0f, 0.0f);

	drawSingleCylinder(-5.0f, 1.0f, -2.0f);
	drawSingleCylinder(-5.0f, 1.5f, -2.0f);
	drawSingleCylinder(-5.0f, 3.0f, -2.0f);
	drawSingleCylinder(-5.0f, 3.5f, -2.0f);
	drawSingleCylinder(-5.0f, 5.0f, -2.0f);

	drawSingleCylinder(-7.0f, 1.0f, -2.0f);
	drawSingleCylinder(-7.0f, 1.5f, -2.0f);
	drawSingleCylinder(-7.0f, 3.0f, -2.0f);
	drawSingleCylinder(-7.0f, 3.5f, -2.0f);
	drawSingleCylinder(-7.0f, 5.0f, -2.0f);
}
void drawSeperateLine() {
	//right cuboid detail outline
	glPushMatrix();
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	//front
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.5f, 0.0f);
	glVertex3f(5.0f, 1.5f, 0.0f);

	//back
	glVertex3f(5.0f, 1.0f, -2.0f);
	glVertex3f(7.0f, 1.0f, -2.0f);
	glVertex3f(7.0f, 1.5f, -2.0f);
	glVertex3f(5.0f, 1.5f, -2.0f);

	//left
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 1.0f, -2.0f);
	glVertex3f(5.0f, 1.5f, -2.0f);
	glVertex3f(5.0f, 1.5f, 0.0f);

	//right
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, -2.0f);
	glVertex3f(7.0f, 1.5f, -2.0f);
	glVertex3f(7.0f, 1.5f, 0.0f);

	//top
	glVertex3f(5.0f, 1.5f, 0.0f);
	glVertex3f(7.0f, 1.5f, 0.0f);
	glVertex3f(7.0f, 1.5f, -2.0f);
	glVertex3f(5.0f, 1.5f, -2.0f);

	//bottom
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, -2.0f);
	glVertex3f(5.0f, 1.0f, -2.0f);

	glEnd();



	//right cuboid detail outline2
	glPushMatrix();
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	//front
	glVertex3f(5.0f, 3.0f, 0.0f);
	glVertex3f(7.0f, 3.0f, 0.0f);
	glVertex3f(7.0f, 3.5f, 0.0f);
	glVertex3f(5.0f, 3.5f, 0.0f);

	//back
	glVertex3f(5.0f, 3.0f, -2.0f);
	glVertex3f(7.0f, 3.0f, -2.0f);
	glVertex3f(7.0f, 3.5f, -2.0f);
	glVertex3f(5.0f, 3.5f, -2.0f);

	//left
	glVertex3f(5.0f, 3.0f, 0.0f);
	glVertex3f(5.0f, 3.0f, -2.0f);
	glVertex3f(5.0f, 3.5f, -2.0f);
	glVertex3f(5.0f, 3.5f, 0.0f);

	//right
	glVertex3f(7.0f, 3.0f, 0.0f);
	glVertex3f(7.0f, 3.0f, -2.0f);
	glVertex3f(7.0f, 3.5f, -2.0f);
	glVertex3f(7.0f, 3.5f, 0.0f);

	//top
	glVertex3f(5.0f, 3.5f, 0.0f);
	glVertex3f(7.0f, 3.5f, 0.0f);
	glVertex3f(7.0f, 3.5f, -2.0f);
	glVertex3f(5.0f, 3.5f, -2.0f);

	//bottom
	glVertex3f(5.0f, 3.0f, 0.0f);
	glVertex3f(7.0f, 3.0f, 0.0f);
	glVertex3f(7.0f, 3.0f, -2.0f);
	glVertex3f(5.0f, 3.0f, -2.0f);

	glEnd();

	//left cuboid detail outline
	glPushMatrix();
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	//front
	glVertex3f(-5.0f, 1.0f, 0.0f);
	glVertex3f(-7.0f, 1.0f, 0.0f);
	glVertex3f(-7.0f, 1.5f, 0.0f);
	glVertex3f(-5.0f, 1.5f, 0.0f);

	//back
	glVertex3f(-5.0f, 1.0f, -2.0f);
	glVertex3f(-7.0f, 1.0f, -2.0f);
	glVertex3f(-7.0f, 1.5f, -2.0f);
	glVertex3f(-5.0f, 1.5f, -2.0f);

	//left
	glVertex3f(-5.0f, 1.0f, 0.0f);
	glVertex3f(-5.0f, 1.0f, -2.0f);
	glVertex3f(-5.0f, 1.5f, -2.0f);
	glVertex3f(-5.0f, 1.5f, 0.0f);

	//right
	glVertex3f(-7.0f, 1.0f, 0.0f);
	glVertex3f(-7.0f, 1.0f, -2.0f);
	glVertex3f(-7.0f, 1.5f, -2.0f);
	glVertex3f(-7.0f, 1.5f, 0.0f);

	//top
	glVertex3f(-5.0f, 1.5f, 0.0f);
	glVertex3f(-7.0f, 1.5f, 0.0f);
	glVertex3f(-7.0f, 1.5f, -2.0f);
	glVertex3f(-5.0f, 1.5f, -2.0f);

	//bottom
	glVertex3f(-5.0f, 1.0f, 0.0f);
	glVertex3f(-7.0f, 1.0f, 0.0f);
	glVertex3f(-7.0f, 1.0f, -2.0f);
	glVertex3f(-5.0f, 1.0f, -2.0f);

	glEnd();

	//left cuboid detail outline2
	glPushMatrix();
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	//front
	glVertex3f(-5.0f, 3.0f, 0.0f);
	glVertex3f(-7.0f, 3.0f, 0.0f);
	glVertex3f(-7.0f, 3.5f, 0.0f);
	glVertex3f(-5.0f, 3.5f, 0.0f);

	//back
	glVertex3f(-5.0f, 3.0f, -2.0f);
	glVertex3f(-7.0f, 3.0f, -2.0f);
	glVertex3f(-7.0f, 3.5f, -2.0f);
	glVertex3f(-5.0f, 3.5f, -2.0f);

	//left
	glVertex3f(-5.0f, 3.0f, 0.0f);
	glVertex3f(-5.0f, 3.0f, -2.0f);
	glVertex3f(-5.0f, 3.5f, -2.0f);
	glVertex3f(-5.0f, 3.5f, 0.0f);

	//right
	glVertex3f(-7.0f, 3.0f, 0.0f);
	glVertex3f(-7.0f, 3.0f, -2.0f);
	glVertex3f(-7.0f, 3.5f, -2.0f);
	glVertex3f(-7.0f, 3.5f, 0.0f);

	//top
	glVertex3f(-5.0f, 3.5f, 0.0f);
	glVertex3f(-7.0f, 3.5f, 0.0f);
	glVertex3f(-7.0f, 3.5f, -2.0f);
	glVertex3f(-5.0f, 3.5f, -2.0f);

	//bottom
	glVertex3f(-5.0f, 3.0f, 0.0f);
	glVertex3f(-7.0f, 3.0f, 0.0f);
	glVertex3f(-7.0f, 3.0f, -2.0f);
	glVertex3f(-5.0f, 3.0f, -2.0f);

	glEnd();
}
void drawOutLine() {
	//right cuboid outlinne
	glPushMatrix();
	glColor3f(0, 0, 0);

	glBegin(GL_LINES);

	//front
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	//back
	glVertex3f(5.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 5.0f, -2.0f);
	glVertex3f(5.0f, 5.0f, -2.0f);

	//left
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, -2.0f);
	glVertex3f(5.0f, 5.0f, -2.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	//right
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 5.0f, -2.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);

	//top
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, -2.0f);
	glVertex3f(5.0f, 5.0f, -2.0f);

	//bottom
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(5.0f, 0.0f, -2.0f);

	glEnd();

	//right cuboid outline
	glBegin(GL_LINES);

	//front
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);

	//back
	glVertex3f(-5.0f, 0.0f, -2.0f);
	glVertex3f(-7.0f, 0.0f, -2.0f);
	glVertex3f(-7.0f, 5.0f, -2.0f);
	glVertex3f(-5.0f, 5.0f, -2.0f);

	//left
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, -2.0f);
	glVertex3f(-7.0f, 5.0f, -2.0f);
	glVertex3f(-7.0f, 5.0f, 0.0f);

	//right
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, -2.0f);
	glVertex3f(-5.0f, 5.0f, -2.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);

	//top
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(-7.0f, 5.0f, 0.0f);
	glVertex3f(-7.0f, 5.0f, -2.0f);
	glVertex3f(-5.0f, 5.0f, -2.0f);

	//bottom
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, -2.0f);
	glVertex3f(-5.0f, 0.0f, -2.0f);

	glEnd();
}
void drawConnector2() {
	//left connector
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-13.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 3.5f, 0.0f);
	glVertex3f(-7.0f, 4.0f, 0.0f);
	glVertex3f(-14.0f, 0.0f, 0.0f);

	//back
	glVertex3f(-13.0f, 0.0f, -0.5f);
	glVertex3f(-7.0f, 3.5f, -0.5f);
	glVertex3f(-7.0f, 4.0f, -0.5f);
	glVertex3f(-14.0f, 0.0f, -0.5f);

	//left
	glVertex3f(-14.0f, 0.0f, 0.0f);
	glVertex3f(-14.0f, 0.0f, -0.5f);
	glVertex3f(-13.0f, 0.0f, -0.5f);
	glVertex3f(-13.0f, 0.0f, 0.0f);

	//right
	glVertex3f(-7.0f, 3.5f, 0.0f);
	glVertex3f(-7.0f, 3.5f, -0.5f);
	glVertex3f(-7.0f, 4.0f, -0.5f);
	glVertex3f(-7.0f, 4.0f, 0.0f);

	//top
	glVertex3f(-7.0f, 4.0f, 0.0f);
	glVertex3f(-7.0f, 4.0f, -0.5f);
	glVertex3f(-13.0f, 0.0f, -0.5f);
	glVertex3f(-13.0f, 0.0f, 0.0f);

	//bottom
	glVertex3f(-14.0f, 0.0f, 0.0f);
	glVertex3f(-14.0f, 0.0f, -0.5f);
	glVertex3f(-7.0f, 3.5f, -0.5f);
	glVertex3f(-7.0f, 3.5f, 0.0f);

	glEnd();
	glPopMatrix();

	//left connector2
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-13.0f, 0.0f, -1.5f);
	glVertex3f(-7.0f, 3.5f, -1.5f);
	glVertex3f(-7.0f, 4.0f, -1.5f);
	glVertex3f(-14.0f, 0.0f, -1.5f);

	//back
	glVertex3f(-13.0f, 0.0f, -2.f);
	glVertex3f(-7.0f, 3.5f, -2.f);
	glVertex3f(-7.0f, 4.0f, -2.f);
	glVertex3f(-14.0f, 0.0f, -2.f);

	//left
	glVertex3f(-14.0f, 0.0f, -1.5f);
	glVertex3f(-14.0f, 0.0f, -2.f);
	glVertex3f(-13.0f, 0.0f, -2.f);
	glVertex3f(-13.0f, 0.0f, -1.5f);

	//right
	glVertex3f(-7.0f, 3.5f, -1.5f);
	glVertex3f(-7.0f, 3.5f, -2.f);
	glVertex3f(-7.0f, 4.0f, -2.f);
	glVertex3f(-7.0f, 4.0f, -1.5f);

	//top
	glVertex3f(-7.0f, 4.0f, -1.5f);
	glVertex3f(-7.0f, 4.0f, -2.f);
	glVertex3f(-13.0f, 0.0f, -2.f);
	glVertex3f(-13.0f, 0.0f, -1.5f);

	//bottom
	glVertex3f(-14.0f, 0.0f, -1.5f);
	glVertex3f(-14.0f, 0.0f, -2.f);
	glVertex3f(-7.0f, 3.5f, -2.f);
	glVertex3f(-7.0f, 3.5f, -1.5f);

	glEnd();
	glPopMatrix();

	//right connector
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(13.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 3.5f, 0.0f);
	glVertex3f(7.0f, 4.0f, 0.0f);
	glVertex3f(14.0f, 0.0f, 0.0f);

	//back
	glVertex3f(13.0f, 0.0f, -0.5f);
	glVertex3f(7.0f, 3.5f, -0.5f);
	glVertex3f(7.0f, 4.0f, -0.5f);
	glVertex3f(14.0f, 0.0f, -0.5f);

	//left
	glVertex3f(14.0f, 0.0f, 0.0f);
	glVertex3f(14.0f, 0.0f, -0.5f);
	glVertex3f(13.0f, 0.0f, -0.5f);
	glVertex3f(13.0f, 0.0f, 0.0f);

	//right
	glVertex3f(7.0f, 3.5f, 0.0f);
	glVertex3f(7.0f, 3.5f, -0.5f);
	glVertex3f(7.0f, 4.0f, -0.5f);
	glVertex3f(7.0f, 4.0f, 0.0f);

	//top
	glVertex3f(7.0f, 4.0f, 0.0f);
	glVertex3f(7.0f, 4.0f, -0.5f);
	glVertex3f(13.0f, 0.0f, -0.5f);
	glVertex3f(13.0f, 0.0f, 0.0f);

	//bottom
	glVertex3f(14.0f, 0.0f, 0.0f);
	glVertex3f(14.0f, 0.0f, -0.5f);
	glVertex3f(7.0f, 3.5f, -0.5f);
	glVertex3f(7.0f, 3.5f, 0.0f);

	glEnd();
	glPopMatrix();

	//right connector2
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(13.0f, 0.0f, -1.5f);
	glVertex3f(7.0f, 3.5f, -1.5f);
	glVertex3f(7.0f, 4.0f, -1.5f);
	glVertex3f(14.0f, 0.0f, -1.5f);

	//back
	glVertex3f(13.0f, 0.0f, -2.f);
	glVertex3f(7.0f, 3.5f, -2.f);
	glVertex3f(7.0f, 4.0f, -2.f);
	glVertex3f(14.0f, 0.0f, -2.f);

	//left
	glVertex3f(14.0f, 0.0f, -1.5f);
	glVertex3f(14.0f, 0.0f, -2.f);
	glVertex3f(13.0f, 0.0f, -2.f);
	glVertex3f(13.0f, 0.0f, -1.5f);

	//right
	glVertex3f(7.0f, 3.5f, -1.5f);
	glVertex3f(7.0f, 3.5f, -2.f);
	glVertex3f(7.0f, 4.0f, -2.f);
	glVertex3f(7.0f, 4.0f, -1.5f);

	//top
	glVertex3f(7.0f, 4.0f, -1.5f);
	glVertex3f(7.0f, 4.0f, -2.f);
	glVertex3f(13.0f, 0.0f, -2.f);
	glVertex3f(13.0f, 0.0f, -1.5f);

	//bottom
	glVertex3f(14.0f, 0.0f, -1.5f);
	glVertex3f(14.0f, 0.0f, -2.f);
	glVertex3f(7.0f, 3.5f, -2.f);
	glVertex3f(7.0f, 3.5f, -1.5f);

	glEnd();
	glPopMatrix();
}
void drawConnectorAtConnector() {
	//left connector
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-10.0f, 0.5f, -0.01f);
	glVertex3f(-9.7f, 0.5f, -0.01f);
	glVertex3f(-9.7f, 2.3f, -0.01f);
	glVertex3f(-10.0f, 2.0f, -0.01f);

	//back
	glVertex3f(-10.0f, 0.5f, -0.49f);
	glVertex3f(-9.7f, 0.5f, -0.49f);
	glVertex3f(-9.7f, 2.3f, -0.49f);
	glVertex3f(-10.0f, 2.0f, -0.49f);

	//left
	glVertex3f(-10.0f, 0.5f, -0.01f);
	glVertex3f(-10.0f, 0.5f, -0.49f);
	glVertex3f(-10.0f, 2.0f, -0.49f);
	glVertex3f(-10.0f, 2.0f, -0.01f);

	//right
	glVertex3f(-9.7f, 0.5f, -0.01f);
	glVertex3f(-9.7f, 0.5f, -0.49f);
	glVertex3f(-9.7f, 2.0f, -0.49f);
	glVertex3f(-9.7f, 2.0f, -0.01f);

	glEnd();
	glPopMatrix();

	//left connector2
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-9.0f, 0.5f, -0.01f);
	glVertex3f(-8.7f, 0.5f, -0.01f);
	glVertex3f(-8.7f, 2.6f, -0.01f);
	glVertex3f(-9.0f, 2.3f, -0.01f);

	//back
	glVertex3f(-9.0f, 0.5f, -0.49f);
	glVertex3f(-8.7f, 0.5f, -0.49f);
	glVertex3f(-8.7f, 2.6f, -0.49f);
	glVertex3f(-9.0f, 2.3f, -0.49f);

	//left
	glVertex3f(-9.0f, 0.5f, -0.01f);
	glVertex3f(-9.0f, 0.5f, -0.49f);
	glVertex3f(-9.0f, 2.3f, -0.49f);
	glVertex3f(-9.0f, 2.3f, -0.01f);

	//right
	glVertex3f(-8.7f, 0.5f, -0.01f);
	glVertex3f(-8.7f, 0.5f, -0.49f);
	glVertex3f(-8.7f, 2.3f, -0.49f);
	glVertex3f(-8.7f, 2.3f, -0.01f);

	glEnd();
	glPopMatrix();

	//left connector3
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-8.0f, 0.5f, -0.01f);
	glVertex3f(-7.7f, 0.5f, -0.01f);
	glVertex3f(-7.7f, 3.2f, -0.01f);
	glVertex3f(-8.0f, 2.9f, -0.01f);

	//back
	glVertex3f(-8.0f, 0.5f, -0.49f);
	glVertex3f(-7.7f, 0.5f, -0.49f);
	glVertex3f(-7.7f, 3.2f, -0.49f);
	glVertex3f(-8.0f, 2.9f, -0.49f);

	//left
	glVertex3f(-8.0f, 0.5f, -0.01f);
	glVertex3f(-8.0f, 0.5f, -0.49f);
	glVertex3f(-8.0f, 2.9f, -0.49f);
	glVertex3f(-8.0f, 2.9f, -0.01f);

	//right
	glVertex3f(-7.7f, 0.5f, -0.01f);
	glVertex3f(-7.7f, 0.5f, -0.49f);
	glVertex3f(-7.7f, 2.9f, -0.49f);
	glVertex3f(-7.7f, 2.9f, -0.01f);

	glEnd();
	glPopMatrix();

	//left connector4
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-10.0f, 0.5f, -1.51f);
	glVertex3f(-9.7f, 0.5f, -1.51f);
	glVertex3f(-9.7f, 2.3f, -1.51f);
	glVertex3f(-10.0f, 2.0f, -1.51f);

	//back
	glVertex3f(-10.0f, 0.5f, -1.99f);
	glVertex3f(-9.7f, 0.5f, -1.99f);
	glVertex3f(-9.7f, 2.3f, -1.99f);
	glVertex3f(-10.0f, 2.0f, -1.99f);

	//left
	glVertex3f(-10.0f, 0.5f, -1.51f);
	glVertex3f(-10.0f, 0.5f, -1.99f);
	glVertex3f(-10.0f, 2.0f, -1.99f);
	glVertex3f(-10.0f, 2.0f, -1.51f);

	//right
	glVertex3f(-9.7f, 0.5f, -1.51f);
	glVertex3f(-9.7f, 0.5f, -1.99f);
	glVertex3f(-9.7f, 2.0f, -1.99f);
	glVertex3f(-9.7f, 2.0f, -1.51f);

	glEnd();
	glPopMatrix();

	//left connector5
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-9.0f, 0.5f, -1.51f);
	glVertex3f(-8.7f, 0.5f, -1.51f);
	glVertex3f(-8.7f, 2.6f, -1.51f);
	glVertex3f(-9.0f, 2.3f, -1.51f);

	//back
	glVertex3f(-9.0f, 0.5f, -1.99f);
	glVertex3f(-8.7f, 0.5f, -1.99f);
	glVertex3f(-8.7f, 2.6f, -1.99f);
	glVertex3f(-9.0f, 2.3f, -1.99f);

	//left
	glVertex3f(-9.0f, 0.5f, -1.51f);
	glVertex3f(-9.0f, 0.5f, -1.99f);
	glVertex3f(-9.0f, 2.3f, -1.99f);
	glVertex3f(-9.0f, 2.3f, -1.51f);

	//right
	glVertex3f(-8.7f, 0.5f, -1.51f);
	glVertex3f(-8.7f, 0.5f, -1.99f);
	glVertex3f(-8.7f, 2.3f, -1.99f);
	glVertex3f(-8.7f, 2.3f, -1.51f);

	glEnd();
	glPopMatrix();

	//left connector6
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-8.0f, 0.5f, -1.51f);
	glVertex3f(-7.7f, 0.5f, -1.51f);
	glVertex3f(-7.7f, 3.2f, -1.51f);
	glVertex3f(-8.0f, 2.9f, -1.51f);

	//back
	glVertex3f(-8.0f, 0.5f, -1.99f);
	glVertex3f(-7.7f, 0.5f, -1.99f);
	glVertex3f(-7.7f, 3.2f, -1.99f);
	glVertex3f(-8.0f, 2.9f, -1.99f);

	//left
	glVertex3f(-8.0f, 0.5f, -1.51f);
	glVertex3f(-8.0f, 0.5f, -1.99f);
	glVertex3f(-8.0f, 2.9f, -1.99f);
	glVertex3f(-8.0f, 2.9f, -1.51f);

	//right
	glVertex3f(-7.7f, 0.5f, -1.51f);
	glVertex3f(-7.7f, 0.5f, -1.99f);
	glVertex3f(-7.7f, 2.9f, -1.99f);
	glVertex3f(-7.7f, 2.9f, -1.51f);

	glEnd();
	glPopMatrix();

	//right connector
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(10.0f, 0.5f, -0.01f);
	glVertex3f(9.7f, 0.5f, -0.01f);
	glVertex3f(9.7f, 2.3f, -0.01f);
	glVertex3f(10.0f, 2.0f, -0.01f);

	//back
	glVertex3f(10.0f, 0.5f, -0.49f);
	glVertex3f(9.7f, 0.5f, -0.49f);
	glVertex3f(9.7f, 2.3f, -0.49f);
	glVertex3f(10.0f, 2.0f, -0.49f);

	//left
	glVertex3f(10.0f, 0.5f, -0.01f);
	glVertex3f(10.0f, 0.5f, -0.49f);
	glVertex3f(10.0f, 2.0f, -0.49f);
	glVertex3f(10.0f, 2.0f, -0.01f);

	//right
	glVertex3f(9.7f, 0.5f, -0.01f);
	glVertex3f(9.7f, 0.5f, -0.49f);
	glVertex3f(9.7f, 2.0f, -0.49f);
	glVertex3f(9.7f, 2.0f, -0.01f);

	glEnd();
	glPopMatrix();

	//right connector2
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(9.0f, 0.5f, -0.01f);
	glVertex3f(8.7f, 0.5f, -0.01f);
	glVertex3f(8.7f, 2.6f, -0.01f);
	glVertex3f(9.0f, 2.3f, -0.01f);

	//back
	glVertex3f(9.0f, 0.5f, -0.49f);
	glVertex3f(8.7f, 0.5f, -0.49f);
	glVertex3f(8.7f, 2.6f, -0.49f);
	glVertex3f(9.0f, 2.3f, -0.49f);

	//left
	glVertex3f(9.0f, 0.5f, -0.01f);
	glVertex3f(9.0f, 0.5f, -0.49f);
	glVertex3f(9.0f, 2.3f, -0.49f);
	glVertex3f(9.0f, 2.3f, -0.01f);

	//right
	glVertex3f(8.7f, 0.5f, -0.01f);
	glVertex3f(8.7f, 0.5f, -0.49f);
	glVertex3f(8.7f, 2.3f, -0.49f);
	glVertex3f(8.7f, 2.3f, -0.01f);

	glEnd();
	glPopMatrix();

	//right connector3
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(8.0f, 0.5f, -0.01f);
	glVertex3f(7.7f, 0.5f, -0.01f);
	glVertex3f(7.7f, 3.2f, -0.01f);
	glVertex3f(8.0f, 2.9f, -0.01f);

	//back
	glVertex3f(8.0f, 0.5f, -0.49f);
	glVertex3f(7.7f, 0.5f, -0.49f);
	glVertex3f(7.7f, 3.2f, -0.49f);
	glVertex3f(8.0f, 2.9f, -0.49f);

	//left
	glVertex3f(8.0f, 0.5f, -0.01f);
	glVertex3f(8.0f, 0.5f, -0.49f);
	glVertex3f(8.0f, 2.9f, -0.49f);
	glVertex3f(8.0f, 2.9f, -0.01f);

	//right
	glVertex3f(7.7f, 0.5f, -0.01f);
	glVertex3f(7.7f, 0.5f, -0.49f);
	glVertex3f(7.7f, 2.9f, -0.49f);
	glVertex3f(7.7f, 2.9f, -0.01f);

	glEnd();
	glPopMatrix();

	//right connector4
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(10.0f, 0.5f, -1.51f);
	glVertex3f(9.7f, 0.5f, -1.51f);
	glVertex3f(9.7f, 2.3f, -1.51f);
	glVertex3f(10.0f, 2.0f, -1.51f);

	//back
	glVertex3f(10.0f, 0.5f, -1.99f);
	glVertex3f(9.7f, 0.5f, -1.99f);
	glVertex3f(9.7f, 2.3f, -1.99f);
	glVertex3f(10.0f, 2.0f, -1.99f);

	//left
	glVertex3f(10.0f, 0.5f, -1.51f);
	glVertex3f(10.0f, 0.5f, -1.99f);
	glVertex3f(10.0f, 2.0f, -1.99f);
	glVertex3f(10.0f, 2.0f, -1.51f);

	//right
	glVertex3f(9.7f, 0.5f, -1.51f);
	glVertex3f(9.7f, 0.5f, -1.99f);
	glVertex3f(9.7f, 2.0f, -1.99f);
	glVertex3f(9.7f, 2.0f, -1.51f);

	glEnd();
	glPopMatrix();

	//right connector5
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(9.0f, 0.5f, -1.51f);
	glVertex3f(8.7f, 0.5f, -1.51f);
	glVertex3f(8.7f, 2.6f, -1.51f);
	glVertex3f(9.0f, 2.3f, -1.51f);

	//back
	glVertex3f(9.0f, 0.5f, -1.99f);
	glVertex3f(8.7f, 0.5f, -1.99f);
	glVertex3f(8.7f, 2.6f, -1.99f);
	glVertex3f(9.0f, 2.3f, -1.99f);

	//left
	glVertex3f(9.0f, 0.5f, -1.51f);
	glVertex3f(9.0f, 0.5f, -1.99f);
	glVertex3f(9.0f, 2.3f, -1.99f);
	glVertex3f(9.0f, 2.3f, -1.51f);

	//right
	glVertex3f(8.7f, 0.5f, -1.51f);
	glVertex3f(8.7f, 0.5f, -1.99f);
	glVertex3f(8.7f, 2.3f, -1.99f);
	glVertex3f(8.7f, 2.3f, -1.51f);

	glEnd();
	glPopMatrix();

	//right connector6
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(8.0f, 0.5f, -1.51f);
	glVertex3f(7.7f, 0.5f, -1.51f);
	glVertex3f(7.7f, 3.2f, -1.51f);
	glVertex3f(8.0f, 2.9f, -1.51f);

	//back
	glVertex3f(8.0f, 0.5f, -1.99f);
	glVertex3f(7.7f, 0.5f, -1.99f);
	glVertex3f(7.7f, 3.2f, -1.99f);
	glVertex3f(8.0f, 2.9f, -1.99f);

	//left
	glVertex3f(8.0f, 0.5f, -1.51f);
	glVertex3f(8.0f, 0.5f, -1.99f);
	glVertex3f(8.0f, 2.9f, -1.99f);
	glVertex3f(8.0f, 2.9f, -1.51f);

	//right
	glVertex3f(7.7f, 0.5f, -1.51f);
	glVertex3f(7.7f, 0.5f, -1.99f);
	glVertex3f(7.7f, 2.9f, -1.99f);
	glVertex3f(7.7f, 2.9f, -1.51f);

	glEnd();
	glPopMatrix();
}
void drawStarField(float sceneWidth, float sceneHeight, int numStars, int seed) {
	srand(seed);

	for (int i = 0; i < numStars; i++) {
		float x = (rand() % 1000 / 1000.0f) * sceneWidth - (sceneWidth / 2.0f);
		float y = (rand() % 1000 / 1000.0f) * sceneHeight;

		float starSize = 1.0f + (rand() % 3);
		float brightness = 0.6f + (rand() % 100 / 500.0f);

		glPointSize(starSize);
		glBegin(GL_POINTS);
		glColor3f(brightness, brightness, brightness);
		glVertex2f(x, y);
		glEnd();
	}
}
void drawBaseOutsideConnector() {
	//left connector
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(-15.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.5f, 0.0f);
	glVertex3f(-15.0f, 0.5f, 0.0f);

	//back
	glVertex3f(-15.0f, 0.0f, -2.0f);
	glVertex3f(-8.0f, 0.0f, -2.0f);
	glVertex3f(-8.0f, 0.5f, -2.0f);
	glVertex3f(-15.0f, 0.5f, -2.0f);

	//left
	glVertex3f(-15.0f, 0.0f, 0.0f);
	glVertex3f(-15.0f, 0.0f, -2.0f);
	glVertex3f(-15.0f, 0.5f, -2.0f);
	glVertex3f(-15.0f, 0.5f, 0.0f);

	//right
	glVertex3f(-8.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.0f, -2.0f);
	glVertex3f(-8.0f, 0.5f, -2.0f);
	glVertex3f(-8.0f, 0.5f, 0.0f);

	//top
	glVertex3f(-15.0f, 0.5f, 0.0f);
	glVertex3f(-8.0f, 0.5f, 0.0f);
	glVertex3f(-8.0f, 0.5f, -2.0f);
	glVertex3f(-15.0f, 0.5f, -2.0f);

	//bottom
	glVertex3f(-15.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.0f, 0.0f);
	glVertex3f(-8.0f, 0.0f, -2.0f);
	glVertex3f(-15.0f, 0.0f, -2.0f);

	glEnd();

	glPopMatrix();

	//right connector
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, -0.5f, 0.0f);
	glBegin(GL_QUADS);

	//front
	glVertex3f(15.0f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.5f, 0.0f);
	glVertex3f(15.0f, 0.5f, 0.0f);

	//back
	glVertex3f(15.0f, 0.0f, -2.0f);
	glVertex3f(8.0f, 0.0f, -2.0f);
	glVertex3f(8.0f, 0.5f, -2.0f);
	glVertex3f(15.0f, 0.5f, -2.0f);

	//left
	glVertex3f(15.0f, 0.0f, 0.0f);
	glVertex3f(15.0f, 0.0f, -2.0f);
	glVertex3f(15.0f, 0.5f, -2.0f);
	glVertex3f(15.0f, 0.5f, 0.0f);

	//right
	glVertex3f(8.0f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, -2.0f);
	glVertex3f(8.0f, 0.5f, -2.0f);
	glVertex3f(8.0f, 0.5f, 0.0f);

	//top
	glVertex3f(15.0f, 0.5f, 0.0f);
	glVertex3f(8.0f, 0.5f, 0.0f);
	glVertex3f(8.0f, 0.5f, -2.0f);	
	glVertex3f(15.0f, 0.5f, -2.0f);

	//bottom
	glVertex3f(15.0f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, -2.0f);
	glVertex3f(15.0f, 0.0f, -2.0f);

	glEnd();

	glPopMatrix();
}

void drawBaseConnector(){
	//left connector
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(-4.0f, -0.5f, 0.0f);
	glRotatef(leftConnectorRotationAngle, 0.0f, 0.0f, 1.0f); 
	glTranslatef(4.0f, 0.0f, 0.0f); 
	glBegin(GL_QUADS);

	//front
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.5f, 0.0f);
	glVertex3f(-4.0f, 0.5f, 0.0f);

	//back
	glVertex3f(-4.0f, 0.0f, -2.0f);
	glVertex3f(.0f, 0.0f, -2.0f);
	glVertex3f(.0f, 0.5f, -2.0f);
	glVertex3f(-4.0f, 0.5f, -2.0f);

	//left
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(-4.0f, 0.0f, -2.0f);
	glVertex3f(-4.0f, 0.5f, -2.0f);
	glVertex3f(-4.0f, 0.5f, 0.0f);

	//right
	glVertex3f(.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, -2.0f);
	glVertex3f(.0f, 0.5f, -2.0f);
	glVertex3f(.0f, 0.5f, 0.0f);

	//top
	glVertex3f(-4.0f, 0.5f, 0.0f);
	glVertex3f(.0f, 0.5f, 0.0f);
	glVertex3f(.0f, 0.5f, -2.0f);
	glVertex3f(-4.0f, 0.5f, -2.0f);

	//bottom
	glVertex3f(-4.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, -2.0f);
	glVertex3f(-4.0f, 0.0f, -2.0f);

	glEnd();

	glPopMatrix();

	//right connector
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(4.0f, -0.5f, 0.0f); 
	glRotatef(rightConnectorRotationAngle, 0.0f, 0.0f, 1.0f); 
	glTranslatef(-4.0f, 0.0f, 0.0f); 
	glBegin(GL_QUADS);

	//front
	glVertex3f(4.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.5f, 0.0f);
	glVertex3f(4.0f, 0.5f, 0.0f);

	//back
	glVertex3f(4.0f, 0.0f, -2.0f);
	glVertex3f(.0f, 0.0f, -2.0f);
	glVertex3f(.0f, 0.5f, -2.0f);
	glVertex3f(4.0f, 0.5f, -2.0f);

	//left
	glVertex3f(4.0f, 0.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, -2.0f);
	glVertex3f(4.0f, 0.5f, -2.0f);
	glVertex3f(4.0f, 0.5f, 0.0f);

	//right
	glVertex3f(.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, -2.0f);
	glVertex3f(.0f, 0.5f, -2.0f);
	glVertex3f(.0f, 0.5f, 0.0f);

	//top
	glVertex3f(4.0f, 0.5f, 0.0f);
	glVertex3f(.0f, 0.5f, 0.0f);
	glVertex3f(.0f, 0.5f, -2.0f);
	glVertex3f(4.0f, 0.5f, -2.0f);

	//bottom
	glVertex3f(4.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, 0.0f);
	glVertex3f(.0f, 0.0f, -2.0f);
	glVertex3f(4.0f, 0.0f, -2.0f);

	glEnd();

	glPopMatrix();
}

void drawBase() {
	//right base
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(0, -2.0, 0);
	glBegin(GL_QUADS);

	glVertex3f(4.0f, 0.0f, 1.0f);
	glVertex3f(8.0f, 0.0f, 1.0f);
	glVertex3f(8.0f, 2.0f, 1.0f);
	glVertex3f(4.0f, 2.0f, 1.0f);

	//back
	glVertex3f(4.0f, 0.0f, -3.0f);
	glVertex3f(8.0f, 0.0f, -3.0f);
	glVertex3f(8.0f, 2.0f, -3.0f);
	glVertex3f(4.0f, 2.0f, -3.0f);

	//left
	glVertex3f(4.0f, 0.0f, 1.0f);
	glVertex3f(4.0f, 0.0f, -3.0f);
	glVertex3f(4.0f, 2.0f, -3.0f);
	glVertex3f(4.0f, 2.0f, 1.0f);

	//right
	glVertex3f(8.0f, 0.0f, 1.0f);
	glVertex3f(8.0f, 0.0f, -3.0f);
	glVertex3f(8.0f, 2.0f, -3.0f);
	glVertex3f(8.0f, 2.0f, 1.0f);

	//top
	glVertex3f(4.0f, 2.0f, 1.0f);
	glVertex3f(8.0f, 2.0f, 1.0f);
	glVertex3f(8.0f, 2.0f, -3.0f);
	glVertex3f(4.0f, 2.0f, -3.0f);

	//bottom
	glVertex3f(4.0f, 0.0f, 1.0f);
	glVertex3f(8.0f, 0.0f, 1.0f);
	glVertex3f(8.0f, 0.0f, -3.0f);
	glVertex3f(4.0f, 0.0f, -3.0f);

	glEnd();

	glPopMatrix();

	//left base
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(0, -2.0, 0);
	glBegin(GL_QUADS);

	glVertex3f(-4.0f, 0.0f, 1.0f);
	glVertex3f(-8.0f, 0.0f, 1.0f);
	glVertex3f(-8.0f, 2.0f, 1.0f);
	glVertex3f(-4.0f, 2.0f, 1.0f);

	//back
	glVertex3f(-4.0f, 0.0f, -3.0f);
	glVertex3f(-8.0f, 0.0f, -3.0f);
	glVertex3f(-8.0f, 2.0f, -3.0f);
	glVertex3f(-4.0f, 2.0f, -3.0f);

	//left
	glVertex3f(-4.0f, 0.0f, 1.0f);
	glVertex3f(-4.0f, 0.0f, -3.0f);
	glVertex3f(-4.0f, 2.0f, -3.0f);
	glVertex3f(-4.0f, 2.0f, 1.0f);

	//right
	glVertex3f(-8.0f, 0.0f, 1.0f);
	glVertex3f(-8.0f, 0.0f, -3.0f);
	glVertex3f(-8.0f, 2.0f, -3.0f);
	glVertex3f(-8.0f, 2.0f, 1.0f);

	//top
	glVertex3f(-4.0f, 2.0f, 1.0f);
	glVertex3f(-8.0f, 2.0f, 1.0f);
	glVertex3f(-8.0f, 2.0f, -3.0f);
	glVertex3f(-4.0f, 2.0f, -3.0f);

	//bottom
	glVertex3f(-4.0f, 0.0f, 1.0f);
	glVertex3f(-8.0f, 0.0f, 1.0f);
	glVertex3f(-8.0f, 0.0f, -3.0f);
	glVertex3f(-4.0f, 0.0f, -3.0f);

	glEnd();

	glPopMatrix();
}
void drawConnector() {
	glPushMatrix();
	glColor3f(0.4f, 0.2f, 0.0f);
	glTranslatef(0, 4.0f, 0);

	glBegin(GL_QUADS);

	//front
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.5f, 0.0f);
	glVertex3f(-7.0f, 0.5f, 0.0f);

	//back
	glVertex3f(-7.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 0.5f, -2.0f);
	glVertex3f(-7.0f, 0.5f, -2.0f);

	//left
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, -2.0f);
	glVertex3f(-7.0f, 0.5f, -2.0f);
	glVertex3f(-7.0f, 0.5f, 0.0f);

	//right
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 0.5f, -2.0f);
	glVertex3f(7.0f, 0.5f, 0.0f);

	//top
	glVertex3f(-7.0f, 0.5f, 0.0f);
	glVertex3f(7.0f, 0.5f, 0.0f);
	glVertex3f(7.0f, 0.5f, -2.0f);
	glVertex3f(-7.0f, 0.5f, -2.0f);

	//bottom
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(-7.0f, 0.0f, -2.0f);

	glEnd();

	glPopMatrix();
}

void drawZhuZhi() {
	//right zhuzhi
	glPushMatrix();
		cylinder = gluNewQuadric();
		glColor3f(1, 1, 1);
		glTranslatef(5.0f, 0.0f, 0);
		glRotatef(-90.0, 1.0f, 0, 0);
		gluCylinder(cylinder, 0.2, 0.2f, 5.0f, 50, 50);
		glPushMatrix();
			glTranslatef(0,0, 6.0f); 
			glRotatef(-180.0, 1.0f, 0, 0);
			gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50); 
		glPopMatrix();
	glPopMatrix();

	//behind right zhuzhi
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(7.0f, 0.0f, -2.0f);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	//right zhuzhi2
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(7.0f, 0.0f, 0);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.0f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	//behind right zhuzhi2
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(5.0f, 0.0f, -2.0f);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	//left zhuzhi
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(-5.0f, 0.0f, 0);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.0f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	//behind left zhuzhi
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(-5.0f, 0.0f, -2.0f);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	//left zhuzhi2
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(-7.0f, 0.0f, 0);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.0f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();

	//behind left zhuzhi2
	glPushMatrix();
	cylinder = gluNewQuadric();
	glColor3f(1, 1, 1);
	glTranslatef(-7.0f, 0.0f, -2.0f);
	glRotatef(-90.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0.2, 0.2f, 5.f, 50, 50);
	glPushMatrix();
	glTranslatef(0, 0, 6.0f);
	glRotatef(-180.0, 1.0f, 0, 0);
	gluCylinder(cylinder, 0, 0.2f, 1.0f, 50, 50);
	glPopMatrix();
	glPopMatrix();
}

void cuboid() {
	//right cuboid
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f); 

	glBegin(GL_QUADS);

	//front
	glVertex3f(5.0f, 0.0f, 0.0f);   
	glVertex3f(7.0f, 0.0f, 0.0f);  
	glVertex3f(7.0f, 5.0f, 0.0f);  
	glVertex3f(5.0f, 5.0f, 0.0f);  

	//back
	glVertex3f(5.0f, 0.0f, -2.0f); 
	glVertex3f(7.0f, 0.0f, -2.0f); 
	glVertex3f(7.0f, 5.0f, -2.0f);  
	glVertex3f(5.0f, 5.0f, -2.0f);

	//left
	glVertex3f(5.0f, 0.0f, 0.0f);  
	glVertex3f(5.0f, 0.0f, -2.0f); 
	glVertex3f(5.0f, 5.0f, -2.0f); 
	glVertex3f(5.0f, 5.0f, 0.0f);  

	//right
	glVertex3f(7.0f, 0.0f, 0.0f);  
	glVertex3f(7.0f, 0.0f, -2.0f);
	glVertex3f(7.0f, 5.0f, -2.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);  

	//top
	glVertex3f(5.0f, 5.0f, 0.0f);   
	glVertex3f(7.0f, 5.0f, 0.0f); 
	glVertex3f(7.0f, 5.0f, -2.0f); 
	glVertex3f(5.0f, 5.0f, -2.0f); 

	//bottom
	glVertex3f(5.0f, 0.0f, 0.0f);  
	glVertex3f(7.0f, 0.0f, 0.0f);  
	glVertex3f(7.0f, 0.0f, -2.0f);  
	glVertex3f(5.0f, 0.0f, -2.0f);  

	glEnd();

	glPopMatrix();


	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);

	//left cuboid
	glBegin(GL_QUADS);

	//front
	glVertex3f(-5.0f, 0.0f, 0.0f);  
	glVertex3f(-7.0f, 0.0f, 0.0f);  
	glVertex3f(-7.0f, 5.0f, 0.0f);   
	glVertex3f(-5.0f, 5.0f, 0.0f);   

	//back
	glVertex3f(-5.0f, 0.0f, -2.0f);  
	glVertex3f(-7.0f, 0.0f, -2.0f); 
	glVertex3f(-7.0f, 5.0f, -2.0f); 
	glVertex3f(-5.0f, 5.0f, -2.0f);

	//left
	glVertex3f(-7.0f, 0.0f, 0.0f);   
	glVertex3f(-7.0f, 0.0f, -2.0f); 
	glVertex3f(-7.0f, 5.0f, -2.0f); 
	glVertex3f(-7.0f, 5.0f, 0.0f);  

	//right
	glVertex3f(-5.0f, 0.0f, 0.0f);   
	glVertex3f(-5.0f, 0.0f, -2.0f);  
	glVertex3f(-5.0f, 5.0f, -2.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);  

	//top
	glVertex3f(-5.0f, 5.0f, 0.0f);  
	glVertex3f(-7.0f, 5.0f, 0.0f);  
	glVertex3f(-7.0f, 5.0f, -2.0f);  
	glVertex3f(-5.0f, 5.0f, -2.0f);  

	//bottom
	glVertex3f(-5.0f, 0.0f, 0.0f);  
	glVertex3f(-7.0f, 0.0f, 0.0f);  
	glVertex3f(-7.0f, 0.0f, -2.0f);
	glVertex3f(-5.0f, 0.0f, -2.0f);  

	glEnd();
	
	glPopMatrix();
	drawConnector();
	drawBaseConnector();
	drawBase();
}
void drawBaseUnderBridge(float width, float depth, float yPosition) {
	glPushMatrix();
	glColor3f(0,0,1);
	glBegin(GL_QUADS);

	// Bottom face
	glVertex3f(-width / 2, yPosition, -depth / 2); 
	glVertex3f(width / 2, yPosition, -depth / 2);  
	glVertex3f(width / 2, yPosition, depth / 2);   
	glVertex3f(-width / 2, yPosition, depth / 2); 

	glEnd();
	glPopMatrix();
}
//void setCamera() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glTranslatef(camX, camY, camZ);
//
//	switch (cameraMode) {
//	case 0: 
//		gluPerspective(45.0, 1.0, 0.1, 100.0);
//		break;
//
//	case 1: 
//		glOrtho(-10.0, 10.0, -10.0, 10.0, 0.1, 100.0);
//		break;
//
//	default:
//		gluPerspective(45.0, 1.0, 0.1, 100.0);
//		break;
//	}
//
//	glMatrixMode(GL_MODELVIEW);
//}

void display()
{
	////modify camera
	glMatrixMode(GL_PROJECTION); //switch matrix state to modify camera
	glLoadIdentity(); // reset the matrix
	////glOrtho(left, right, bottom, top, near, far);
	////glOrtho(camLeft, camRight, camBottom, camTop, camNear, camFar); // apply new matrix

	//gluPerspective(45.0, 1.0, 0.1, 100.0);
	if (isPerspective) {
		gluPerspective(45.0, 1.0, 0.1, 100.0);
	}
	else {
		glOrtho(-10.0, 10.0, -10.0, 10.0, 0.1, 100.0);
	}
	/*setCamera();*/
	glTranslatef(camX, camY, camZ);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
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

		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_LINE);
		glColor3f(1, 1, 1);
		//gluSphere(sphere, 0.5, 10, 10);

		cylinder = gluNewQuadric();
		gluQuadricDrawStyle(cylinder, GLU_LINE);
		glColor3f(1, 1, 1);
		//gluCylinder(GLUquadric obj *, baseRadius,topRadius, height, slices, stacks);
		gluCylinder(cylinder, 0, 0.2f, 0.6f, slices, stacks);
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

		drawBaseConnector();
		drawBaseOutsideConnector();
		drawConnector2();
		drawCylinderSeperateLine();
		drawSeperateLine();
		drawOutLine();
		drawZhuZhi();
		cuboid();
		drawConnector();
		drawBase();
		drawConnectorAtConnector();
		drawStarField(50.0f, 10.0f, 100, 42);
		drawBaseUnderBridge(50.0f, -10.0f, -2.0f);
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

	glEnable(GL_DEPTH_TEST);

	

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