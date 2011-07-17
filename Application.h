//
//  Application.h
//  ogreApp
//
//  Created by iMac on 11-6-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#pragma once

 

//#include "ogreConfig.h"
//#include "Ogreplatform.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE

#include "FileSystemLayerImpl.h"
#include  "ofxiPhoneVideoGrabber.h"
#include "Accelerometer.h"


#endif


#include "stateMachine.h"
#include "UIManager.h"


class ofxiPhoneVideoGrabber;
class SdkTrayManager;
class InputListen;


class Application :public Ogre::Singleton<Application>, public StateMachine , public UIManager
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

	/**销毁所有的ogre对像*/
	void destroyOgreRender();
    
    /**初始化ogre插件，包括openles都在这里初始化*/
  //  bool initOgrePlugs();
   

    
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
    


	//*/输入事件，

    /**开始按下*/
    void TouchBegan(int x,int y);
    
     /**手指离开*/
	void TouchEnd(int x,int y);

	/**手指滑动*/
	void TouchMove(int x,int y);


    
    Ogre::RenderWindow* getRenderWindow()const  {return m_pRenderWindow;}


	//*/输入事件结束


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	///开始帧循环,windows平台下使用
	void go();

	///window下函创建窗口函数
	bool  InitWindow(int width,int height);


    static	LRESULT MsgProc(HWND hWnd, DWORD message, WPARAM wParam, LPARAM lParam);

#endif

    
protected:
    
    /**初始化函数，一般在这个函数里注册所有的状态
     *在这个函数里需要手动指定当前活动状态。同时调用活动状态的begin函数
     */
	virtual void  initState();
    

    /**根据手机现在的方向转变ui位置*/
    void transformInputCoordinate(int&x, int &y);
    
    
    
    
    
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
    

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE

    OgreBites::FileSystemLayerImpl*    m_pFileSystem;



#else OGRE_PLATFORM ==OGRE_PLATFORM_WIN32

	HWND  mHwnd;
    HINSTANCE	mInstance;

#endif
    
    
    InputListen*            m_pInputListen;

    SdkTrayManager*           m_pUIManager;
    
    
  
    
};



