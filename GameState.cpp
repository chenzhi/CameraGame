#include "pch.h"
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
    
}

/*
 *状态结束函数
 */
void  GameState::end( )
{
    State::end();
      
}



StateType GameState::update(float time)
{
    
  return  State::update(time);
    
}



