/**************************************************************
道具管理器，用来负责道具的创建和销毁
****************************************************************/


#pragma once 

#include "WarItem.h"

class WarItemManager :public Ogre::Singleton<WarItemManager>
{
public:

	typedef WarItem*  (WarItemManager::*createFun)(const Ogre::String&MeshName,const Ogre::String&textureName);
	typedef std::vector<std::pair<WarItemType ,createFun> > CreateFunCollect;


	///道具种类的
	struct ItemInformat
	{
		WarItemType          m_ItemType;//类型id
		Ogre::String         m_MeshName;//模型名字
		Ogre::String         m_Texture;//贴图名
		float                m_Power;///攻击力

	};



public:

	WarItemManager();


	~WarItemManager();




	/**创建一个道具
	*@param itemtype 道具类型
	*@p
	*/
	WarItem*  createWarItem(WarItemType  itemtype);

	/**创建道具
	*@param typeName  类型名
	*@param  MeshName 道具模型文件名.
	*@param  textureName 贴图名
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
	//WarItem* createEggItem(const Ogre::String&MeshName,const Ogre::String&textureName);

    /**内部函数，把类型转了字符串
	*/
	Ogre::String itemTypeToString(WarItemType itemType);
	
	/**内部函数把字符串转成类型
	*/
	WarItemType stringToItemtype(const Ogre::String& itemtype);


	/**初始化道具类型信息*/
	void initItemTypeInformation();


	/**根据类型查找到相应的模型名*/
	bool  getItemTypeMeshAndTexture(WarItemType itemType,ItemInformat& itemTypeInfor);



protected:




	WarItemCollect            m_WarItemCollect;///所有道具的列表。
	WarItemCollect            m_RemoveItemCollect;
	CreateFunCollect          m_CreateFunCollect;///创建函数列表


	
	
	typedef std::vector<ItemInformat> ItemInformationCollect;
	ItemInformationCollect    m_ItemInformation;



};