#include "pch.h"
#include "WarItemManager.h"




WarItemManager* Ogre::Singleton<WarItemManager>::ms_Singleton=NULL;


WarItemManager::WarItemManager()
{

	addItemType(WIT_EGG,(&WarItemManager::createEggItem));



}


//----------------------------------------------------------------------------
WarItem*  WarItemManager::createWarItem(WarItemType itemtype)
{

	createFun fun=findCrateFun(itemtype);

	assert(fun);

	return 	(this->*fun)();

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
WarItem* WarItemManager::createEggItem()
{
	WarItem* pItem=	new EggItem();
	m_WarItemCollect.push_back(pItem);
	return pItem;
}