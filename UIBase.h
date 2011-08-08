//
//  UIBase.h
//  ogreApp
//
//  Created by thcz on 11-7-6.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once
#include "SdkTrays.h"


class Widget;

typedef std::vector<Widget*> WidgetCollect;



/**
 游戏的ＵＩ界面的基类，一个实例表示一个游戏页面
*/

class UIBase :public SdkTrayListener
{
public:

	enum Flag
	{
		F_SHOW=1<<1,//需要显示
		F_HIDE=1<<2,//需要隐藏
	};

    
public:
    
    /** 构造函数，
       *@param name uibase名字
       *@param templateName overlay模板的名字
      */
    UIBase(const std::string& name, const std::string& templateName);
    
    
    virtual ~UIBase();
    
    
    /**获取名字*/
    const std::string& getName()const {return m_Name;}
    
    /**初始化*/
    virtual void init();
    
    /**每帧更新数*/
    virtual void update(float time);
    
    
    /**开始触摸,*/
    virtual void onBeginTouch(int x,int y);
    
    
    /**滑动手指*/
    virtual void onMoveTouch(int x,int y);
    
    
    /**手指离开*/
    virtual void onEndTouch(int x,int y);
    
    
    
    /**设置是否可见*/
    virtual void  setVisible(bool b);
    
    
    /**判断是否可见,如果不同见不响应手指事件*/
    virtual bool   isVisible()const ;
    

    /**销毁一个overlayElement和其子对像*/
    static bool destroyOverlayElementAndChild(Ogre::OverlayElement* pOverlay);
    
     /**销毁一个overlay和其子对像*/
    static bool destroyOverlayAndChiled(Ogre::Overlay* pOverlay);
    
    
    /**设置界面的z*/
    void setZorder(unsigned short z);
    
    
    /**获取界面z,如果界面未初始返回0*/
    unsigned short getZorder()const;


	/**加入一个控件*/
	bool registerWidget(Widget* pWidget);

	/**
	*/
	bool unregisterWidget(Widget* pWidget);


	/**根据名字获取控件*/
	Widget* getWidgetByName(const Ogre::String& anem);


	/**设置属性*/
	void    setFlag(Flag flag){m_Flag=flag;}
	void    addFlag(Flag roleFlag){m_Flag|=roleFlag;}
	void    removeFlag(Flag roleFlag){m_Flag&=~roleFlag;}
	unsigned int  getFlag()const {return m_Flag;}
	bool    hasFlag(Flag flag) const   {return (m_Flag&flag)!=0;}

    
    
protected:
    
    /**销毁
       销毁overlay和其子对像
     */
    void destroy();


	/**销毁所有的控件*/
	void destroyAllWidget();


	/**销毁一个控件*/
	void destroyWidget(Widget* pWidget);






    
    std::string m_Name;//// ＵＩ名
    
    std::string m_TemplateName;/// 模板名
    
    Ogre::Overlay* m_pParentOverlay; ///最上层overlay
    
	WidgetCollect m_WidgetCollect;    ///子控件列表

	unsigned int  m_Flag;             ///标记，用来标记属性
    
    
    
    
    
};