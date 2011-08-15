#include "pch.h"
#include "stateMachine.h"




StateMachine::StateMachine()
:m_pcurrentState(NULL)
{
    
}


StateMachine::~StateMachine()
{
	
	destroyAllState();
}


void  StateMachine::update(float time)
{
	if(m_pcurrentState==NULL)
		return ;
    
	static bool firstFrame=true;
    
	StateType nextType = m_pcurrentState->update(firstFrame?0.01f:time);
	
	///如果下一帧的状态和当前帧不同需要更换状态
	if(nextType!=m_pcurrentState->getType())
	{
		m_pcurrentState->end();
            
		State* ptemState = findState(nextType);
		assert(ptemState);
		m_pcurrentState=ptemState;
		ptemState->begin();
		firstFrame=true;
	}
    
	firstFrame=false;
}


void StateMachine::destroyAllState()
{
    
	////如果当前有活动状态，首先结束状态
	if(m_pcurrentState!=NULL)
	{
		m_pcurrentState->end();
	}
    
	StateCollect::iterator it = m_stateCollect.begin();
	while(it!=m_stateCollect.end())
	{
		delete *it;
		*it=NULL;
		++it;
	}
	m_stateCollect.clear();
    
	m_pcurrentState=NULL;
	return ;
    
}


State* StateMachine::findState(StateType type)
{
    
	StateCollect::iterator it = m_stateCollect.begin();
	while(it!=m_stateCollect.end())
	{
        if((*it)->getType()==type)
        {
            return *it;
        }
        ++it;
	}
	return NULL;
}



bool  StateMachine::registerState(State* pState)
{
	if(pState==NULL)
		return false;
    
	if(findState(pState->getType())!=NULL)
	{
		return false;
	}
	m_stateCollect.push_back(pState);
    
	return true;
    
}


bool StateMachine::unregisterState(StateType type)
{
    
	StateCollect::iterator it =m_stateCollect.begin();
	while(it!=m_stateCollect.end())
	{
		if((*it)->getType()==type)
		{
			delete (*it);
			m_stateCollect.erase(it);
			return true;
		}
		++it;
	}
	return false;
    
}


State*  StateMachine::getState(unsigned int index) const 
{
	if(index>=m_stateCollect.size())
		return NULL;
	return m_stateCollect[index];
    
}


///设置游戏开始的状态
void StateMachine::setBeginState(StateType GS)
{
	State* pGameState=findState(GS);
	if(pGameState==NULL)
	{
        
        throw("can't find begin state StateMachine::setBeginState");
		//OGRE_EXCEPT(0,"can't find begin state ","Application::setBeginState");
		return ;
	}
    
	m_pcurrentState=pGameState;
	m_pcurrentState->begin();
    
}
