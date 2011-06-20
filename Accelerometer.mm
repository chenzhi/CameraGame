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
//@synthesize	m_pController;
-(Accelerometer*) init 
{
	if(self = 	[super init]) {
		UIAccelerometer *paccelerometer = [UIAccelerometer sharedAccelerometer];
		paccelerometer.delegate = self;
		paccelerometer.updateInterval = 1.0f/60.0f;
		
		m_pOFHander =new ofxAccelerometerHandler();
	}
	return self;
}

-(void) dealloc
{
	[super	 dealloc];
    UIAccelerometer *paccelerometer = [UIAccelerometer sharedAccelerometer];
    paccelerometer.delegate = nil;
    delete m_pOFHander;
	//delete m_pController;
}


-(void) accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration*)accel
{
	
	m_pOFHander->update(accel.x, accel.y, accel.z);
	
	//float * pMatrix=m_pOFHander->getMatrix();
    
	//[m_pController.m_pXText setText:[NSString stringWithFormat:@"x:%.2f,%.2f,%.2f", pMatrix[0], pMatrix[1], pMatrix[2] ]];
	//[m_pController.m_pYText setText:[NSString stringWithFormat:@"y:%.2f,%.2f,%.2f", pMatrix[4], pMatrix[5], pMatrix[6] ]];
	//[m_pController.m_pZText setText:[NSString stringWithFormat:@"z:%.2f,%.2f,%.2f", pMatrix[8], pMatrix[9], pMatrix[10] ]];
	
}




@end



