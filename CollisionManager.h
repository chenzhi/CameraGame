//
//  CollisionManager.h
//  ogreApp
//
//  Created by thcz on 11-6-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//


#pragma once


#include "btBulletDynamicsCommon.h"

/// 简单封装bullet库文

class CollisionManager : public Ogre::Singleton<CollisionManager>
{
    
public:
    CollisionManager();
    
    
    ~CollisionManager();
    
    
    /**创建一个刚体物体
       *@param radius 半径
       *@param mass 重量
       *@param 绑定的ogre实体
       */
    btRigidBody* createRigidBody(float radius,float mass,Ogre::SceneNode* pNode);
    
    
    
    ///初始化
    void init();
    
    ///消毁所有的物理物体
    void destroy();
    
    ///每帧更新
    void update(float time);
    
    ///设置重力
    void setGravity(float x,float y, float z);
    
    
    
    
    
    
protected:
    
    
    btDiscreteDynamicsWorld*         m_pDynamicsWorld;
    btCollisionConfiguration*        m_pCollisionConfig;
    btCollisionDispatcher*          m_pCollisionDispatcher;
    btSequentialImpulseConstraintSolver*  m_pConstraintSolver;
    btBroadphaseInterface*          m_pBroadphase;
    
    
    btAlignedObjectArray<btCollisionShape*> m_CollisionShapes;
    btAlignedObjectArray<btRigidBody*>    m_BoxBodies;
    
};