#include "pch.h"
#include "WarItemManager.h"




template<> WarItemManager* Ogre::Singleton<WarItemManager>::ms_Singleton=NULL;


WarItemManager::WarItemManager()
{

	initItemTypeInformation();

	//addItemType(WIT_EGG,(&WarItemManager::createEggItem));



}


WarItemManager::~WarItemManager()
{
    destroyWarItem();
}


WarItem*  WarItemManager::createWarItem(const Ogre::String& typeName)
{

	WarItemType itemType=stringToItemtype(typeName);
	
	return createWarItem(itemType);



}

//----------------------------------------------------------------------------
WarItem*  WarItemManager::createWarItem(WarItemType itemtype)
{

	//createFun fun=findCrateFun(itemtype);

	//assert(fun);

	Ogre::String meshName;
	Ogre::String textureName;

	 ItemInformat itemTypeInformation;
	if(getItemTypeMeshAndTexture(itemtype,itemTypeInformation)==false)
		return NULL;

	WarItem* pItem=new  EggItem(itemTypeInformation.m_MeshName,itemTypeInformation.m_Texture,itemTypeInformation.m_Power);
	m_WarItemCollect.push_back(pItem);

	return pItem ;
	//return 	(this->*fun)(meshName,textureName);

}


//----------------------------------------------------------------------------
void WarItemManager::update(float time)
{


	///删除上一帧需要删除的对像
	WarItemCollect::iterator it = m_RemoveItemCollect.begin();
	WarItemCollect::iterator endit=m_RemoveItemCollect.end();
	for(;it!=endit;++it)
	{

		WarItemCollect::iterator eraseIt=std::find(m_WarItemCollect.begin(),m_WarItemCollect.end(),(*it));
		if(eraseIt!=m_WarItemCollect.end())
		{
			m_WarItemCollect.erase(eraseIt);
		}

		SafeDelete(*it);
	}
	m_RemoveItemCollect.clear();




	it=m_WarItemCollect.begin();
	endit=m_WarItemCollect.end();

	for(;it!=endit;++it)
	{
		///如果已经完成。进入删除队列
		if((*it)->update(time)==false)
		{
         m_RemoveItemCollect.push_back(*it);

		}
	}
	return ;


}


//----------------------------------------------------------------------------
void WarItemManager::destroy(WarItem* pItem)
{
	if(pItem==NULL)
		return ;

	WarItemCollect::iterator it=std::find(m_WarItemCollect.begin(),m_WarItemCollect.end(),pItem);
	if(it!=m_WarItemCollect.end())
	{
		SafeDelete(*it);
		m_WarItemCollect.erase(it);
	}
	return ;
}

//----------------------------------------------------------------------------
void WarItemManager::destroyWarItem()
{

	WarItemCollect::iterator it=m_WarItemCollect.begin();
	WarItemCollect::iterator endit=m_WarItemCollect.end();

	for(;it!=endit;++it)
	{
		SafeDelete(*it);
	}

	m_WarItemCollect.clear();
    
    
    it = m_RemoveItemCollect.begin();
	endit=m_RemoveItemCollect.end();
	for(;it!=endit;++it)
	{
		SafeDelete(*it);
	}
	m_RemoveItemCollect.clear();

    
    
    
    


}

//----------------------------------------------------------------------------
bool WarItemManager::addItemType(WarItemType itemtype,createFun fun)
{

	if(findCrateFun(itemtype)!=NULL)
	{
		Ogre::LogManager::getSingleton().logMessage("add item type fun failed ,has this itmtype create fun");
		return false;
	}

	m_CreateFunCollect.push_back(std::make_pair(itemtype,fun));
	return true;
}

//----------------------------------------------------------------------------
bool WarItemManager::removeItemtype(WarItemType itemtype)
{
	CreateFunCollect::iterator it=m_CreateFunCollect.begin();
	CreateFunCollect::iterator itend=m_CreateFunCollect.end();
	for(;it!=itend;++it)
	{
		if(it->first==itemtype)
		{
			m_CreateFunCollect.erase(it);
			return true;
		}

	}
	return false;
}

//----------------------------------------------------------------------------
WarItemManager::createFun  WarItemManager::findCrateFun(WarItemType itemtype)
{
	CreateFunCollect::iterator it=m_CreateFunCollect.begin();
	CreateFunCollect::iterator itend=m_CreateFunCollect.end();
	for(;it!=itend;++it)
	{
        if(it->first==itemtype)
		{
			return it->second;
		}

	}
	return NULL;
}


//----------------------------------------------------------------------------
Ogre::String WarItemManager::itemTypeToString(WarItemType itemType)
{
	switch (itemType)
	{
	case  WIT_EGG:
		{
			return "egg";
		}
	
	default:
		{
			assert(0);
			break;
		}

	}


	return "";
}
	
//----------------------------------------------------------------------------
WarItemType WarItemManager::stringToItemtype(const Ogre::String& itemtype)
{
	if(itemtype=="egg")
	{
		return WIT_EGG;
	}
	return WIT_NONE;
}




//----------------------------------------------------------------------------
//WarItem* WarItemManager::createEggItem(const Ogre::String&MeshName,const Ogre::String&textureName)
//{
//	WarItem* pItem=	new EggItem(MeshName,textureName);
//    pItem->begin();
//	m_WarItemCollect.push_back(pItem);
//	return pItem;
//}


//----------------------------------------------------------------------------
bool WarItemManager::getItemTypeMeshAndTexture(WarItemType itemType,ItemInformat& itemTypeInfor)
{
	ItemInformationCollect::iterator it=m_ItemInformation.begin();
	ItemInformationCollect::iterator itend=m_ItemInformation.end();

	for(;it!=itend;++it)
	{
		if((*it).m_ItemType==itemType)
		{
          itemTypeInfor.m_MeshName=(*it).m_MeshName;
		  itemTypeInfor.m_Texture=(*it).m_Texture;
		  itemTypeInfor.m_Power=(*it).m_Power;
		  itemTypeInfor.m_ItemType=itemType;
		  return true;
		}
	}

	return false;

}


void WarItemManager::initItemTypeInformation()
{

	ItemInformat Item={WIT_EGG,"jidan.mesh","danqin.png",1.5f}; 
	m_ItemInformation.push_back(Item);

	Item.m_ItemType=WIT_BRICK;
	Item.m_MeshName="banzhuan.mesh";
	Item.m_Texture="banzhuan.png";
	Item.m_Power=2.0f;
	m_ItemInformation.push_back(Item);


	Item.m_ItemType=WIT_STICK;
	Item.m_MeshName="gunzi.mesh";
	Item.m_Texture="";
	Item.m_Power=2.0f;
	m_ItemInformation.push_back(Item);



	Item.m_ItemType=WIT_SHOE;
	Item.m_MeshName="xiezi.mesh";
	Item.m_Texture="xiezi.png";
	Item.m_Power=1.0f;
	m_ItemInformation.push_back(Item);


	Item.m_ItemType=WIT_KNIFE;
	Item.m_MeshName="caidao.mesh";
	Item.m_Texture="";
    Item.m_Power=2.0f;
	m_ItemInformation.push_back(Item);




	//Item.m_ItemType=
	//WIT_BRICK, //板砖
	//WIT_SHOE,//鞋子
	//WIT_BENCH,//板登
	//WIT_STICK,//棍子


	  
}