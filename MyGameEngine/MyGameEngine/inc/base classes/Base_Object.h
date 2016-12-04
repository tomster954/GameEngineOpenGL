//-----------------------------------------------------------------------------
//Author: Tom Solarino	
//Description: Any object placed in the world inherits from this class
//-----------------------------------------------------------------------------
#ifndef BASE_OBJECT
#define BASE_OBJECT

#include "glm/glm.hpp"

class Base_Object
{
public:
	//contructor
	Base_Object();
	//destrutor
	~Base_Object();

	//All base objects will be able to move
	void MoveTo(glm::vec3 a_location);
	
	glm::vec3 GetLocation(){ return m_location; };
	void SetLocation(glm::vec3 a_location){ m_location = a_location; }

protected:
	glm::vec3 m_location = glm::vec3(0);
};
#endif

//TODO fix up inheritance <-----------------------------------