/*******************************************
模式三的道具类型
*************************************************/


class Enemy;

class Item
{

public:
	Item(const Ogre::String& name)
		:m_pTarget(NULL)
	{}

	virtual ~Item(){}


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

	


protected:

	Enemy*        m_pTarget;///目标点
    
	
};




/*************************************************
鸡蛋道具
*****************************************************/
class EggItem :public Item
{

public:

	/**构造函数
	*@param startPos 开始位置
	*@pEnemy 目标点
	*/
	EggItem(const Ogre::Vector3& startPos,Enemy* pEnemy);

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