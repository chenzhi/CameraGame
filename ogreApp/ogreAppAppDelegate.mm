//
//  ogreAppAppDelegate.m
//  ogreApp
//
//  Created by iMac on 11-6-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//





#import "ogreAppAppDelegate.h"

//#import "ogreAppViewController.h"

@implementation ogreAppAppDelegate


@synthesize m_pTimer;
@synthesize m_LastFrameTime;


-(void) setLastFrameTime:(NSTimeInterval)frameInterval
{
    if(frameInterval>=1)
    {
        m_LastFrameTime=frameInterval;
    }
}

-(void) go
{
    NSAutoreleasePool* pool=[[NSAutoreleasePool alloc] init];
    try
    {
        m_Application=new Application();
        m_Application->init();
       
       
        
    }catch(Ogre::Exception& e)
    {
        std::cerr<<"an exception has occurred"<<e.getFullDescription().c_str()<<std::endl;
    }
    
    if(m_DisplayLinkSupported)
    {
        m_pDate=[[NSDate alloc] init];
        m_LastFrameTime=-[m_pDate timeIntervalSinceNow];
        m_DisplayLink=[NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(renderOneFrame:)];
        [m_DisplayLink setFrameInterval:m_LastFrameTime];
        [m_DisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    }else
    {
        m_pTimer=[NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)(1.0/60.0f)*m_LastFrameTime
                                                  target:self selector:@selector(renderOneFrame:)
                                                userInfo:nil repeats:YES];
        
    }
    
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:)
                                                 name:UIDeviceOrientationDidChangeNotification object:nil];
    
    [pool release];
}






- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    // Override point for customization after application launch.
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES];
    m_DisplayLinkSupported=FALSE;
    m_DisplayLink=nil;
    m_pTimer=nil;
    
  
    //*/
#define USE_CADISPLAYLINK
#ifdef  USE_CADISPLAYLINK
    
    NSString*reSysVer=@"3.1";
    NSString*currSysVer=[[UIDevice currentDevice] systemVersion];
                                                                
    if([currSysVer compare:reSysVer options:NSNumericSearch] != NSOrderedAscending)
    {
        m_DisplayLinkSupported=TRUE;
    }
    
#endif
    
    
    [self go];

    
}



- (void)applicationWillResignActive:(UIApplication *)application
{
       Ogre::Root::getSingleton().saveConfig();
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];

}

- (void)applicationDidEnterBackground:(UIApplication *)application
{  
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
   }

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:)
                                                 name:UIDeviceOrientationDidChangeNotification object:nil];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    Ogre::Root::getSingleton().queueEndRendering();
    [[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
    
    if (m_DisplayLinkSupported)
    {
        [m_pDate release];
        m_pDate = nil;
        
        [m_DisplayLink invalidate];
        m_DisplayLink = nil;
    }
    else
    {
        [m_pTimer invalidate];
        m_pTimer = nil;
    }
    
    m_Application->destory();
    delete m_Application;
    m_Application=NULL;
    
}


-(void)orientationChanged:(NSNotification*)notification
{
    return ;
   // size_t v=0;
   // Ogre::Root::getSingleton().getAutoCreatedWindow()->getCustomAttribute("VIEW",&v);
   // [(UIView*)v setNeedsLayout];
}


-(void)renderOneFrame:(id)sender
{
    // [sb.mGestureView becomeFirstResponder];
    if(m_DisplayLinkSupported)
    {
        NSTimeInterval currentFrameTime=-[m_pDate timeIntervalSinceNow];
        NSTimeInterval differenceinSeconds=currentFrameTime-m_LastFrameTime;
        m_LastFrameTime=currentFrameTime;
        m_Application->update((float)differenceinSeconds);
        
    }else
    {
    
        m_Application->update((float) [m_pTimer timeInterval]);
    }
}






@end


 
//static ogreAppAppDelegate appDelegate;

int main(int argc, char *argv[])
{
    
    /*/
     NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
     int retVal = UIApplicationMain(argc, argv, nil, nil);
     [pool release];
     return retVal;
     //*/
    
    
    
    //*
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	int retVal = UIApplicationMain(argc, argv,nil, @"ogreAppAppDelegate");
	[pool release];
	return retVal;
    //*/
}



 
//*/
