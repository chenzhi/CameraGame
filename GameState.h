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
    
    ///初始化ＵＩ ,子类如果需要初始化ui重载这个函数,begin里会被调用
    virtual  void initUI(){};
    
    ///销毁状态机里的ＵＩ，子类如果需要销毁ＵＩ重载此函数，在end函数里被调用
    virtual  void destroyUI(){};
    
    
    
    Ogre::SceneManager* m_pSceneManager;
	

  
    
};

