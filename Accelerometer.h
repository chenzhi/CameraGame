//
//  Accelerometer.h
//  ogreApp
//
//  Created by thcz on 11-6-17.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#ifndef  accelerometer_h_h_h_h
#define  accelerometer_h_h_h_h

#import <Foundation/Foundation.h>
//#import "AccelerometerViewController.h"
#include "ofPoint.h"

//@class AccelerometerViewController;

//@clas

@interface Accelerometer : NSObject < UIAccelerometerDelegate>
{
    
	//AccelerometerViewController* m_pController;
	
	ofxAccelerometerHandler*        m_pOFHander;
    
}




//@property(retain,nonatomic)AccelerometerViewController* m_pController;

@end



#endif