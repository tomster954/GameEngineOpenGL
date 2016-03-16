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
class Shapes;
class Texture;
class Sprite_Batch;

class Application
{
public:
	Application();
	~Application();
	void InitialiseGLFW();

	void Run();
	void Draw();
	void Update();

private:
	GLFWwindow* m_pWindow;
	Camera *m_camera;
	Sprite_Batch *m_SB;
	Shapes *m_shapes;
	Texture *m_texture1;

	int m_winWidth, m_winHeight;
	float m_winRatio;
	
	float m_dt;
	float m_prevTime;
	double m_time;
};

#endif