#include "Shapes.h"

//GLEW
#define GLEW_STATIC
#include "glew.h"

//GLFW
#include "glfw3.h"

Shapes::Shapes()
{
	
}

Shapes::~Shapes()
{

}

void Shapes::CreateShape(glm::vec3 a_size, glm::vec3 a_pos, glm::vec3 a_col, bool a_rotate)
{
	Shape s = Shape();
	s.size = a_size;
	s.pos = a_pos;
	s.col = a_col;
	s.rotate = a_rotate;

	m_allShapes.push_back(s);
}

void Shapes::Draw()
{
	for (std::list<Shape>::const_iterator itr = m_allShapes.begin(), end = m_allShapes.end(); itr != end; ++itr) 
	{	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(itr->pos.x, itr->pos.y, itr->pos.z);

		//rotate the square
		if (itr->rotate == true)
			glRotatef(glfwGetTime() * 50.f, 0.f, 1.f, 1.f);

	#pragma region Cube Quads
		float hBW = itr->size.x / 2; //Half Box Width
		float hBH = itr->size.y / 2; //Half Box Height
		float hBD = itr->size.z / 2; //Half Box Depth

		glBegin(GL_QUADS);
		//TOP - RED
		glColor3f(1.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-hBW, hBH, hBD);
		glVertex3f(hBW, hBH, hBD);
		glVertex3f(hBW, hBH, -hBD);
		glVertex3f(-hBW, hBH, -hBD);

		glEnd();

		glBegin(GL_QUADS);

		//FRONT - ORANGE
		//glColor3f(1.0f, 0.5f, 0.0f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(hBW, hBH, hBD);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(hBW, -hBH, hBD);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-hBW, -hBH, hBD);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-hBW, hBH, hBD);

		glEnd();

		glBegin(GL_QUADS);
		//RIGHT - BLUE
		glColor3f(0.0f, 0.0f, 1.0f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(hBW, hBH, -hBD);
		glVertex3f(hBW, hBH, hBD);
		glVertex3f(hBW, -hBH, hBD);
		glVertex3f(hBW, -hBH, -hBD);

		glEnd();

		glBegin(GL_QUADS);
		//LEFT - GREEN
		glColor3f(0.0f, 1.0f, 0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-hBW, -hBH, hBD);
		glVertex3f(-hBW, hBH, hBD);
		glVertex3f(-hBW, hBH, -hBD);
		glVertex3f(-hBW, -hBH, -hBD);

		glEnd();

		glBegin(GL_QUADS);
		//BOTTOM - PURPLE
		glColor3f(0.5f, 0.0f, 1.0f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(hBW, -hBH, hBD);
		glVertex3f(-hBW, -hBH, hBD);
		glVertex3f(-hBW, -hBH, -hBD);
		glVertex3f(hBW, -hBH, -hBD);

		glEnd();

		glBegin(GL_QUADS);
		//BACK - YELLOW
		glColor3f(1.0f, 1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 0.5f);
		glVertex3f(hBW, -hBH, -hBD);
		glVertex3f(hBW, hBH, -hBD);
		glVertex3f(-hBW, hBH, -hBD);
		glVertex3f(-hBW, -hBH, -hBD);

		glEnd();
#pragma endregion
	}
	
}

void Shapes::Update(float a_dt)
{
	m_dt = a_dt;
}