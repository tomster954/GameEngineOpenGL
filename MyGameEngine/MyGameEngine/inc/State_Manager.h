//-----------------------------------------------------------------------------
//Author:: Tom Solarino	
//Description:: This class manages all the game states
//-----------------------------------------------------------------------------

#ifndef STATE_MANAGER
#define STATE_MANAGER
#include <map>
#include <vector>

class Application;
class Sprite_Batch;

class IState
{
public:
	IState(Application *a_pApp);
	~IState();

	virtual void Update(float a_dt);
	virtual void Draw(Sprite_Batch *a_pSB);

	bool m_blockUpdate;
	bool m_blockDraw;

	int m_windowWidth;
	int m_windowHeight;

protected:
	virtual void Inititalise();
	Application *m_pApplication;
};

class State_Manager
{
public:
	State_Manager();
	virtual ~State_Manager();

	void UpdateStates(float a_dt);
	void DrawStates(Sprite_Batch *a_SB);

	void SetState(const char *a_name, IState *a_pState);
	void PushState(const char *a_name);
	void PopState();
	void PopAll();
	
protected:
	void ProcessCommands();

	//All available maps
	std::map< const char *, IState * > m_availableStates;

	//States to be updated and drawn
	std::vector<IState*> m_StateStack;

	//State commands
	enum ECommands
	{
		E_PUSH,
		E_POP,
		E_POPALL,
	};

	//Commands structure
	struct SCommands
	{
		const char *name;
		ECommands cmd;
	};

	//Vector of current commands
	std::vector< SCommands > m_commands;

private:

};
#endif