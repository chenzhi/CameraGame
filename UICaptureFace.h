//
//  UICaptureFace.h
//  ogreApp
//
//  Created by thcz on 11-7-7.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
/****************************************
 捕获人脸界面
*****************************************/

#include "UIBase.h"





class UICaptureFace :public UIBase
{
    
public:
    
    UICaptureFace();
    
    
    ~UICaptureFace();


	/**初始化*/
	virtual void init();
    

    
    
protected:
    

	/**开始触摸,*/
	virtual void onBeginTouch(int x,int y);


	/**滑动手指*/
	virtual void onMoveTouch(int x,int y);


	/**手指离开*/
	virtual void onEndTouch(int x,int y);



	virtual void buttonHit(Button* button);
    
    
    
};