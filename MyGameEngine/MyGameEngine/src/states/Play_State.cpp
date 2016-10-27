#include "States\Play_State.h"
#include "Application.h"

//GLFW
#include "glfw3.h"

#include "Map_Manager.h"
#include "Sprite_Batch.h"
#include "Shapes.h"

Play_State::Play_State(Application *a_app) : IState(a_app)
{
	m_pApp = a_app;
	Initialise();
}

Play_State::~Play_State()
{
	//Deleting textures
	delete m_playerTexture;
}

void Play_State::Initialise()
{
	//Initialise Textures
	m_playerTexture = new Texture("./resources/Images/survivor.png", glm::vec2(50, 40), glm::vec2(0), glm::vec3(0, 0, 1), glm::vec2(0));
	m_playerTexture->DrawFromCentre(true);
}

void Play_State::LoadMap()
{

}

void Play_State::Update(float a_dt)
{
	m_playerTexture->SetPosition(glm::vec3(m_pApp->GetCamera()->GetPosition().x, m_pApp->GetCamera()->GetPosition().y, 1));
	m_pApp->GetMapManager()->Update(a_dt);

	if (glfwGetKey(m_pApp->m_pWindow, GLFW_KEY_P) == GLFW_PRESS)
	{
		m_pApp->GetStateManager()->PopState();
		m_pApp->GetStateManager()->PushState("Menu_State");
		m_pApp->GetCamera()->SetPosition(glm::vec3(0, 0, 500));
	}

	
}

void Play_State::Draw(Sprite_Batch *a_SB)
{
	//Drawing map 1
	m_pApp->GetMapManager()->Draw(a_SB);

	//adds m_texture to the list of textures
	a_SB->DrawSprite(m_playerTexture);
}