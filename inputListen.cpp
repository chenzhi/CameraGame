//
//  inputListen.cpp
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "inputListen.h"




InputListen::InputListen()
:mInputMgr(NULL),mMouse(NULL),mAccelerometer(NULL),mWindow(NULL)
{
  
}

//--------------------------------
InputListen::~InputListen()
{
    destroyInputDevices();
   return; 
}


//-----------------------------------------------------------------------------
void InputListen::setupInput(Ogre::RenderWindow* pRenderWindow)
{
    mWindow=pRenderWindow;
    OIS::ParamList pl;
    size_t winHandle = 0;
    std::ostringstream winHandleStr;
    
    mWindow->getCustomAttribute("WINDOW", &winHandle);
    winHandleStr << winHandle;
    
    pl.insert(std::make_pair("WINDOW", winHandleStr.str()));
    
    mInputMgr = OIS::InputManager::createInputSystem(pl);
    
    createInputDevices();      // create the specific input devices
    
    //windowResized(mWindow);    // do an initial adjustment of mouse area
}


//----------------------------------------------------
void InputListen::createInputDevices()
{

    mMouse = static_cast<OIS::MultiTouch*>(mInputMgr->createInputObject(OIS::OISMultiTouch, true));
    mMouse->setEventCallback(this);

    mAccelerometer = static_cast<OIS::JoyStick*>(mInputMgr->createInputObject(OIS::OISJoyStick, true));
    mAccelerometer->setEventCallback(this);

 
}


//------------------------------------------------------
void InputListen::destroyInputDevices()
{
    if (mInputMgr)
    {
        mInputMgr->destroyInputObject(mAccelerometer);
        mInputMgr->destroyInputObject(mMouse);
        OIS::InputManager::destroyInputSystem(mInputMgr);
        mInputMgr = 0;
    }

}

//---------------------------------------------------------
void InputListen::Captuer()
{
    
    mAccelerometer->capture();
    mMouse->capture();

}



bool InputListen::axisMoved( const OIS::JoyStickEvent &ayrg, int axis )
{
    
    size_t AxisSize=ayrg.state.mAxes.size();
    
  
    for(int i=0; i<AxisSize; ++i)
    {
        OIS::Axis axis=ayrg.state.mAxes[i];
        
        Ogre::stringstream stream;
        stream<<"AxisIndex is" << i<<" Axisabs "<< axis.abs <<" Axis relate is"<<axis.rel;
        
        Ogre::LogManager::getSingleton().logMessage(Ogre::String(stream.str()));
        
    }

    return true;
    
}

//-- Not so common control events, so are not required --//
//! Joystick Event, and sliderID
bool InputListen::sliderMoved( const OIS::JoyStickEvent &, int index)
{
    return true;

}

//! Joystick Event, and povID
bool InputListen::povMoved( const OIS::JoyStickEvent &arg, int index)
{
    return true;

}

//! Joystick Event, and Vector3ID
bool InputListen::vector3Moved( const OIS::JoyStickEvent &arg, int index)
{
    return true;

}



bool InputListen::touchMoved( const OIS::MultiTouchEvent &arg )
{
    return true;

}

bool InputListen::touchPressed( const OIS::MultiTouchEvent &arg )
{
    return true;

}

bool InputListen::touchReleased( const OIS::MultiTouchEvent &arg )
{
    return true;

}


bool InputListen::touchCancelled( const OIS::MultiTouchEvent &arg )
{
    return true;

}