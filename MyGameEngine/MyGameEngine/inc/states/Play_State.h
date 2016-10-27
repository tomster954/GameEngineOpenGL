//-----------------------------------------------------------------------------
//Author: Tom solarino
//Description: This is the main play state where the game is played
//-----------------------------------------------------------------------------

#ifndef PLAY_STATE
#define PLAY_STATE
#include "State_Manager.h"

class Texture;
class Map_Manager;
class Application;

class Play_State : public IState
{
public:
	Play_State(Application *a_pApp);
	virtual ~Play_State();

	virtual void Update(float a_dt);
	virtual void Draw(Sprite_Batch *a_pSB);

private:
	virtual void Initialise();
	void LoadMap();
	Texture *m_playerTexture;
	Application *m_pApp;
};
#endif