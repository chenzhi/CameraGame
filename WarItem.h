/*******************************************
模式三的道具类型
*************************************************/


#pragma  once	


class Enemy;
class WarItem;

enum WarItemType
{
	WIT_NONE,

	WIT_EGG,//鸡蛋

};


class WarItemListen
{
public:
	WarItemListen(){}

	virtual ~WarItemListen(){}
 	virtual void onHitTarget(WarItem* pItem,Enemy* pEnemy)=0;
};



class WarItem
{

public:
	WarItem(const Ogre::String& name,float power,WarItemType type)
		:m_pTarget(NULL),m_PowerValue(power),m_Type(type),m_pListen(NULL)
	{}

	virtual ~WarItem(){}


	///设置目标点
	void setTarget(Enemy* pEnemy) {m_pTarget=pEnemy;}

	///获取目标点
	Enemy* getTarget()const       {return m_pTarget;}


	/**开始使用*/
	virtual void  begin(){}

	/**每帧更新,返回false表示道具使用完成*/
	virtual bool  update(float time){return true;}

	/**结束*/
	virtual void end(){}

	/**获取能量点数*/
	float getPower()const {return m_PowerValue;}

	void setPower(float power){m_PowerValue=power;}

	WarItemType getType()      {return m_Type;}

	
	/**设置监听*/
	void setListen(WarItemListen* pListen){m_pListen=pListen;}


	/**广播打击中了目标*/
	 void fireHitTarget()
	 {
		 if(m_pListen!=NULL)
		 {
			 m_pListen->onHitTarget(this,m_pTarget);
		 }
	 }


protected:

	Enemy*        m_pTarget;///目标点

	float         m_PowerValue;///击中后加多少照像点数

	WarItemType       m_Type;

	WarItemListen*    m_pListen; ///监听
    
	
};


typedef std::vector<WarItem*> WarItemCollect;



/*************************************************
鸡蛋道具
*****************************************************/
class EggItem :public WarItem
{

public:

	/**构造函数
	*@param startPos 开始位置
	*@pEnemy 目标点
	*/
	EggItem(/*const Ogre::Vector3& startPos,Enemy* pEnemy*/);

	virtual ~EggItem();

	/**开始使用*/
	virtual void  begin();

	/**每帧更新*/
	virtual bool   update(float time);

	/**结束*/
	virtual void end();

protected:

	////初始化实体
	void initEtity();

	///消毁实体
	void destroyEntiy();

	/**判断是否击中目标点*/
	bool hitTarget();




	Ogre::Vector3    m_StartPos;///初始位置

	Ogre::SceneNode* m_pParentNode;///节点

	Ogre::Entity*    m_pEntity;    ///模型实体
	
	Ogre::Vector3    m_pRotateDir;///旋转方向


	float            m_liftTime;///生命周期


}
;