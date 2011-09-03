/**************************************************
被打击对象的队列
***************************************************/


#pragma  once


#include "enemy.h"
#include "EventManager.h"

class Enemy;


typedef std::vector<Ogre::Vector3> PositionList;
typedef std::vector<Enemy*> EnemyCollect;///



class EnemyQueue : public CEventManager ,public ActiveContainer
{

public:

	enum EQST
	{
      EQ_NORMAl,         //正常状态
	//  EQ_LOVE,             //示爱
	  EQ_RUNAWAY,          //逃跑
	  EQ_SWALLOWBALL,      ///含球
	  EQ_DISACTIVE,      //生命周期结束
	};


public:

	EnemyQueue(const Ogre::Vector3& pos,const  PositionList&EnemyList,const PositionList& FriendList );

	~EnemyQueue();


	/**每帧循环*/
    EQST   update(float time);

	/**获取队列所在的世界节点*/
	Ogre::SceneNode* getSceneNode()const {return m_pRootNode;}

	/**更新碰撞检测*/
	void updateCollision(Bullet* pBullet);


	/**获取世界坐标外框盒*/
	Ogre::AxisAlignedBox getWordBox();

	/**获取生命周期*/
	float getLeftTime()const{return m_leftTime;}

	/**设置生命周期*/
	void  setLeftTime(float time){m_leftTime=time;}

	

protected:

	/**开始逃跑*/
	void startRunaway();

	/**开始示爱*/
	void startLove();


	/**更新感谢状态后消息*/
	void updateThankState(float time);


	/**更新逃跑状态*/
	void updateLevelState(float time);
    
    /**正常状态更新*/
    void updateNormal(float time);

	
	/**更新示爱*/
	void updateLove(float time);

	/**更新含球状态*/
	void updateSwallowBall(float time);

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
	bool  hasFriendKilled() const ;

	/**所有敌人是否都被打死*/
	bool  isEnemyAllKilled() const ;

	/**是否所有敌人都被击中*/
	bool  isHitAllEnemy() const ;
             
	/**是否有含球状的的目标*/
	bool  hasSwallowBallEnemy()const;


protected:



	Ogre::SceneManager*         m_pSceneMrg;      ///场景管理器
	Ogre::SceneNode*           m_pRootNode;

	EnemyCollect             m_ElemyCollect; ///需要打击的对象列表
	EnemyCollect             m_FriendCollect;///不能打击的对像列表

	EQST                       m_State;
	float                      m_currentLeftTime;       ///当前生命值
	//Ogre::Vector3              m_LevelPoint;      ///飞到幕后的目标点
	float                      m_leftTime;        ///生命周期
    








};
