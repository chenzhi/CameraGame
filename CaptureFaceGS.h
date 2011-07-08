//
//  CaptureVideoGS.h
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "GameState.h"
#include  "state.h"
#include  "ofxiPhoneVideoGrabber.h"








class CaptureFaceGS : public GameState
{

    
public:
    
    CaptureFaceGS();
    
    
    ~CaptureFaceGS();
    
    
    
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
	
    
    
	virtual void  beginTouch();
	    
	
    
    
protected:
    
    /**初始背影板*/
    void initBackGround();


    /**初始化摄像头*/
    void initVideo();

    /**更新摄像头*/
    void updateVideo();
    
    
    
    

protected:
    
    ///背影板
    Ogre::Entity*      m_BackGround;
    
    Ogre::SceneNode*   m_pCameraNode;
    
    Ogre::TexturePtr   m_pVideoTexture;
    
    
    
#if defined  __arm__

    //ofxiPhoneVideoGrabber* m_pVideo;
#endif
    
    
    UIBase*         m_pCaptureUI;
    
    
};
