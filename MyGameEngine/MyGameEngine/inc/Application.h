//-----------------------------------------------------------------------------
//Author: Tommas Solarino
//Description: This is the main run loop
//-----------------------------------------------------------------------------

#ifndef APPLICATION
#define APPLICATION

//GLM
#include "glm/glm.hpp"

#include "Sprite_Batch.h"
#include "State_Manager.h"
#include "Camera.h"

struct GLFWwindow;
class Application
{
public:
	Application();
	~Application();
	void InitialiseGLFW();

	void Run();
	void Draw();
	void Update();
	
	GLFWwindow* m_pWindow;
private:
	
	State_Manager m_stateManager;
	Sprite_Batch m_SB;
	Camera m_camera;

	int m_winWidth, m_winHeight;
	float m_winRatio;
	
	float m_dt;
	float m_prevTime;
	double m_time;
};

#endif