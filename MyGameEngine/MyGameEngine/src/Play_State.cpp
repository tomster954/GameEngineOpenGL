#include "Play_State.h"
#include "Application.h"

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
	delete m_texture1;

	//Deleting shapes
	delete m_shapes;
}

void Play_State::Initialise()
{
	//Creating some shapes to see
	m_shapes = new Shapes();
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(00, 00, -50), glm::vec3(0, 0, 0), false);
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(-50, 00, 00), glm::vec3(0, 0, 0), false);
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(00, 00, 50), glm::vec3(0, 0, 0), false);
	m_shapes->CreateShape(glm::vec3(10, 10, 10), glm::vec3(50, 00, 00), glm::vec3(0, 0, 0), false);

	//Initialise Textures
	m_texture1 = new Texture("./resources/Images/cherry.png", glm::vec2(50), glm::vec2(0), glm::vec3(0, 0, -50), glm::vec2(0.5f, 0.5f));
}

void Play_State::LoadMap()
{

}

void Play_State::Update(float a_dt)
{
	m_shapes->Update(a_dt);
}

void Play_State::Draw(Sprite_Batch *a_SB)
{
	m_shapes->Draw();
	
	//Drawing map 1
	m_pApp->GetMapManager()->Draw(a_SB, MAP1);

	//adds m_texture to the list of textures
	a_SB->DrawSprite(m_texture1);
}