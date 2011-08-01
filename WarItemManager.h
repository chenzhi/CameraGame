/**************************************************************
道具管理器，用来负责道具的创建和销毁
****************************************************************/


#pragma once 

#include "WarItem.h"

class WarItemManager :public Ogre::Singleton<WarItemManager>
{
public:

	typedef WarItem*  (WarItemManager::*createFun)();
	typedef std::vector<std::pair<WarItemType ,createFun> > CreateFunCollect;

public:

	WarItemManager();


	~WarItemManager(){destroyWarItem();}




	/**创建一个道具
	*@param itemtype 道具类型
	*/
	WarItem*  createWarItem(WarItemType  itemtype);

	/**创建道具
	*@see createWarItem
	*/
	WarItem*  createWarItem(const Ogre::String& typeName);


	/**每帧更新*/
	void update(float time);


	/**销毁道具*/
	void destroy(WarItem* pItem);

protected:

	/**销毁所有的道具*/
	void destroyWarItem();


	/**添加一个创建类型*/
	bool addItemType(WarItemType itemtype,createFun);

	/**移除一个创建类型*/
	bool removeItemtype(WarItemType itemtype);

	/**查打一个创建函数*/
	createFun  findCrateFun(WarItemType itemtype);


protected:

	/**创建鸡蛋道具函数*/
	WarItem* createEggItem();

    /**内部函数，把类型转了字符串
	*/
	Ogre::String itemTypeToString(WarItemType itemType);
	
	/**内部函数把字符串转成类型
	*/
	WarItemType stringToItemtype(const Ogre::String& itemtype);


protected:




	WarItemCollect            m_WarItemCollect;///所有道具的列表。
	WarItemCollect            m_RemoveItemCollect;

	CreateFunCollect          m_CreateFunCollect;///创建函数列表



};