//
//  WarGS.h
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once


#include "GameState.h"
//#include "Bullet.h"


class WarManager;
class WarMode;
typedef std::vector<WarMode*>WarModeCollect;
class WarGS :public GameState
{
    
public:
    WarGS();
    
    ~WarGS();
    
    
protected:
    

    void begin();
    
    void end();
    
    virtual StateType update(float time);
    
    /**更新重力计数据，控制摄像头运动*/
    void updateAccelerometer();

    
protected:


	///初始化ui
	void intiUI();

	///销毁ui
	void destroyUI();
   

	void beginTouch(int x,int y);
    
    ///初始化视频贴图
    void initVideoTeture();


	/**初始化所有的战斗模式*/
	void initWarMode();

	/**销毁所有的战争模式*/
	void destroyWarMode();
    
    /**初始背影板*/
    void initBackGround();
    
    /**销毁背景板*/
    void destroyBackGround();
    
    
    
protected:
    
    
  
    
    
    WarManager* m_pWarManager;
    
    Ogre::SceneNode* m_pCameraNode;


//	WarModeCollect m_WarModeCollect;
	WarMode*       m_ActiveWarMode;
	

	UIBase*        m_pUIPause;
    
    
    
    ///背影板
    Ogre::Entity*      m_BackGround;
    
    Ogre::TexturePtr   m_pVideoTexture;

};