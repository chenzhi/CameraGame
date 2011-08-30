/******************************************
管理和驱动所有activeContainer类
********************************************/


#pragma once





class ActiveContainer;


typedef std::vector<ActiveContainer*> AcitveContainerVector;

class ActiveContainerManager : public Ogre::Singleton<ActiveContainerManager>
{

public:

	ActiveContainerManager();

	~ActiveContainerManager();


	/**加入一个ActiveContainer
	*如果是已经存在就不再加入返回false
	*/
	bool  addContainer(ActiveContainer* pContainer);


	/**移除一个activeContainer*/
	bool  removeContainer(ActiveContainer* pContainer);


   /**每帧更新*/
	void update(float time);




protected:


	AcitveContainerVector m_AcitveContainerVector;  ///当前活动

	AcitveContainerVector m_AddVector;             ///新加入的容器
	AcitveContainerVector m_RemoveVector;          ///需要移除的容器



};