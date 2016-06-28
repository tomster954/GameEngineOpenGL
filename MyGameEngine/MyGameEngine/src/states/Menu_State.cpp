#include "States\Menu_State.h"

#include "Application.h"
#include "State_Manager.h"

#include "Sprite_Batch.h"

Menu_State::Menu_State(Application *a_app) : IState(a_app)
{
	m_pApp = a_app;
	Initialise();
}

Menu_State::~Menu_State()
{
	//Deleting textures
	delete m_background;
}

void Menu_State::Initialise()
{
	//Initialise Textures
	m_background = new Texture("./resources/Images/lmao.png", glm::vec2(m_pApp->GetWindowSize()), glm::vec2(0), glm::vec3(0, 0, 0), glm::vec2(0));
	m_background->DrawFromCentre(true);
}

void Menu_State::LoadMap()
{

}

void Menu_State::Update(float a_dt)
{
	}

void Menu_State::Draw(Sprite_Batch *a_SB)
{
	//adds m_texture to the list of textures
	a_SB->DrawSprite(m_background);
}