//
//  Application.h
//  ogreApp
//
//  Created by iMac on 11-6-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#pragma once

#ifndef application_h_h_h_
#define application_h_h_h_  

//#include "ogreConfig.h"
//#include "Ogreplatform.h"


#include "FileSystemLayerImpl.h"
#include  "ofxiPhoneVideoGrabber.h"
//#include "inputListen.h"
#include "Accelerometer.h"

#include "inputListen.h"


class ofxiPhoneVideoGrabber;


class Application :public InputListen
{
    
public:
    
    Application();
    
    ~Application();
    
    
    /**初始化
    */
    void init();
    
    /**销毁所以物体
    */
    void destory();
    
    
    /**初始化ogre渲染器*/
    bool initOgreRender();
    
    /**初始化ogre插件，包括openles都在这里初始化*/
    bool initOgrePlugs();
   
    /**destroy render*/
    void destroyOgreRender();
    
    
    /**每帧更新
    @param time 单位为秒
    */
    void update(float time);
    
    
    /**初始化渲染资源*/
    void initResource();
    
    
    /**初始化输入设备*/
    void initInputDevice();
    
    /***/
    void destroyInputDevice();
    
    
    
    
protected:
    
    /**初始化场景*/
    void initScene();
    
    /**初始化摄像头*/
    void initVideo();
    
    /**更新摄像头*/
    void updateVideo();
    
    /**更新重车计数据，控制摄像头运动*/
    void updateAccelerometer();
    
    /**初始背影板*/
    void initBackGround();
    
    Ogre::Root* m_pRoot;
    
  //  Ogre::StaticPluginLoader mStaticPluginLoader;
    
    Ogre::RenderWindow* m_pRenderWindow;
    
    Ogre::Viewport*     m_pViewPort;
    
    
    Ogre::SceneNode*     m_pCameraNode;
    Ogre::Camera*       m_pCamera;
    
    Ogre::SceneManager*    m_pSceneManager;
    
    OgreBites::FileSystemLayerImpl*    m_pFileSystem;
    
    
#if defined  __arm__
  
    ofxiPhoneVideoGrabber m_pVideo;
#endif
    
    Ogre::TexturePtr    m_pVideoTexture;
    
    Ogre::Entity*      m_pEntity;
    
    ///背影板
    Ogre::Entity*      m_BackGround;
    
   
    
    Accelerometer*  m_Accelerometer;
    
    
    
};











#endif