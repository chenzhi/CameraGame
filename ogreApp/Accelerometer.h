//
//  Accelerometer.h
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#ifndef  accelerometer_h_h_h_h
#define  accelerometer_h_h_h_h


#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE




#import <Foundation/Foundation.h>
#import <CoreMotion/CoreMotion.h>

//#import "AccelerometerViewController.h"
#include "ofPoint.h"

//@class AccelerometerViewController;

//@clas

@interface Accelerometer : NSObject 
{
    
	//AccelerometerViewController* m_pController;
	
	    
    CMMotionManager*            motionManager;  
    
    BOOL  m_IsSupperAccelerometer;
    BOOL  m_IsSupeGyroscope;
}


@property (nonatomic, retain) CMMotionManager *motionManager;
@property (nonatomic)  BOOL  m_IsSupperAccelerometer;
@property (nonatomic)  BOOL  m_IsSupeGyroscope;

//@property(retain,nonatomic)AccelerometerViewController* m_pController;

-(BOOL) startCaptureAccelerometer;

-(BOOL) startCaptureGyroscope;

-(BOOL) getAccelerometerX:(float&)x Y:(float&)y Z:(float&)z;

-(BOOL) getGroyscopeX:(float&)x Y:(float&)y Z:(float&)z;

@end



#endif


#endif