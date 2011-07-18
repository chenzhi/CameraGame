//
//  ogreAppAppDelegate.h
//  ogreApp
//
//  Created by iMac on 11-6-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

//#ifndef OgreAppAppDelegate_h_h_h_h
//#define OgreAppAppDelegate_h_h_h_h



#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>



#include "../Application.h"

//@class ogreAppViewController;

@interface ogreAppAppDelegate : NSObject <UIApplicationDelegate> 
{
    NSTimer*  m_pTimer;    
    Application* m_Application;
    id m_DisplayLink;
    NSDate* m_pDate;
    NSTimeInterval m_LastFrameTime;
    BOOL m_DisplayLinkSupported;
    

}

-(void)go;
-(void)renderOneFrame:(id)sender;
-(void)orientationChanged:(NSNotification*) notification;




@property (retain) NSTimer* m_pTimer;

@property (nonatomic) NSTimeInterval m_LastFrameTime;

@end



//#endif