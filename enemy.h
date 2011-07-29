//
//  enemy.h
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once

#include "EventManager.h"


class Bullet;




#define EnemyMask 0x0100



///敌人事件，
enum EnemyEvent
{
	EE_Hit,//被击上事件
	EE_Die,//死亡事件
};




class Enemy :public CEventManager
{
    
public:
    
    enum EnemyState
    {
        ES_NORMAL, ///出现，未受伤时状态
        ES_DODGE, ////已经变打中，找飞的状态
        ES_DEATH, ///死亡状态
    };
    
    
    
    public:
    
    /**构造函数
     *@param meshName mesh文件名
     *@param pos     出现的初始位
     */
	Enemy(const Ogre::String& meshName,const Ogre::String& headMesh,const Ogre::Vector3&  pos, Ogre::SceneNode* pParent);

    
    ~Enemy();
    
    
    
    /**被打中时的回调
     *@param hitPos 打中的点
     *@param pBullet 打中的子弹
     */
    virtual void onHit(const Ogre::Vector3& hitPos,Bullet* pBullet );
    
    
    ///
    void setVisible(bool b);
    
    
    ///
    virtual void update(float time);
    
    
    
    ///获取名字
    const std::string& getEntityName()const;
    
    
    ///获取生命值
    float getLeftValue()const{return m_LifeValue;}
        
    ///设置生命值
    void  setLeftValue(float value){m_LifeValue=value;}

    
    ///重置,在指定的位置重新出现
    void reset(const Ogre::Vector3& pos);
    
    ///获取状态
    EnemyState getState()const {return m_State;}   


	///获取场景节点
	Ogre::SceneNode* getSceneNode()const {return m_pNode;}


	/**播放一个动画
	*@param aniName 动画名
	*@param loop 是否循环播放
	*@param fadetime 动作过流的时间.如果小于1直接播放无过渡
	*/
	bool playAnimation(const Ogre::String& aniName,bool loop,float fadetime);


	/**更新动画*/
	void updateAnimation(float time);


	/**判断是否和射线碰撞
    *@param ray 用来做碰撞的射线
	*@param length 如果碰撞点长度限制
	*@return 如果和射线相交返回真，未击中返回假
	*/
	virtual bool intersectRay(const Ogre::Ray& ray,float length);


	/**注册一个事件监听
	*@param EEevent 敌人事件
	*@param f 注册的类函数指针
	*@param obj 临听类实例指针
	*/
	template<typename T >
	bool registerEvent(EnemyEvent EEevent, void (T::*f)( Enemy *) , T * obj )
	{
		return CEventManager::registerMessageHandle(EEevent,f,obj );
	}

	/**注销事件*/
	template<typename T >
	bool unregisterEven(EnemyEvent EEevent,T*obj)
	{
		return CEventManager::unregisterMessageHandle(EEevent,obj);
	}
	

	/**设置hit贴图*/
	bool  setHitEffectTextureName(const Ogre::String& textureName); 

protected:
    
    ///死亡
    void death();
    
    ///消毁
    void destroy();
    
    
    ///更新出现时
    void updateNormal(float time);
    
    ///
    void updateDodge(float time);
    
    ///
    void updateDeath(float time);
    
    
    
    Ogre::Entity*     m_pEntity;

    Ogre::SceneNode*  m_pNode;

    Ogre::SceneManager* m_pSceneMrg;

    Ogre::AnimationState* m_pAniSate;

    static int     m_EntityIndex;
 
    float        m_LifeValue;///生命值
    
    EnemyState      m_State;///状态
    
    ///被击中后的旋转 
    float         m_Rotate;
    
    ///被击中后向哪个方向运动多
    Ogre::Vector3     m_Trans;

    Ogre::MaterialPtr    m_pMaterial;

	Ogre::Entity*        m_pHeadEnity;

	float                m_HurtTime;///受伤的时间

	float                m_AniFade;///动作过渡时间
    
    
    
};