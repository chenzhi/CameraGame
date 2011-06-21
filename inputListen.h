//
//  inputListen.h
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef inputListen_h_h_h_h
#define inputListen_h_h_h_h


#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>









class InputListen 
{
    
public:
    
    InputListen();
    
    ~InputListen();
    
    void  setupInput();
    
    /**开始按下*/
    virtual void TouchBegan() {}
    
    /**获取输入数据*/
    void Captuer();  
    
    
    
protected:
    
    
    void  createInputDevices();
    
    /**销毁所有的输入设备*/
    void  destroyInputDevices();
    
    

    
    
    
    
    protected:
    
    
   
    
    

};








#endif
