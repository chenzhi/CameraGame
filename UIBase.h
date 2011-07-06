//
//  UIBase.h
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once



/**
 游戏的ＵＩ界面的基类，一个实例表示一个游戏页面
*/

class UIBase
{
    
    
public:
    
    /** 构造函数，
       *@param name uibase名字
       *@param templateName overlay模板的名字
      */
    UIBase(const std::string& name, const std::string& templateName);
    
    
    virtual ~UIBase();
    
    
    /**初始化*/
    virtual void init()=0;
    
    /**每帧更新数*/
    virtual void update(float time)=0;
    
    
    /**开始触摸*/
    virtual void onBeginTouch()=0;
    
    
    /**滑动手指*/
    virtual void onMoveTouch()=0;
    
    
    /**手指离开*/
    virtual void onEndTouch()=0;
    
    
    
    /**设置是否可见*/
    void  setVisible(bool b);
    
    
    /**判断是否可见,如果不同见不响应手指事件*/
    bool   isVisible()const ;
    

    /**销毁一个overlay和其子对像*/
    static bool destroyOverlayAndChild(Ogre::OverlayElement* pOverlay);
    
    
    /**设置界面的z*/
    void setZorder(unsigned short z);
    
    
    /**获取界面z,如果界面未初始返回0*/
    unsigned short getZorder()const;
    
    
protected:
    
    std::string m_Name;//// ＵＩ名
    
    std::string m_TemplateName;/// 模板名
    
    Ogre::Overlay* m_pParentOverlay; ///最上层overlay
    
    
    
    
    
    
    
};