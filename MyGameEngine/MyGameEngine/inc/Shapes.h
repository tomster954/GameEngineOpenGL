//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Author:Tom Solarino
//Description: This class create a specified shape
//-----------------------------------------------------------------------------

#ifndef SHAPES
#define SHAPES

//GLM
#include "glm/glm.hpp"

#include <list>

struct Shape
{
	glm::vec3 size;
	glm::vec3 pos;
	glm::vec3 col;
	bool rotate;
};

class Shapes
{
public:
	Shapes();
	~Shapes();

	void CreateShape(glm::vec3 a_size, glm::vec3 a_pos, glm::vec3 a_col, bool a_rotate);

	void Draw();
	void Update(float a_dt);

private:
	std::list<Shape> m_allShapes;
	float m_dt;
};
#endif