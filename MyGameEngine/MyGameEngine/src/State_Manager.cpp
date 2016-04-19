#include "State_Manager.h"
#include "Application.h"
#include "glfw3.h"

#pragma region IState

IState::IState(Application *a_pApp)
{
	//Sets the pointer to the main application
	m_pApplication = a_pApp;

	//Sets the member width and height variables
	glfwGetWindowSize(m_pApplication->m_pWindow, &m_windowWidth, &m_windowHeight);
}

IState::~IState()
{
	//Left Blank
}

void IState::Inititalise()
{
	//Left Blank
}

void IState::Update(float dt)
{
	//Left Blank
}

void IState::Draw(Sprite_Batch *a_pSB)
{
	//Left Blank
}

#pragma endregion IState

#pragma region Manager

State_Manager::State_Manager()
{

}

State_Manager::~State_Manager()
{

}

void State_Manager::UpdateStates(float a_dt)
{
	//Find all the states that require updating 
	ProcessCommands();

	//Loops throught states that need updating
	for (int i = 0; i < m_StateStack.size(); i++)
	{
		bool blocking = false;

		//Finds if there are any states higher on the stack that are blocking updates, if so, dont update this state.
		for (int j = i + 1; j < m_StateStack.size(); j++)
		{
			if (m_StateStack[j]->m_blockUpdate == true)
			{
				blocking = true;
				break;
			}
		}

		//Only updates this state if the states ontop aren't blocking updates
		if (!blocking)
			m_StateStack[i]->Update(a_dt);
	}
}

void State_Manager::DrawStates(Sprite_Batch *a_pSB)
{
	//Loops throught states that need drawing
	for (int i = 0; i < m_StateStack.size(); i++)
	{
		bool blocking = false;

		//Finds if there are any states higher on the stack that are blocking drawing, if so, dont draw this state.
		for (int j = i + 1; j < m_StateStack.size(); j++)
		{
			if (m_StateStack[j]->m_blockDraw == true)
			{
				blocking = true;
				break;
			}
		}

		//Only draws this state if the states ontop aren't blocking drawing
		if (!blocking)
			m_StateStack[i]->Draw(a_pSB);
	}
}

void State_Manager::ProcessCommands()
{
	for (int i = 0; i< m_commands.size(); i++)
	{
		if (m_commands[i].cmd == E_PUSH)
		{
			//process the "push" command
			//-----------------------------------------------------
			auto iter = m_availableStates.find(m_commands[i].name);

			if (iter != m_availableStates.end())
			{
				m_StateStack.push_back(iter->second);
			}
			//-----------------------------------------------------
		}
		else if (m_commands[i].cmd == E_POP)
		{
			if (m_StateStack.size() > 0)
				m_StateStack.pop_back();
		}
		else if (m_commands[i].cmd == E_POPALL)
		{
			for (int i = m_StateStack.size(); i > 0; i--)
				m_StateStack.pop_back();
		}
	}

	m_commands.clear();
}

void State_Manager::SetState(const char *a_name, IState *a_pState)
{
	//if the a_name == an existing state that isnt already on the top of m_availableStates,
	//	delete it and re-add it to m_availableStates.
	auto iter = m_availableStates.find(a_name);
	if (iter != m_availableStates.end())
	{
		delete iter->second;
	}

	m_availableStates[a_name] = a_pState;
}

void State_Manager::PushState(const char *name)
{
	SCommands command;
	command.name = name;
	command.cmd = E_PUSH;

	m_commands.push_back(command);
}

void State_Manager::PopState()
{
	SCommands command;
	command.cmd = E_POP;

	m_commands.push_back(command);
}

void State_Manager::PopAll()
{
	SCommands command;
	command.cmd = E_POPALL;

	m_commands.push_back(command);
}
#pragma endregion Manager
