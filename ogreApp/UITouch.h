//
//  UITouch.h
//  ogreApp
//
//  Created by thcz on 11-6-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


#include "inputListen.h"


//class InputListen;

@interface UITouchView : UIView
{
    
    InputListen* m_pListen;
    
}


@property(nonatomic) InputListen* m_pListen;





@end
