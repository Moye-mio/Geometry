#include <windows.h>
#define GLEW_STATIC
#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

int G_Width = 400;
int G_Height = 400;
int G_ChoosedPoint = -1;
float G_X = 0.0f;
float G_Y = 0.0f;
float G_LineWidth = 3.0f;
float G_PointSize = 9.0f;

#define POINTS_NUM	6
#define POINT_POS	3

std::array<std::array<float, POINT_POS>, POINTS_NUM> G_ControlPoints;
static std::array<std::array<float, POINT_POS>, POINTS_NUM> G_OriginalPoints =
{{	{-0.8f, 0.8f, 0.0f},
	{-0.8f, 0.0f, 0.0f},
	{0.0f, -0.0f, 0.0f},
	{0.0f, -0.0f, 0.0f},
	{0.8f, -0.0f, 0.0f},
	{0.8f, -0.8f, 0.0f}
}};

void resetControlPoints()
{
	for (int i = 0; i < POINTS_NUM; i++)
		for (int k = 0; k < POINT_POS; k++)
			G_ControlPoints[i][k] = G_OriginalPoints[i][k];
}

void keyboardCallback(GLFWwindow* vWindow, int vKey, int vScancode, int vAction, int vMode)
{
	if (vKey == GLFW_KEY_ESCAPE && vAction == GLFW_PRESS)
		glfwSetWindowShouldClose(vWindow, GL_TRUE);
	else if (vKey == GLFW_KEY_LEFT)
		G_X -= 0.01;
	else if (vKey == GLFW_KEY_RIGHT)
		G_X += 0.01;
	else if (vKey == GLFW_KEY_UP)
		G_Y += 0.01;
	else if (vKey == GLFW_KEY_DOWN)
		G_Y -= 0.01;
}

void windowPos2CoordiatePos(GLFWwindow* vWindow, double vPosX, double vPosY, double* voX, double* voY)
{
	int Width, Height;
	glfwGetWindowSize(vWindow, &Width, &Height);

	vPosX -= (Width - G_Width) / 2;
	*voX = vPosX / (G_Width / 2) - 1.0;

	vPosY -= (Height - G_Height) / 2;
	*voY = 1.0 - vPosY / (G_Height / 2);
}

void coordiatePos2WindowPos(GLFWwindow* vWindow, double vX, double vY, double* voPosX, double* voPosY)
{
	int Width, Height;
	glfwGetWindowSize(vWindow, &Width, &Height);

	*voPosX = (vX + 1.0) * (G_Width / 2);
	*voPosY = (1.0 - vY) * (G_Height / 2);

	*voPosX += (Width - G_Width) / 2;
	*voPosY += (Height - G_Height) / 2;
}

bool isPointPosValid(GLFWwindow* vWindow, double vPosX, double vPosY, double vX, double vY, double vPointSize)
{
	double WinPosX, WinPosY;
	coordiatePos2WindowPos(vWindow, vX, vY, &WinPosX, &WinPosY);

	if (vPosX >= WinPosX - vPointSize && vPosX <= WinPosX + vPointSize && vPosY >= WinPosY - vPointSize && vPosY <= WinPosY + vPointSize)
		return true;

	return false;
}

void mouseButtonCallback(GLFWwindow* vWindow, int vButton, int vAction, int vMode)
{
	double WinPosX = 0, WinPosY = 0;
	double CoorPosX = 0, CoorPosY = 0;
	glfwGetCursorPos(vWindow, &WinPosX, &WinPosY);

	WCHAR str[200];
	swprintf(str, 400, L"button %d, action %d, mode %x [%lf,%lf]\r\n", vButton, vAction, vMode, WinPosX, WinPosY);

	G_ChoosedPoint = -1;
	windowPos2CoordiatePos(vWindow, WinPosX, WinPosY, &CoorPosX, &CoorPosY);

	for (int i = 0; i < POINTS_NUM && (GLFW_PRESS == vAction); ++i)
	{
		if (isPointPosValid(vWindow, WinPosX, WinPosY, G_ControlPoints[i][0], G_ControlPoints[i][1], G_PointSize))
		{
			G_ChoosedPoint = i;
			break;
		}
	}

	if (GLFW_PRESS == vAction && (GLFW_MOD_CONTROL & vMode))
	{
		resetControlPoints();
	}
}

void mouseMoveCallback(GLFWwindow* vWindow, double vPosX, double vPosY)
{
	if (G_ChoosedPoint >= 0 && G_ChoosedPoint <= POINTS_NUM - 1)
	{
		double CoorPosX = 0, CoorPosY = 0;
		windowPos2CoordiatePos(vWindow, vPosX, vPosY, &CoorPosX, &CoorPosY);
		G_ControlPoints[G_ChoosedPoint][0] = CoorPosX;
		G_ControlPoints[G_ChoosedPoint][1] = CoorPosY;
	}
}

void windowResizeCallback(GLFWwindow* vWindow, int vWidth, int vHeight)
{
	G_Width = vWidth > vHeight ? vHeight : vWidth;
	G_Height = G_Width;
	glViewport((vWidth - G_Width) / 2, (vHeight - G_Height) / 2, G_Width, G_Height);
}

[[nodiscard]] bool initWindow(GLFWwindow* vWindow)
{
	try
	{
		glfwMakeContextCurrent(vWindow);
		glfwSetKeyCallback(vWindow, keyboardCallback);
		glfwSetMouseButtonCallback(vWindow, mouseButtonCallback);
		glfwSetCursorPosCallback(vWindow, mouseMoveCallback);
		glfwSetWindowSizeCallback(vWindow, windowResizeCallback);
	}
	catch (...)
	{
		std::cout << "Failed to register GLFW Callback" << std::endl;
		return false;
	}

	return true;
}

[[nodiscard]] bool initGL(GLFWwindow* voWindow)
{
	if (voWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	bool r = initWindow(voWindow);
	if (r == false) return false;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	glViewport(0, 0, G_Width, G_Height);
	glLineWidth(G_LineWidth);

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void DrawBezier()
{
	glColor3b(100, 40, 20);
	glMap1f(GL_MAP1_VERTEX_3, 0.0f, 1.0f, POINT_POS, POINTS_NUM, &G_ControlPoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	glBegin(GL_LINE_STRIP);

	for (float i = 0.0f; i <= 1.0f; i += 0.01f)
	{
		glColor3f(i, 1.0f - i, 0.4f + i);
		glEvalCoord1f(i);
	}

	glEnd();

	glColor3b(0, 0, 0);
	glPointSize(G_PointSize);
	glBegin(GL_POINTS);
	for (int i = 0; i < POINTS_NUM; i++)
		glVertex3fv(G_ControlPoints[i].data());

	glEnd();
}

void render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	DrawBezier();
}

int main()
{
	glfwInit();
	GLFWwindow* pWindow = glfwCreateWindow(G_Width, G_Height, "Bezier", NULL, NULL);
	bool r = initGL(pWindow);
	if (r == false) return -1;

	resetControlPoints();

	while (!glfwWindowShouldClose(pWindow))
	{
		glfwPollEvents();
		render();
		glfwSwapBuffers(pWindow);
	}

	glfwTerminate();
	return 0;
}