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


class BulletManager;

class WarGS :public GameState
{
    
public:
    WarGS();
    
    ~WarGS();
    
    
protected:
    
    void begin();
    
    void end();
    
    virtual StateType update(float time);
    
    void beginTouch();
    
    
    /**更新重车计数据，控制摄像头运动*/
    void updateAccelerometer();

    
protected:
    
    
    void initMode();
    
    void destroyMode();
    
    void updateMode(float time);
    
    
    BulletManager* m_pBulletManager;
    
    Ogre::SceneNode* m_pCameraNode;
    
    Ogre::Entity*      m_pHeadEntity;
    
    
    
    
    
};