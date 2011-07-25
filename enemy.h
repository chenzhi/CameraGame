//
//  enemy.h
//  ogreApp
//
//  Created by thcz on 11-6-27.
//  Copyright 2011�� __MyCompanyName__. All rights reserved.
//


#pragma once

#include "EventManager.h"


class Bullet;




#define EnemyMask 0x0100



///�����¼���
enum EnemyEvent
{
	EE_Hit,//�������¼�
	EE_Die��//�����¼�
};




class Enemy :public CEventManager
{
    
public:
    
    enum EnemyState
    {
        ES_NORMAL, ///���֣�δ����ʱ״̬
        ES_DODGE, ////���˺���
        ES_DEATH, ///����״̬
    };
    
    
    
    public:
    
    /**���캯��
     *@param meshName mesh�ļ���
     *@param pos     ���ֵĳ�ʼλ
     */
	Enemy(const Ogre::String& meshName,const Ogre::Vector3&  pos, Ogre::SceneNode* pParent);

    
    ~Enemy();
    
    
    
    /**������ʱ�Ļص�
     *@param hitPos ���еĵ�
     *@param pBullet ���е��ӵ�
     */
    virtual void onHit(const Ogre::Vector3& hitPos,Bullet* pBullet );
    
    
    ///
    void setVisible(bool b);
    
    
    ///
    void update(float time);
    
    
    
    ///��ȡ����
    const std::string& getEntityName()const;
    
    
    ///��ȡ����ֵ
    float getLeftValue()const{return m_LeftValue;}
        
    ///��������ֵ
    void  setLeftValue(float value){m_LeftValue=value;}

    
    ///����,��ָ����λ�����³���
    void reset(const Ogre::Vector3& pos);
    
    ///��ȡ״̬
    EnemyState getState()const {return m_State;}   


	///��ȡ�����ڵ�
	Ogre::SceneNode* getSceneNode()const {return m_pNode;}


	/**�ж��Ƿ��������ײ
    *@param ray ��������ײ������
	*@param length �����ײ�㳤������
	*@return ����������ཻ�����棬δ���з��ؼ�
	*/
	bool intersectRay(const Ogre::Ray& ray,float length);


	/**ע��һ���¼�����
	*@param EEevent �����¼�
	*@param f ע����ຯ��ָ��
	*@param obj ������ʵ��ָ��
	*/
	template<typename T >
	bool registerEvent(EnemyEvent EEevent, void (T::*f)( Enemy *) , T * obj )
	{
		return CEventManager::registerMessageHandle(EEevent,f,obj );
	}

	/**ע���¼�*/
	template<typename T >
	bool unregisterEven(EnemyEvent EEevent,T*obj)
	{
		return CEventManager::unregisterMessageHandle(EEevent,obj);
	}
	

protected:
    
    ///����
    void death();
    
    ///����
    void destroy();
    
    
    ///���³���ʱ
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
    
    
    float        m_LeftValue;///����ֵ
    
    EnemyState      m_State;///״̬
    
    
    ///�����к����ת 
    float         m_Rotate;
    
    ///�����к����ĸ������˶���
    Ogre::Vector3     m_Trans;
    
    Ogre::MaterialPtr    m_pMaterial;


	Ogre::Entity*        m_pHeadEnity;
    
    
    
};