//
//  Accelerometer.m
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#import "Accelerometer.h"
//#import "AccelerometerViewController.h"




@implementation Accelerometer
@synthesize	motionManager,m_IsSupperAccelerometer,m_IsSupeGyroscope;


-(Accelerometer*) init 
{
	if(self = [super init])
    {
		
       
        self.motionManager = [[[CMMotionManager alloc] init] autorelease];
        
        m_IsSupeGyroscope=motionManager.gyroAvailable;
        m_IsSupperAccelerometer=motionManager.accelerometerAvailable;
        if (motionManager.accelerometerAvailable) 
        {
            motionManager.accelerometerUpdateInterval = 1.0/30.0;
           
        }
        
        
        if (motionManager.gyroAvailable) 
        {
            motionManager.gyroUpdateInterval = 1.0/30.0;
           // [motionManager startGyroUpdates];
        } 
        
		
		}
	return self;
}

-(void) dealloc
{
    [super dealloc];
    [self.motionManager release];
   	//delete m_pController;
}



-(BOOL) startCaptureAccelerometer
{
    if(m_IsSupperAccelerometer==YES)
    {
     [motionManager startAccelerometerUpdates];
     return YES;
    }
    return NO;
}

-(BOOL) startCaptureGyroscope
{
    if(m_IsSupeGyroscope==YES)
    {
        [motionManager startGyroUpdates];
        return YES;
    }
    
    return NO;
    
}




-(BOOL) getAccelerometerX:(float&)x Y:(float&)y Z:(float&)z
{
    if(m_IsSupperAccelerometer==NO)
    {
        return NO;
    }
    
    CMAccelerometerData *accelerometerData = motionManager.accelerometerData;
    x= accelerometerData.acceleration.x;
    y= accelerometerData.acceleration.y;
    z= accelerometerData.acceleration.z;
    return YES;
    
}


-(BOOL) getGroyscopeX:(float&)x Y:(float&)y Z:(float&)z
{
    if(m_IsSupeGyroscope==NO)
    {
        return NO;
    }
    
    CMGyroData *gyroData = motionManager.gyroData;
    
    x=gyroData.rotationRate.x;
    y=gyroData.rotationRate.y;
    z=gyroData.rotationRate.z;
    
    return YES;

}








@end



