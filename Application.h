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
#include "Accelerometer.h"
#include "inputListen.h"
#include "stateMachine.h"
#include "UIManager.h"


class ofxiPhoneVideoGrabber;
class SdkTrayManager;

class Application :public Ogre::Singleton<Application>, StateMachine , UIManager
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
    
    /**返回场景的的主摄像机节点*/
    Ogre::SceneNode* getMainCameraNode()const {return m_pCameraNode;}
    
    
    /**返回主摄像*/
    Ogre::Camera*   getMainCamera()const{return m_pCamera;}

    
    
    /**返回场景管理器*/
    Ogre::SceneManager* getMainSceneManager()const {return m_pSceneManager;}
    
    
    /**开始按下*/
    void TouchBegan();

    
protected:
    
    /**初始化函数，一般在这个函数里注册所有的状态
     *在这个函数里需要手动指定当前活动状态。同时调用活动状态的begin函数
     */
	virtual void  initState();
    

    
    
    
protected:
    
   
    
    
protected:
    
    /**初始化场景*/
    void initScene();
    
       
 
    
       
      
    Ogre::Root* m_pRoot;
    
  //  Ogre::StaticPluginLoader mStaticPluginLoader;
    
    Ogre::RenderWindow* m_pRenderWindow;
    
    Ogre::Viewport*     m_pViewPort;
    
    
    Ogre::SceneNode*     m_pCameraNode;
    Ogre::Camera*       m_pCamera;
    
    Ogre::SceneManager*    m_pSceneManager;
    
    OgreBites::FileSystemLayerImpl*    m_pFileSystem;
    
    

    InputListen*            m_pInputListen;
    
    SdkTrayManager*           m_pUIManager;
    
    
    
    
    
};











#endif