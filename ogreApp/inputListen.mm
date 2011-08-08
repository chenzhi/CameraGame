//
//  inputListen.cpp
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "inputListen.h"

#include "UITouch.h"
#include "../Application.h"


namespace Ogre
{
    template<> InputListen*
    Ogre::Singleton<InputListen>::ms_Singleton=NULL;
}

InputListen::InputListen()
:m_AccelerometerData(0,0,0),m_GyroscopeData(0,0,0),m_pAccelerometer(NULL),m_GyroHander(NULL),m_IsDeviceActive(false)
{
  
    setupInput();
}

//--------------------------------
InputListen::~InputListen()
{
    destroyInputDevices();
   return; 
}


//-----------------------------------------------------------------------------
void InputListen::setupInput()
{
   
    
    UIWindow* pWind=[[UIApplication sharedApplication] keyWindow]; 
    if(pWind==nil)
    {
        return ;
    }
    
    
    UITouchView* pUITouch =[[UITouchView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
        
    
    [pUITouch becomeFirstResponder];
    [pUITouch setMultipleTouchEnabled:YES];
    [pUITouch setExclusiveTouch:YES];
    pUITouch.m_pListen=this;
    
    [pWind addSubview: pUITouch];
    
    
    m_pAccelerometer= [[Accelerometer alloc] init];
   // if(m_pAccelerometer.m_IsSupperAccelerometer==YES)
   // {
    //    [m_pAccelerometer startCaptureAccelerometer];
    //}
    
   // if(m_pAccelerometer.m_IsSupeGyroscope==YES)
   // {
     //   [m_pAccelerometer startCaptureGyroscope];
    //}
    
    
    
    m_AccelerHander =new ofxAccelerometerHandler();
    m_GyroHander=new ofxAccelerometerHandler();
    
}


//----------------------------------------------------
void InputListen::createInputDevices()
{

    
 
}


/**开始启用陀螺仪*/
void InputListen::beginGyroscope()
{
     [m_pAccelerometer startCaptureGyroscope];
    m_IsDeviceActive=true;
}

/**结束启用陀螺仪*/
void InputListen::endGyroscope()
{
     [m_pAccelerometer startCaptureGyroscope];
     m_IsDeviceActive=false;
    
}


//------------------------------------------------------
void InputListen::destroyInputDevices()
{
    
    [m_pAccelerometer release];
    delete m_AccelerHander;
    delete m_GyroHander;
}

//---------------------------------------------------------
void InputListen::Captuer()
{
   // if(m_pAccelerometer.m_IsSupperAccelerometer==YES)
   // {
      //  [m_pAccelerometer getAccelerometerX:m_AccelerometerData.x Y:m_AccelerometerData.y Z:m_AccelerometerData.z];
        
        //暂时去掉光滑插值
       // m_AccelerHander->update(m_AccelerometerData.x,m_AccelerometerData.y,m_AccelerometerData.z);
        
   // }
    
   // if(m_pAccelerometer.m_IsSupeGyroscope==YES)
    //{
      //  [m_pAccelerometer getGroyscopeX:m_GyroscopeData.x Y:m_GyroscopeData.y Z:m_GyroscopeData.z];
        
       // m_GyroHander->update(m_GyroscopeData.x,m_GyroscopeData.y,m_GyroscopeData.z);
   // }
    
    if(m_pAccelerometer)
    {
         [m_pAccelerometer getGroyscopeX:m_GyroscopeData.x Y:m_GyroscopeData.y Z:m_GyroscopeData.z];
    }
    
    return ;
}


//----------------------------------------------------------------
const Ogre::Vector3&  InputListen::getAccelerometerData()const
{
    return m_AccelerometerData;
}

//----------------------------------------------------------------
const Ogre::Vector3&  InputListen::getGyroscopeData()const
{
    return m_GyroscopeData;
}

//----------------------------------------------------------------
Ogre::Vector3  InputListen::getSmoothAccelerometer()
{
    ofPoint p=m_AccelerHander->getSmoothOrientation();
    
    return Ogre::Vector3(p.x,p.y,p.z);
    
}

//----------------------------------------------------------------
Ogre::Vector3  InputListen::getSmoothGyroscope()
{

    ofPoint p=m_GyroHander->getSmoothOrientation();
    return Ogre::Vector3(p.x,p.y,p.z);

}

//----------------------------------------------------------------
void InputListen::TouchBegan(int x,int y)
{
    
    Application::getSingleton().TouchBegan(x,y);
}

//----------------------------------------------------------------
void InputListen::TouchEnd(int x, int y)
{
    Application::getSingleton().TouchEnd(x,y);
}

//----------------------------------------------------------------
void InputListen::TouchMove(int x, int y)
{
    Application::getSingleton().TouchMove(x,y);
}

