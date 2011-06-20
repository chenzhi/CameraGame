//
//  inputListen.cpp
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "inputListen.h"




InputListen::InputListen()
:mWindow(NULL)
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
   
    
   // mWindow->getCustomAttribute("WINDOW", &winHandle);
   // winHandleStr << winHandle;
    
    
}


//----------------------------------------------------
void InputListen::createInputDevices()
{

    
 
}


//------------------------------------------------------
void InputListen::destroyInputDevices()
{
    
}

//---------------------------------------------------------
void InputListen::Captuer()
{
    
}

