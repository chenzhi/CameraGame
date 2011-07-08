
#include "GameState.h"
#include "Application.h"



GameState::GameState(StateType stateType)
:State(stateType),m_pSceneManager(NULL)
{
    
    m_pSceneManager=Application::getSingleton().getMainSceneManager();
    
}


GameState::~GameState()
{
    
}


/*状态开始函数,
 */
void  GameState::begin( )
{
	State::begin();
    
    initUI();
    
}

/*
 *状态结束函数
 */
void  GameState::end( )
{
    State::begin();
    destroyUI();
      
}



StateType GameState::update(float time)
{
    
  return  State::update(time);
    
}



