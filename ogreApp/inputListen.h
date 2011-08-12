//
//  inputListen.h
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#pragma once



#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#include "../ofPoint.h"
#import  "Accelerometer.h"
class ofxAccelerometerHandler;

class InputListen :public Ogre::Singleton<InputListen>
{
public:
	 InputListen();

#else if OGRE_PLATFORM ==OGRE_PLATFORM_WIN32

#include "ois/ois.h"


#ifdef _DEBUG

#pragma comment(lib,"ois_d.lib")

#else
#pragma comment(lib,"ois.lib")

#endif

class InputListen :public Ogre::Singleton<InputListen>,public OIS::KeyListener, public OIS::MouseListener
{
public:

	 InputListen(HWND wnd);

#endif


    
public:
    
   
    
    ~InputListen();
    
    
    void  setupInput();
    
    
    /**开始启用陀螺仪*/
    void beginGyroscope();
    
    /**结束启用陀螺仪*/
	void endGyroscope();
    
    
    /**判断陀螺仪是否启用*/
    bool isGyroscopeActive()const{return m_IsDeviceActive;}
    
    
    /**开始按下*/
    void TouchBegan(int x,int y);

	/**手指离开*/
	void TouchEnd(int x, int y);

	/**手指滑动*/
	void TouchMove(int x, int y);

    
    /**获取输入数据*/
    void Captuer();  
    



    
    const Ogre::Vector3&  getAccelerometerData()const ;
    
    const Ogre::Vector3&  getGyroscopeData()const;
    
    Ogre::Vector3  getSmoothAccelerometer();
    
    Ogre::Vector3  getSmoothGyroscope();


#if OGRE_PLATFORM ==OGRE_PLATFORM_WIN32


	/**OIS回调函数*/
	bool mouseMoved(const OIS::MouseEvent &arg);

	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	bool keyPressed(const OIS::KeyEvent &arg);

	bool keyReleased(const OIS::KeyEvent &arg);

#endif


    
protected:
    
    
    void  createInputDevices();
    
    /**销毁所有的输入设备*/
    void  destroyInputDevices();
    
    

    
    
    
    
    protected:
    
    
   
#if OGRE_PLATFORM ==OGRE_PLATFORM_IPHONE

    Accelerometer* m_pAccelerometer;
    ofxAccelerometerHandler*        m_AccelerHander; ///重力记
    ofxAccelerometerHandler*        m_GyroHander;    ///陀螺仪

    
#else if OGRE_PLATFORM==OGRE_PLATFORM_WIN32



	HWND                    m_wnd;                      ///win32窗口句柄
	OIS::InputManager*		mInputManager;				// 输入管理类
	OIS::Mouse*				mMouse;						// 鼠标
	OIS::Keyboard*			mKeyboard;					// 键盘


#endif
        
        bool       m_IsDeviceActive;///判断是否设备是否启用


		Ogre::Vector3  m_AccelerometerData;
		Ogre::Vector3  m_GyroscopeData;



};



