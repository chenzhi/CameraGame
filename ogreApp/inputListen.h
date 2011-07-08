//
//  inputListen.h
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE





#ifndef inputListen_h_h_h_h
#define inputListen_h_h_h_h





#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#include "ofPoint.h"

#import  "Accelerometer.h"

class ofxAccelerometerHandler;




class InputListen :public Ogre::Singleton<InputListen>
{
    
public:
    
    InputListen();
    
    ~InputListen();
    
    void  setupInput();
    
    /**开始按下*/
    void TouchBegan();
    
    /**获取输入数据*/
    void Captuer();  
    
    
    const Ogre::Vector3&  getAccelerometerData()const ;
    
    const Ogre::Vector3&  getGyroscopeData()const;
    
    Ogre::Vector3  getSmoothAccelerometer();
    
    Ogre::Vector3  getSmoothGyroscope();
    
protected:
    
    
    void  createInputDevices();
    
    /**销毁所有的输入设备*/
    void  destroyInputDevices();
    
    

    
    
    
    
    protected:
    
    
   
    Accelerometer* m_pAccelerometer;
    
    ofxAccelerometerHandler*        m_AccelerHander;
    ofxAccelerometerHandler*        m_GyroHander;

    
    
    Ogre::Vector3  m_AccelerometerData;
    Ogre::Vector3  m_GyroscopeData;
    
    

};




#endif



#endif
