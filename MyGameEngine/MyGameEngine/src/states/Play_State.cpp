#include "States\Play_State.h"
#include "Application.h"

//GLFW
#include "glfw3.h"

#include "Map_Manager.h"
#include "Sprite_Batch.h"
#include "Shapes.h"
#include "base classes\Base_Character.h"

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
	//Initialise Player 1
	m_playerTexture = new Texture("./resources/Images/survivor.png", glm::vec2(50, 40), glm::vec2(0), glm::vec3(0, 0, 1), glm::vec2(0));
	m_playerTexture->DrawFromCentre(true);
	m_player = new Base_Character(m_pApp->m_pWindow, glm::vec3(700, -700, 10), 10, 100, m_playerTexture);

	m_testTextue = new Texture("./resources/Images/survivor.png", glm::vec2(50, 40), glm::vec2(0), glm::vec3(0, 0, 1), glm::vec2(0));
	m_testTextue->DrawFromCentre(true);
	m_testTextue->SetPosition(glm::vec3(720, -720, 10));
}

void Play_State::LoadMap()
{

}

void Play_State::Update(float a_dt)
{
	//call the players update function
	m_player->Update(a_dt);

	//sets the texture to the cameras position
	//m_playerTexture->SetPosition(glm::vec3(m_pApp->GetCamera()->GetPosition().x, m_pApp->GetCamera()->GetPosition().y, 1));
	
	//Updates the map
	m_pApp->GetMapManager()->Update(a_dt);

	//PAUSE
	if (glfwGetKey(m_pApp->m_pWindow, GLFW_KEY_P) == GLFW_PRESS)
	{
		m_pApp->GetStateManager()->PopState();
		m_pApp->GetStateManager()->PushState("Menu_State");
		m_pApp->GetCamera()->MoveTo(glm::vec3(0, 0, 500));
	}

	
}

void Play_State::Draw(Sprite_Batch *a_SB)
{
	//Drawing map 1 (Draw everything after the map or it wont be seen)
	m_pApp->GetMapManager()->Draw(a_SB);

	//call the players draw function
	m_player->Draw(a_SB);
	
	a_SB->DrawSprite(m_testTextue);
}