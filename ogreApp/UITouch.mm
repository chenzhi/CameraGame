//
//  UITouch.m
//  ogreApp
//
//  Created by thcz on 11-6-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "UITouch.h"



@implementation UITouchView


@synthesize  m_pListen;

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event 
{
    
    if(m_pListen==NULL)
    {
        return ;
    }
    
    UITouch* pTouch=[touches anyObject]; 
    CGPoint point=[pTouch locationInView:self];
    m_pListen->TouchEnd(point.x,point.y);

   
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event 
{
    
    if(m_pListen==NULL)
    {
        return ;
    }
    
    UITouch* pTouch=[touches anyObject]; 
    CGPoint point=[pTouch locationInView:self];
    m_pListen->TouchMove(point.x,point.y);

    
    
   
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
   
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event 
{
    if(m_pListen==NULL)
    {
        return ;
    }
    
    UITouch* pTouch=[touches anyObject]; 
    CGPoint point=[pTouch locationInView:self];
    
    
    
   //// int w = m_pRenderWindow->getViewport(0)->getActualWidth();
   // int h = m_pRenderWindow->getViewport(0)->getActualHeight();

    m_pListen->TouchBegan(point.x,point.y);
    
    
    
    return ; 
}


@end
