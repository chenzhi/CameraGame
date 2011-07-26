/**************************************************
被打击对象的队列
***************************************************/


#pragma  once


#include "enemy.h"
#include "EventManager.h"

class Enemy;


typedef std::vector<Ogre::Vector3> PositionList;
typedef std::vector<Enemy*> EnemyCollect;///



class EnemyQueue : public CEventManager
{

public:

	EnemyQueue(const Ogre::Vector3& pos,const  PositionList&EnemyList,const PositionList& FriendList );

	~EnemyQueue();


	/**每帧循环*/
	void update(float time);

	/**获取队列所在的世界节点*/
	Ogre::SceneNode* getSceneNode()const {return m_pRootNode;}

	/**更新碰撞检测*/
	void updateCollision(Bullet* pBullet);


	/**获取世界坐标外框盒*/
	Ogre::AxisAlignedBox getWordBox();


protected:

	
	/**判断是否和射线碰撞
    *@param ray 用来做碰撞的射线
	*@param length 如果碰撞点长度限制
	*@return 如果和射线相交返回真，未击中返回假
	*/
	// bool intersectRay(const Ogre::Ray& ray,float length);
	


	/**销毁所有*/
	void destroy();



protected:



	Ogre::SceneManager*         m_pSceneMrg;      ///场景管理器
	Ogre::SceneNode*            m_pRootNode;

	EnemyCollect                m_ElemyCollect; ///需要打击的对象列表
	EnemyCollect                m_FriendCollect;///不能打击的对像列表










};
