#include "base classes\Base_Object.h"

Base_Object::Base_Object()
{

}

Base_Object::~Base_Object()
{

}

void Base_Object::MoveTo(glm::vec3 a_location)
{
	m_location = a_location;
}