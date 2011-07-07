#pragma once


#include "state.h"
#include  "UIBase.h"


class GameState : public State
{
public:
    
	GameState( StateType stateType );
    
    
	virtual ~GameState();
    
	
    /*
     *状态开始函数,
     */
	virtual void  begin( );
    
	/*
     *状态结束函数
     */
	virtual void  end( );
    
    
	/**更新函数*/
	virtual StateType update(float time);
	
    
    
	virtual void  beginTouch()
	{ 
		return ; 
	}
    
	virtual void  endTouch()
	{
		return ; 
	}
	virtual void  moveTouch()
	{ 
		return ; 
	}

	    
    
protected:
    
    
    
    Ogre::SceneManager* m_pSceneManager;
	

  
    
};

