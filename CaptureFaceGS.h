//
//  CaptureVideoGS.h
//  ogreApp
//
//  Created by thcz on 11-6-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "GameState.h"
#include  "state.h"
#include  "ogreapp/ofxiPhoneVideoGrabber.h"






class UISelectUser;
class UICaptureFace;
class UIBase;
class CaptureFaceGS : public GameState
{

    
public:
    
    CaptureFaceGS();
    
    
    ~CaptureFaceGS();
    
    
    
    /**
     *状态开始函数,
     */
	virtual void  begin( );
    
	/**
     *状态结束函数
     */
	virtual void  end( );
    
    
	/**更新函数*/
	virtual StateType update(float time);
	
    
    
	virtual void  beginTouch(int x,int y);
	    
	
    
    
protected:
    
   


    /**初始化摄像头*/
   // void initVideo();

    /**更新摄像头*/
    //void updateVideo();
    
    

	
    


protected:


	///ui相关函数
	void initUI();


	void destroyUI();


protected:
    
    
    
    Ogre::SceneNode*   m_pCameraNode;
    
       

    
    
    
#if defined  __arm__

    //ofxiPhoneVideoGrabber* m_pVideo;
#endif
    
    
    UICaptureFace*         m_pCaptureUI;///捕获脸

	UISelectUser*         m_pSelectUserUI;///选择用户

	UIBase*               m_pSelectHeadUI;///选择头套

	UIBase*               m_pSelectFaceUI;//选择脸型
    
    
};
