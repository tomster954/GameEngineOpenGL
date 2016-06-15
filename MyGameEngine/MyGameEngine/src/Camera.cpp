#include "Camera.h"

//GLEW
#define GLEW_STATIC
#include "glew.h"

//GLU
#include <GL/glu.h>

//GLFW
#include "glfw3.h"

//Runtime Error
#include <stdexcept>

#include <cmath>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialise(glm::vec3 a_pos, glm::vec3 a_direction, GLFWwindow *a_pWindow)
{
	//vars
	m_pWindow = a_pWindow;
	m_cameraPosition = a_pos;
	m_direction = a_direction;

	float aaa[9] =
	{
		0, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
	
	//Default camera rot
	m_camRotation = glm::mat3(
								1,0,0,
								0,1,0,
								0,0,1						
								);
	
	//Default directions
	m_up	= glm::vec3(0, 1, 0);
	m_right = glm::vec3(1, 0, 0);

	//vars
	m_cameraMoveSpeed = 10;
	m_cursorPos = glm::vec2(0, 0);
	m_cursorLastPos = glm::vec2(0, 0);
	m_rotation = 0;

	AddRotation('x', m_rotation);
}

void Camera::Draw()
{
	//setting the view port
	glViewport(0, 0, m_winWidth, m_winHeight);

	//calculating perspective
	glfwGetFramebufferSize(m_pWindow, &m_winWidth, &m_winHeight);
	m_winRatio = (float)m_winWidth / (float)m_winHeight;

	//Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, m_winRatio, 0.1, 1000);

	//setting the look at, based off the camera's pos and dir
	glm::vec3 facing = m_direction + m_cameraPosition;
	gluLookAt(m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z, facing.x, facing.y, facing.z, 0, 1, 0);
}

void Camera::Update(float a_dt)
{
	m_dt = a_dt;
	KeyInputHandling();
	MouseInputHandling();
}

void Camera::KeyInputHandling()
{
	float speed = m_cameraMoveSpeed * 10 * m_dt;
	float rotationSpeed = 1 * m_dt;

	//move camera with WASD
	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
		m_cameraPosition += speed * m_up;

	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
		m_cameraPosition += speed * -m_up;
	
	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
		m_cameraPosition -= glm::normalize(glm::cross(m_direction, m_up)) * speed;

	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
		m_cameraPosition += glm::normalize(glm::cross(m_direction, m_up)) * speed;

	float cameraRotSpeed = 100 * m_dt;
	//camera rotation off arrow keys
	//if (glfwGetKey(m_pWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
	//	AddRotation('Y', -cameraRotSpeed);
	//if (glfwGetKey(m_pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//	AddRotation('Y', cameraRotSpeed);
	//if (glfwGetKey(m_pWindow, GLFW_KEY_UP) == GLFW_PRESS)
	//	AddRotation('X', cameraRotSpeed);
	//if (glfwGetKey(m_pWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
	//	AddRotation('X', -cameraRotSpeed);
}

void Camera::MouseInputHandling()
{
	m_cursorLastPos = m_cursorPos;

	double x, y;
	glfwGetCursorPos(m_pWindow, &x, &y);
	
	m_cursorPos.x = (float)x;
	m_cursorPos.y = (float)y;

	float cursorSensitivity = 0.5f;
	m_cursorOffset = glm::vec2(m_cursorPos - m_cursorLastPos) * cursorSensitivity;
}

void Camera::AddRotation(char a_axis, float a_degrees)
{
	//Target - z axis, Right - x axis
	glm::vec3 right = glm::vec3(m_camRotation[0].x, m_camRotation[0].y, m_camRotation[0].z);
	glm::vec3 up = glm::vec3(m_camRotation[1].x, m_camRotation[1].y, m_camRotation[1].z);
	glm::vec3 target = glm::vec3(m_camRotation[2].x, m_camRotation[2].y, m_camRotation[2].z);

	if (a_axis == 'x' || a_axis == 'X')
	{
		float ygamma = glm::radians(a_degrees);		// how much we are rotating 
		float yalpha = glm::radians(90.0f - a_degrees);// 90 degrees - the rotation

		float zgamma = glm::radians(90.0f + a_degrees);	// 90 degrees + the rotation - this will give 90 difference between x and z
		float zalpha = glm::radians(a_degrees);		// how much we are rotating 

		//if target.y > -0.9999f to prevent inverting
		if (cos(zgamma) * up.y + cos(zalpha) * target.y < 0.999f &&
			cos(zgamma) * up.y + cos(zalpha) * target.y > -0.999f)
		{
			//Y UP
			m_camRotation[1].y = cos(ygamma) * up.y + cos(yalpha) * target.y;
			m_camRotation[1].z = cos(ygamma) * up.z + cos(yalpha) * target.z;

			//Z TARGET
			m_camRotation[2].y = cos(zgamma) * up.y + cos(zalpha) * target.y;
			m_camRotation[2].z = cos(zgamma) * up.z + cos(zalpha) * target.z;

			//normalize y and z since we modified them
			glm::normalize(glm::vec3(m_camRotation[1].x, m_camRotation[1].y, m_camRotation[1].z));
			glm::normalize(glm::vec3(m_camRotation[2].x, m_camRotation[2].y, m_camRotation[2].z));
		}
	}
	else if (a_axis == 'y' || a_axis == 'Y')
	{
		float xbeta = glm::radians(a_degrees);		// how much we are rotating 
		float xalpha = glm::radians(90.0f - a_degrees);// 90 degrees - the rotation

		float zbeta = glm::radians(90.0f + a_degrees);	// 90 degrees + the rotation - this will give 90 difference between x and z
		float zalpha = glm::radians(a_degrees);		// how much we are rotating 

		//X RIGHT		     |			 X		   ||			Z		  |	
		m_camRotation[0].x = cos(xbeta) * right.x + cos(xalpha) * target.x;
		m_camRotation[0].z = cos(xbeta) * right.z + cos(xalpha) * target.z;

		//Z TARGET
		m_camRotation[2].x = cos(zbeta) * right.x + cos(zalpha) * target.x;
		m_camRotation[2].z = cos(zbeta) * right.z + cos(zalpha) * target.z;

		//normalize x and z since we modified them
		glm::normalize(glm::vec3(m_camRotation[0].x, m_camRotation[0].y, m_camRotation[0].z));
		glm::normalize(glm::vec3(m_camRotation[2].x, m_camRotation[2].y, m_camRotation[2].z));
	}
	else if (a_axis == 'z' || a_axis == 'Z')
	{ 
		//if the selected axis is "Z"
	}
	else
	{
		//error no such axis
		throw std::runtime_error("Error: No such axis ");
	}

	//last set the current direction (negative is into the screen)
	m_direction = -glm::vec3(m_camRotation[2].x, m_camRotation[2].y, m_camRotation[2].z);
}