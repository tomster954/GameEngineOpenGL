//-----------------------------------------------------------------------------
//Author: Tom solarino
//Description: This is the map select state where you choose a map to play
//-----------------------------------------------------------------------------

#ifndef MAP_SELECT
#define MAP_SELECT
#include "State_Manager.h"

class Texture;
class Application;

class Map_Select : public IState
{
public:
	Map_Select(Application *a_pApp);
	virtual ~Map_Select();

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