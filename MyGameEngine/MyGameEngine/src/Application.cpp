#include "Application.h"

//standard headers
#include <stdio.h>

//GLEW
#define GLEW_STATIC
#include "glew.h"

//GLU
#include <GL/glu.h>

//GLFW
#include "glfw3.h"

//GLM
#include "glm/glm.hpp"

#include "Camera.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

Application::Application()
{
	m_time		= 0.0f;
	m_dt		= 0.0f;
	m_prevTime	= 0.0f;

	InitialiseGLFW();

	m_cameraPos = glm::vec3(0, 50, 100);
	m_cameraTar = glm::vec3(0, 0, -1);

	m_camera = new Camera(m_cameraPos, m_cameraTar, m_pWindow);
}

Application::~Application()
{
	//Destroying window
	glfwDestroyWindow(m_pWindow);

	//Terminating GLFW
	glfwTerminate();
}

void Application::InitialiseGLFW()
{
	//Setting an error call back function
	glfwSetErrorCallback(error_callback);

	//initialising GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Create the window
	m_pWindow = glfwCreateWindow(640, 480, "My Engine", NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Make this window the current context
	glfwMakeContextCurrent(m_pWindow);

	//set the swap intervals the a reasonable amount

	glfwSwapInterval(1);
	//Setting key call back function
	glfwSetKeyCallback(m_pWindow, key_callback);

	glEnable(GL_DEPTH_TEST);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		Draw();
		Update();		
	}
}

void Application::Draw()
{
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Poll events
	glfwPollEvents();
	
	m_camera->Draw();
	
	//creating a square
	CreateSquare(glm::vec3(10000, 1, 10000), glm::vec3(0, 0, 0), false);

	CreateSquare(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), true);
	CreateSquare(glm::vec3(10, 10, 10), glm::vec3(20, 20, 20), false);

	//swap buffers
	glfwSwapBuffers(m_pWindow);
}

void Application::Update()
{
	m_time = glfwGetTime();
	m_dt = m_time - m_prevTime;
	m_prevTime = m_time;

	m_camera->Update(m_dt);
}

void Application::CreateSquare(glm::vec3 _size, glm::vec3 _pos, bool _rotate)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(_pos.x, _pos.y, _pos.z);

	//rotate the square
	if (_rotate == true)
		glRotatef(m_time * -50.f, 0.f, 1.f, 1.f);

#pragma region Cube Quads
	float hBW = _size.x / 2; //Half Box Width
	float hBH = _size.y / 2; //Half Box Height
	float hBD = _size.z / 2; //Half Box Depth

	glBegin(GL_QUADS);
	//TOP - grey
	glColor3f(0.4f, 0.4f, 0.4f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-hBW, hBH, hBD);
	glVertex3f(hBW, hBH, hBD);
	glVertex3f(hBW, hBH, -hBD);
	glVertex3f(-hBW, hBH, -hBD);

	glEnd();

	glBegin(GL_QUADS);
	
	//FRONT - ORANGE
	glColor3f(1.0f, 0.5f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(hBW, hBH, hBD);
	glVertex3f(hBW, -hBH, hBD);
	glVertex3f(-hBW, -hBH, hBD);
	glVertex3f(-hBW, hBH, hBD);

	glEnd();

	glBegin(GL_QUADS);
	//RIGHT - BLUE
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(hBW, hBH, -hBD);
	glVertex3f(hBW, hBH, hBD);
	glVertex3f(hBW, -hBH, hBD);
	glVertex3f(hBW, -hBH, -hBD);

	glEnd();

	glBegin(GL_QUADS);
	//LEFT - GREEN
	glColor3f(0.0f, 1.0f, 0.5f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-hBW, -hBH, hBD);
	glVertex3f(-hBW, hBH, hBD);
	glVertex3f(-hBW, hBH, -hBD);
	glVertex3f(-hBW, -hBH, -hBD);

	glEnd();

	glBegin(GL_QUADS);
	//BOTTOM - PURPLE
	glColor3f(0.5f, 0.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(hBW, -hBH, hBD);
	glVertex3f(-hBW, -hBH, hBD);
	glVertex3f(-hBW, -hBH, -hBD);
	glVertex3f(hBW, -hBH, -hBD);

	glEnd();

	glBegin(GL_QUADS);
	//FRONT - YELLOW
	glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 0.5f);
	glVertex3f(hBW, -hBH, -hBD);
	glVertex3f(hBW, hBH, -hBD);
	glVertex3f(-hBW, hBH, -hBD);
	glVertex3f(-hBW, -hBH, -hBD);

	glEnd();
#pragma endregion
}