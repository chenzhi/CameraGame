//
//  CollisionManager.cpp
//  ogreApp
//
//  Created by thcz on 11-6-24.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#include "pch.h"
#include "CollisionManager.h"


#define MAX_PROXIES 8192

template<> CollisionManager* Ogre::Singleton<CollisionManager>::ms_Singleton=NULL;



CollisionManager::CollisionManager()
:m_pDynamicsWorld(NULL),m_pCollisionConfig(NULL),m_pCollisionDispatcher(NULL),m_pConstraintSolver(NULL),m_pBroadphase(NULL)
{
    
    init();
}


CollisionManager::~CollisionManager()
{
    destroy();
}


//-----------------------------------
void CollisionManager::init()
{
       
	m_pCollisionConfig = new btDefaultCollisionConfiguration();
	
	///the maximum size of the collision world. Make sure objects stay within these boundaries
	///Don't make the world AABB size too large, it will harm simulation quality and performance
	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_pBroadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,MAX_PROXIES);
	m_pCollisionDispatcher = new btCollisionDispatcher(m_pCollisionConfig);
	m_pConstraintSolver = new btSequentialImpulseConstraintSolver;
	m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pCollisionDispatcher,m_pBroadphase,m_pConstraintSolver,m_pCollisionConfig);
	m_pDynamicsWorld->setGravity(btVector3(0,0,0));

}


///设置重力
void CollisionManager::setGravity(float x,float y, float z)
{
    m_pDynamicsWorld->setGravity(btVector3(x,y,z));
    
    return ;
}

//-----------------------------------
btRigidBody* CollisionManager::createRigidBody(float radius,float mass,Ogre::SceneNode* pNode)
{
    
    
    
    return NULL;
}

//-----------------------------------
void CollisionManager::update(float time)
{
    
   	if (m_pDynamicsWorld)
    {
		m_pDynamicsWorld->stepSimulation(time,4);
    }

    return ;
    
}


//------------------------------------------
void CollisionManager::destroy()
{
    
    //remove the rigidbodies from the dynamics world and delete them
	for (int i=m_pDynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_pDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_pDynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}
    
    
	//delete collision shapes
	for (int j=0;j<m_CollisionShapes.size();j++)
	{
		btCollisionShape* shape = m_CollisionShapes[j];
		m_CollisionShapes[j] = 0;
		delete shape;
	}
    
    m_CollisionShapes.clear();
    
    
    ///cleanup Bullet stuff
	delete m_pDynamicsWorld;
	m_pDynamicsWorld =NULL;
	delete m_pConstraintSolver;
	m_pConstraintSolver=NULL;;
	delete m_pCollisionDispatcher;
	m_pCollisionDispatcher=NULL;;
	delete m_pBroadphase;
	m_pBroadphase=NULL;;
	delete m_pCollisionConfig;
	m_pCollisionConfig=NULL;

    return ;
}