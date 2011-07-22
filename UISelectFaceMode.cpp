#include "pch.h"
#include  "UISelectFaceMode.h"
#include "Application.h"

/**************************************************************/

//----------------------------------------------------------
UserSelectMode::UserSelectMode(const Ogre::String& faceMesh,const Ogre::String&headMesh)
:m_currentTime(0.0f),m_isRoll(false),m_pNode(NULL),m_pFaceEntity(NULL),m_pHeadEntity(NULL)
{
	Ogre::SceneManager* pSceneMrg=Application::getSingletonPtr()->getMainSceneManager();
	m_pNode=pSceneMrg->getRootSceneNode()->createChildSceneNode();

	m_pFaceEntity=pSceneMrg->createEntity(faceMesh);
	m_pHeadEntity=pSceneMrg->createEntity(headMesh);

	if(m_pFaceEntity->hasSkeleton()&&m_pHeadEntity->hasSkeleton())
	{
		m_pHeadEntity->shareSkeletonInstanceWith(m_pFaceEntity);
	}

	m_pNode->attachObject(m_pFaceEntity);
	m_pNode->attachObject(m_pHeadEntity);



}


//----------------------------------------------------------
UserSelectMode::~UserSelectMode()
{

	Ogre::SceneManager* pSceneMrg=Application::getSingletonPtr()->getMainSceneManager();
	m_pNode->detachAllObjects();
	pSceneMrg->getRootSceneNode()->removeAndDestroyChild(m_pNode->getName());
	m_pNode=NULL;
	pSceneMrg->destroyEntity(m_pHeadEntity);
	pSceneMrg->destroyEntity(m_pFaceEntity);
	m_pHeadEntity=NULL;
	m_pFaceEntity=NULL;

	return ;
}


//----------------------------------------------------------
void UserSelectMode::update(float time)
{
	///如果不需要移动返回
	if(m_isRoll==false)
		return ;

	m_currentTime+=time;
    
	updatePos(m_currentTime);
	if(m_currentTime>=1.0f)
	{
		reset();
	}

	return ;

}

//----------------------------------------------------------
void UserSelectMode::setFaceMesh(const Ogre::String& faceMesh)
{
	
    Ogre::SceneManager* pSceneMrg=Application::getSingletonPtr()->getMainSceneManager();
	if(m_pFaceEntity!=NULL)
	{
		m_pNode->detachObject(m_pFaceEntity);
        pSceneMrg->destroyEntity(m_pFaceEntity);
	}
	m_pFaceEntity=pSceneMrg->createEntity(faceMesh);


}

//----------------------------------------------------------
void UserSelectMode::setHeadMesh(const Ogre::String& headMesh)
{

	Ogre::SceneManager* pSceneMrg=Application::getSingletonPtr()->getMainSceneManager();
	if(m_pHeadEntity!=NULL)
	{
		m_pNode->detachObject(m_pHeadEntity);
		pSceneMrg->destroyEntity(m_pHeadEntity);
	}

 	m_pHeadEntity=pSceneMrg->createEntity(headMesh);

}


//----------------------------------------------------------
bool UserSelectMode::isIntersect(const  Ogre::Ray& ray)
{
	const  Ogre::AxisAlignedBox& box=m_pNode->_getWorldAABB();
	float d1=0,d2=0;
	return  Ogre::Math::intersects(ray,box,&d1,&d2);
}


void UserSelectMode::reset()
{
	m_orginPos=m_pNode->getPosition();
	m_targetPos=m_orginPos;
	m_currentTime=0.0f;
	m_isRoll=false;

}

///移动到指定位置
void UserSelectMode::translate(const Ogre::Vector3& pos)
{
	m_targetPos=pos;
	m_currentTime=0.0f;
	m_isRoll=true;

}

void UserSelectMode::updatePos(float precent)
{
	if(precent>=1.0f)
	{
		m_pNode->setPosition(m_targetPos);
		return ;
	}

	Ogre::Vector3 temPos=m_orginPos+(m_targetPos-m_orginPos)*precent;
	m_pNode->setPosition(temPos);

}

void UserSelectMode::setVisible(bool b)
{
	m_pNode->setVisible(b);
}

//--------------------------------------
void UserSelectMode::setPosition(float x,float y,float z)
{
	m_pNode->setPosition(Ogre::Vector3(x,y,z));

}




/***********************************************************/


//----------------------------------------------------------
UISelectFaceMode::UISelectFaceMode()
:UIBase("UISelectFaceMode","")
{


}


//----------------------------------------------------------
UISelectFaceMode::~UISelectFaceMode()
{


   destroyAllFaceMode();

}


//----------------------------------------------------------
void UISelectFaceMode::init()
{
     UIBase::init();

	 /**创建三个模型用来做为不同脸型的选择*/

	 UserSelectMode* pMode=new UserSelectMode("face.mesh","Head.mesh");
	 m_FaceModeCollect.push_back(pMode);
	 pMode->setPosition(-2.0f,0.0f,0.0f);


	 
	 pMode=new UserSelectMode("face.mesh","Head.mesh");
	 m_FaceModeCollect.push_back(pMode);
	 pMode->setPosition(0.0f,0.0f,0.0f);


	 pMode=new UserSelectMode("face.mesh","Head.mesh");
	 m_FaceModeCollect.push_back(pMode);
	 pMode->setPosition(2.0f,0.0f,0.0f);




	return ;

}


//----------------------------------------------------------
void  UISelectFaceMode::setVisible(bool b)
{

	setUserSelctModeVisible(b);

}





//----------------------------------------------------------
void UISelectFaceMode::setUserSelctModeVisible(bool b)
{
	FaceModeCollect::iterator it=m_FaceModeCollect.begin();
	FaceModeCollect::iterator endit=m_FaceModeCollect.end();
	for(;it!=endit;++it)
	{
		(*it)->setVisible(b);
	}

	return ;

}


void UISelectFaceMode::onEndTouch(int x,int y)
{
	UIBase::onEndTouch(x,y);

	///判断是否有拾取一个模型

	Ogre::Camera* pCamera=Application::getSingleton().getMainCamera();
	
	Ogre::Ray pickRay;

	float w = Application::getSingleton().getRenderWindows()->getViewport(0)->getActualWidth();
	float  h= Application::getSingleton().getRenderWindows()->getViewport(0)->getActualHeight();
	pCamera->getCameraToViewportRay(x/w,y/h,&pickRay);



	FaceModeCollect::iterator it=m_FaceModeCollect.begin();
	FaceModeCollect::iterator endit=m_FaceModeCollect.end();
	for(;it!=endit;++it)
	{
		if(	(*it)->isIntersect(pickRay))
		{

			Application::getSingleton().getCurrentActive()->setNextStateType(ST_WAR);
			return ;
		}
	}




}


///销毁所有脸部模型
void  UISelectFaceMode::destroyAllFaceMode()
{

	FaceModeCollect::iterator it=m_FaceModeCollect.begin();
	FaceModeCollect::iterator itend=m_FaceModeCollect.end();

	for(;it!=itend;++it)
	{
		delete (*it);
	}

	m_FaceModeCollect.clear();


}