//
//  UIManager.h
//  ogreApp
//
//  Created by thcz on 11-7-7.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

/****************************************************************
 管理ui界面
************************************************************/

#pragma once


class UIBase;

typedef std::vector<UIBase*> UICollect;

class UIManager
{
    
public:
    UIManager();
    
    ~UIManager();
    
    
    /**注册一个ui,成功返回真，失败返回假*/
    bool registerUI(UIBase* pUI);
    
    
    /**注销一个ui,不销毁*/
    bool unregisterUI(UIBase* pUI);
    
    
    /**通过名字获取一个ui,无返回空*/
    UIBase* getUIByName(const std::string& name);
    
    
    /**每帧更新*/
    void update(float time);
    
    
    /**消毁一个ui*/
    void destroyUI(UIBase* pUI);
    
    void destroyUI(const std::string& name);
    
    
    /**销毁所有的ui*/
    void destroyAll();
    
    
    protected:
    
    
    UICollect m_UICollect;
    
    
    
};