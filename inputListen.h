//
//  inputListen.h
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef inputListen_h_h_h_h
#define inputListen_h_h_h_h









class InputListen :public OIS::MultiTouchListener,OIS::JoyStickListener
{
    
public:
    
    InputListen();
    
    ~InputListen();
    
    void  setupInput(Ogre::RenderWindow* pRenderWindow);
    
    
    
    /**获取输入数据*/
    void Captuer();  
    
protected:
    
    
    void  createInputDevices();
    
    /**销毁所有的输入设备*/
    void  destroyInputDevices();
    
    
protected:
    
    /** @remarks Joystick axis moved event */
    virtual bool axisMoved( const OIS::JoyStickEvent &arg, int axis );
    
    //-- Not so common control events, so are not required --//
    //! Joystick Event, and sliderID
    virtual bool sliderMoved( const OIS::JoyStickEvent &, int index);
    
    //! Joystick Event, and povID
    virtual bool povMoved( const OIS::JoyStickEvent &arg, int index);    
    
    //! Joystick Event, and Vector3ID
    virtual bool vector3Moved( const OIS::JoyStickEvent &arg, int index);
    
    /** @remarks Joystick button down event */
    virtual bool buttonPressed( const OIS::JoyStickEvent &arg, int button ){return true;}
    
    /** @remarks Joystick button up event */
    virtual bool buttonReleased( const OIS::JoyStickEvent &arg, int button) {return true;}
    
       
    
    protected:
    
    virtual bool touchMoved( const OIS::MultiTouchEvent &arg );
    
    virtual bool touchPressed( const OIS::MultiTouchEvent &arg );
    
    virtual bool touchReleased( const OIS::MultiTouchEvent &arg );
    
    virtual bool touchCancelled( const OIS::MultiTouchEvent &arg );

    
    
    protected:
    
    
    OIS::InputManager* mInputMgr;   // OIS input manager

    OIS::MultiTouch* mMouse;        // multitouch device
    OIS::JoyStick* mAccelerometer;  // accelerometer device
    Ogre::RenderWindow* mWindow;

    
    

};








#endif
