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
class Map_Manager;

class Application
{
public:
	Application();
	~Application();
	void InitialiseGLFW();

	void Run();
	void Draw();
	void Update();
	
	Map_Manager* GetMapManager(){ return m_mapManager; }
	Camera* GetCamera(){ return &m_camera; }
	glm::vec2 GetWindowSize();
	
	State_Manager* GetStateManager(){ return &m_stateManager; }
	
	GLFWwindow* m_pWindow;
private:
	Camera m_camera;
	State_Manager m_stateManager;
	Sprite_Batch m_SB;

	Map_Manager *m_mapManager;

	int m_winWidth, m_winHeight;
	float m_winRatio;
	
	float m_dt;
	float m_prevTime;
	double m_time;
};

#endif