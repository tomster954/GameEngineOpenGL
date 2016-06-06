//-----------------------------------------------------------------------------
//Author: Tom Solarino
//Description: this is a tile class that the map will mostly use for the map tiles
//-----------------------------------------------------------------------------

#ifndef TILE
#define TILE

class Texture;

class Tile
{
public:
	Tile();
	~Tile();

private:
	Texture *m_texture;	//Tile Texture of Tile sheet with texture coords
	int m_tileID;		//The ID of the specific tile needed to be drawn
};
#endif