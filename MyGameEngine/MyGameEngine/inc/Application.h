//-----------------------------------------------------------------------------
//Author: Tommas Solarino
//Description: This is the main run loop
//-----------------------------------------------------------------------------

#ifndef APPLICATION
#define APPLICATION

//GLM
#include "glm/glm.hpp"

struct GLFWwindow;
class Camera; 

class Application
{
public:
	Application();
	~Application();
	void InitialiseGLFW();

	void Run();
	void Draw();
	void Update();

	void CreateSquare(glm::vec3 _size, glm::vec3 _pos, bool _rotate);

private:
	GLFWwindow* m_pWindow;
	Camera *m_camera;

	int m_winWidth, m_winHeight;
	float m_winRatio;
	float m_dt;
	float m_prevTime;

	double m_time;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraTar;
};

#endif