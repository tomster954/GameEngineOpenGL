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
#include "Shapes.h"
#include "Texture.h"
#include "Sprite_Batch.h"

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

	m_SB = new Sprite_Batch();

	glm::vec3 m_cameraPos = glm::vec3(0, 0, 0);
	glm::vec3 m_direction = glm::vec3(0, 0, -1);

	m_camera = new Camera(m_cameraPos, m_direction, m_pWindow);
	
	m_shapes = new Shapes();
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(00, 00, -50), glm::vec3(0, 0, 0), false);
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(-50, 00, 00), glm::vec3(0, 0, 0), false);
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(00, 00, 50), glm::vec3(0, 0, 0), false);
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(50, 00, 00), glm::vec3(0, 0, 0), false);

	m_texture1 = new Texture("./resources/Images/cherry.png", glm::vec2(50), glm::vec3(0, 0, -50));
}

Application::~Application()
{
	//Deleting textures
	delete m_texture1;

	//Deleting shapes
	delete m_shapes;

	//Deleting the camera
	delete m_camera;

	//Delete Sprite Batch
	delete m_SB;

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
	
	m_camera->Draw();
	m_shapes->Draw();

	//adds m_texture to the list of textures
	m_SB->DrawSprite(m_texture1);
	
	//called last after all textures are passed in
	m_SB->Draw();
	
	//swap buffers
	glfwSwapBuffers(m_pWindow);
}

void Application::Update()
{
	m_time = glfwGetTime();
	m_dt = m_time - m_prevTime;
	m_prevTime = m_time;

	m_camera->Update(m_dt);
	m_shapes->Update(m_dt);
}