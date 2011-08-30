

/***********************************************
动作类
****************************************************/

#pragma  once 

/**动作监听类*/
class ActiveListen
{
public:

	virtual void onBegin(){}

	virtual void onEnd(){}



};







class Active
{

public:

	Active()
		:m_pListen(NULL){}

	virtual ~Active(){}

	/**开始动作*/
	virtual void  begin()
	{
		if(m_pListen!=NULL)
		{
			m_pListen->onBegin();
		}
	}

	 /**每帧更新,返回false表示完成*/
	virtual bool   update(float time){ return true;}

	/**结束动作*/
	virtual void  end()
	{
		if(m_pListen!=NULL)
		{
			m_pListen->onEnd();
		}
	}

	void  setListen(ActiveListen* pListen)
	{
		m_pListen=pListen;
	}

protected:
	

	ActiveListen*      m_pListen;


};
typedef  std::vector<Active*> ActitveVector;




/**动作队列，把多个动作连成一个大动作，队列里所有的动作依次
运行，直到所有动作都完成了，整个动作动队列结束*/

class ActiveQueue :public Active
{
public:

	ActiveQueue(){}

    virtual 	~ActiveQueue();

	/**在最后面加入一个动作*/
	void         addActive(Active* pActive);


	/**开始动作*/
	virtual void  begin();

    /**每帧更新*/
	virtual bool   update(float time);

	/**结束动作*/
	virtual void  end();

	
protected:

	/**删除所有动作*/
	void  destroyAllActive();


	ActitveVector           m_ActiveVector;   ///动作列表

	ActitveVector::iterator m_CurrentIterator;//当前活动的动作

};










/**********************************************************
///从当前朝向旋转到哪个朝向
***********************************************************/
class RotateToActive :public Active
{
public:

	/**构造函数
	*@param pTarget 需要转旋的结节点
	*@param quat    转到的目标朝向
	*@param time    完成需要的总时间
	*/
	RotateToActive(Ogre::SceneNode* pTarget,const Ogre::Quaternion& quat,float time);


	~RotateToActive();


	/**开始动作*/
	virtual void  begin();

	/**每帧更新*/
	virtual bool   update(float time);

	/**结束动作*/
	virtual void  end();



protected:

	Ogre::SceneNode*           m_pTarget;              ///旋转目标
	Ogre::Quaternion           m_pTargetQuater;        ///目标朝向
	Ogre::Quaternion           m_OrignQuater;          ///当前朝向
	float                      m_LeftTime;             ///完成总时间
	float                      m_CurrentTime;          ///当前时间


};



/******************************************************************
从当前位置位移到指定的目标点
*****************************************************************/
class MoveToActive :public Active
{

public:

	MoveToActive(Ogre::SceneNode* pTarget,const Ogre::Vector3& TargetPosition,float time );

	~MoveToActive(){}

	/**开始动作*/
	virtual void  begin();

	/**每帧更新*/
	virtual bool   update(float time);

	/**结束动作*/
	virtual void  end();



protected:

	Ogre::SceneNode*           m_pTarget;              ///旋转目标
	Ogre::Vector3              m_TargetPosition;        ///目标朝向
	Ogre::Vector3              m_OrignPosition;          ///当前朝向
	float                      m_LeftTime;             ///完成总时间
	float                      m_CurrentTime;          ///当前时间

};