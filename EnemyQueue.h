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

	enum EQST
	{
      EQ_NORMAl,//正常状态
	  EQ_KILLALLENEMY,///所有敌人被打死
	  EQ_KILLFRIEND,//杀死了友人。

	  EQ_DISACTIVE,//非活动状态
	};


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

	/**更新感谢状态后消息*/
	void updateThankState(float time);



	/**更新逃跑状态*/
	void updateLevelState(float time);
    
    /**正常状态更新*/
    void updateNormal(float time);

	
	/**判断是否和射线碰撞
    *@param ray 用来做碰撞的射线
	*@param length 如果碰撞点长度限制
	*@return 如果和射线相交返回真，未击中返回假
	*/
	// bool intersectRay(const Ogre::Ray& ray,float length);
	


	/**销毁所有*/
	void destroy();


	/**敌人被击中通知*/
	void notifyEnemyHit(Enemy* pEnemy);


	/**是否有队友对像被打死*/
	bool  hasFriendKilled();

	/**所有敌人是否都被打死*/
	bool  isEnemyAllKilled();


protected:



	Ogre::SceneManager*         m_pSceneMrg;      ///场景管理器
	Ogre::SceneNode*           m_pRootNode;

	EnemyCollect             m_ElemyCollect; ///需要打击的对象列表
	EnemyCollect             m_FriendCollect;///不能打击的对像列表

	EQST                   m_State;
	float                  m_loveTime;       ///示爱时间
	Ogre::Vector3              m_LevelPoint;      ///飞到幕后的目标点
    








};
