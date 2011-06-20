//
//  inputListen.cpp
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "inputListen.h"




InputListen::InputListen()
{
  
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
        
    [pWind addSubview: pUITouch];
    [pUITouch becomeFirstResponder];
    [pUITouch setMultipleTouchEnabled:YES];
    [pUITouch setExclusiveTouch:YES];
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

