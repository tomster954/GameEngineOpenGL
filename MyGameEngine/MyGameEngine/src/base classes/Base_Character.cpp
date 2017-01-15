#include "base classes\Base_Character.h"

#include "Sprite_Batch.h"

//GLFW
#include "glfw3.h"
//GLM
#include "glm/glm.hpp"

Base_Character::Base_Character(GLFWwindow *a_pWindow, glm::vec3 a_startLocation, float a_speed, float a_health, Texture *a_playerTexture) : Base_Object()
{
	m_pWindow = a_pWindow;
	m_location = a_startLocation;
	m_playerTexture = a_playerTexture;
	//Default directions
	m_up = glm::vec3(0, 1, 0);
	m_right = glm::vec3(1, 0, 0);
}

Base_Character::~Base_Character()
{
	delete m_playerTexture;
}

void Base_Character::Draw(Sprite_Batch *a_SB)
{
	//adds m_texture to the list of textures
}

void Base_Character::Update(float a_dt)
{
	m_playerTexture->SetPosition(m_location);
	HandleInput(a_dt);
}

void Base_Character::HandleInput(float a_dt)
{
	//Handles all player input
	//move camera with WASD
	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS && !glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_location += m_speed * a_dt * m_up;
	
	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS && !glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_location += m_speed * a_dt * -m_up;
	
	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS && !glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_location += m_speed * a_dt * -m_right;

	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS && !glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_location += m_speed * a_dt * m_right;
	
	//move z
	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS && glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_location += m_speed * a_dt * glm::vec3(0, 0, 1);
	
	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS && glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_location += m_speed * a_dt * glm::vec3(0, 0, -1);
}