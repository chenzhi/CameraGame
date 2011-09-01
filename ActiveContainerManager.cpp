#include "pch.h"
#include "ActiveContainerManager.h"
#include "ActiveContainer.h"

template<> ActiveContainerManager*
Ogre::Singleton<ActiveContainerManager>::ms_Singleton=NULL;


//------------------------------------------------------------------
ActiveContainerManager::ActiveContainerManager()
{

}


//------------------------------------------------------------------
ActiveContainerManager::~ActiveContainerManager()
{

}


//------------------------------------------------------------------
bool  ActiveContainerManager::addContainer(ActiveContainer* pContainer)
{
	assert(pContainer);

	AcitveContainerVector::iterator it=std::find(m_AcitveContainerVector.begin(),m_AcitveContainerVector.end(),pContainer);
	if(it!=m_AcitveContainerVector.end())
	{
		return false;
	}

	it=std::find(m_AddVector.begin(),m_AddVector.end(),pContainer);
	if(it!=m_AddVector.end())
	{
	  return  false;
	}

	it=std::find(m_RemoveVector.begin(),m_RemoveVector.end(),pContainer);
	if(it!=m_RemoveVector.end())
	{
		return  false;
	}


	m_AddVector.push_back(pContainer);


	return true;


}


//------------------------------------------------------------------
void ActiveContainerManager::update(float time)
{

	AcitveContainerVector::iterator itbegin=m_AddVector.begin();
	AcitveContainerVector::iterator itend= m_AddVector.end();
	for(;itbegin!=itend;++itbegin)
	{
		(*itbegin)->begin();
		m_AcitveContainerVector.push_back(*itbegin);
	}
	m_AddVector.clear();


	

	itbegin=m_AcitveContainerVector.begin();
	itend= m_AcitveContainerVector.end();
	for(;itbegin!=itend;++itbegin)
	{
	    if((*itbegin)->updateActive(time)==false)
		{
			m_RemoveVector.push_back(*itbegin);
		}
	}


	itbegin=m_RemoveVector.begin();
	itend= m_RemoveVector.end();
	for(;itbegin!=itend;++itbegin)
	{
		(*itbegin)->end();
		AcitveContainerVector::iterator reit=std::find(m_AcitveContainerVector.begin(),m_AcitveContainerVector.end(),(*itbegin));
	    assert(reit!=m_AcitveContainerVector.end());
		m_AcitveContainerVector.erase(reit);
	
	}

	m_RemoveVector.clear();




}

//------------------------------------------------------------------
bool  ActiveContainerManager::removeContainer(ActiveContainer* pContainer)
{

	AcitveContainerVector::iterator it=std::find(m_AcitveContainerVector.begin(),m_AcitveContainerVector.end(),pContainer);
	if(it!=m_AcitveContainerVector.end())
	{
		m_AcitveContainerVector.erase(it);
		return  true;
	}

	it=std::find(m_AddVector.begin(),m_AddVector.end(),pContainer);
	if(it!=m_AddVector.end())
	{
		m_AddVector.erase(it);
		return  true;
	}

	it=std::find(m_RemoveVector.begin(),m_RemoveVector.end(),pContainer);
	if(it!=m_RemoveVector.end())
	{
		m_RemoveVector.erase(it);
		return  true;
	}

	return  false;

}

