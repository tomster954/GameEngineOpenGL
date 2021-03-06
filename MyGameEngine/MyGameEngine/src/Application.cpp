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

//My includes
#include "Camera.h"
#include "Sprite_Batch.h"
//States
#include "State_Manager.h"
#include "States\Menu_State.h"
#include "States\Play_State.h"
//Maps
#include "Map_Manager.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

Application::Application() :
m_SB(Sprite_Batch(this)),
m_stateManager(State_Manager()),
m_camera(Camera())
{
	//Initialise time values
	m_time = 0.0f;
	m_dt = 0.0f;
	m_prevTime = 0.0f;

	//Initialise GLFW
	InitialiseGLFW();

	//Initialise Camera
	glm::vec3 m_cameraPos = glm::vec3(0, 0, 500);
	glm::vec3 m_direction = glm::vec3(0, 0, -1);
	m_camera.Initialise(m_cameraPos, m_direction, m_pWindow);

	//Initialise map manager and load a map
	m_mapManager = new Map_Manager(this);
	m_mapManager->LoadNewMap("./resources/maps/map1.tmx");
	m_mapManager->SetMap(MAP1);

	//Add States to the State Manager
	m_stateManager.SetState("Menu_State", new Menu_State(this));
	m_stateManager.SetState("Play_State", new Play_State(this));
	m_stateManager.PushState("Play_State");

}

Application::~Application()
{
	//deleting the map manager
	delete m_mapManager;

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
	m_pWindow = glfwCreateWindow(1024, 576, "My Engine", NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Make this window the current context
	glfwMakeContextCurrent(m_pWindow);

	//set the swap intervals to a reasonable amount
	glfwSwapInterval(1);
	//Setting key call back function
	glfwSetKeyCallback(m_pWindow, key_callback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_pWindow))
	{
		Update();		
		Draw();
	}
}

void Application::Draw()
{
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Poll events
	glfwPollEvents();
	
	m_camera.Draw();

	m_stateManager.DrawStates(&m_SB);
	
	//called last after all textures are passed in
	m_SB.Draw();
	
	//swap buffers
	glfwSwapBuffers(m_pWindow);
}

void Application::Update()
{
	m_time = glfwGetTime();
	m_dt = (float)m_time - m_prevTime;
	m_prevTime = (float)m_time;

	m_camera.Update(m_dt);

	m_stateManager.UpdateStates(m_dt);
}

glm::vec2 Application::GetWindowSize()
{
	int x, y;
	glfwGetWindowSize(m_pWindow, &x, &y);
	return glm::vec2(x, y);
}