//-----------------------------------------------------------------------------
//Author: Tom solarino
//Description: This is the menu state, this is the first main state
//-----------------------------------------------------------------------------

#ifndef MENU_STATE
#define MENU_STATE
#include "State_Manager.h"

class Texture;
class Application;

class Menu_State : public IState
{
public:
	Menu_State(Application *a_pApp);
	virtual ~Menu_State();

	virtual void Update(float a_dt);
	virtual void Draw(Sprite_Batch *a_pSB);

private:
	//private functions
	virtual void Initialise();
	void LoadMap();

	//private vars
	Application *m_pApp;
	Texture *m_background;
};
#endif