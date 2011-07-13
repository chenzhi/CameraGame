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
    
   
    
    
    /**更新重车计数据，控制摄像头运动*/
    void updateAccelerometer();

    
protected:
    


	void beginTouch(int x,int y);
    
    ///初始化视频贴图
    void initVideoTeture();
    
  
    
    
    BulletManager* m_pBulletManager;
    
    Ogre::SceneNode* m_pCameraNode;

    
    
    
};