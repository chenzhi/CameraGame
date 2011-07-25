#include "pch.h"
#include  "UISelectFaceMode.h"
#include "Application.h"
#include "Config.h"

/**************************************************************/

//----------------------------------------------------------
UserSelectMode::UserSelectMode(const Ogre::String& faceMesh,const Ogre::String&headMesh)
:m_currentTime(0.0f),m_isRoll(false),m_pNode(NULL),m_pFaceEntity(NULL),m_pHeadEntity(NULL),m_pAnimation(NULL)
{
	Ogre::SceneManager* pSceneMrg=Application::getSingletonPtr()->getMainSceneManager();
	m_pNode=pSceneMrg->getRootSceneNode()->createChildSceneNode();

	m_pFaceEntity=pSceneMrg->createEntity(faceMesh);
	m_pHeadEntity=pSceneMrg->createEntity(headMesh);

	//if(m_pFaceEntity->hasSkeleton()&&m_pHeadEntity->hasSkeleton())
	//{
	//	m_pHeadEntity->shareSkeletonInstanceWith(m_pFaceEntity);
	//}

	m_pNode->attachObject(m_pFaceEntity);
	m_pNode->attachObject(m_pHeadEntity);


	m_pAnimation=m_pFaceEntity->getAnimationState("shiai");
	if(m_pAnimation!=NULL)
	{
		m_pAnimation->setLoop(true);
		m_pAnimation->setEnabled(true);
		m_pAnimation->setTimePosition(0);
	}


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
	m_pAnimation=NULL;

	return ;
}


//----------------------------------------------------------
void UserSelectMode::update(float time)
{
	updateOrientation();

		if(m_pAnimation!=NULL)
	{
		m_pAnimation->addTime(time);
	}
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

//-------------------------------------------------------------------------
void UserSelectMode::setPosition(float x,float y,float z)
{
	m_pNode->setPosition(Ogre::Vector3(x,y,z));

	updateOrientation();

}

//-------------------------------------------------------------------------
void UserSelectMode::updateOrientation()
{

	if(m_pNode==NULL)
		return ;

	//m_pNode->rotate(Ogre::Vector3::UNIT_Y,Ogre::Radian(0.01f));
	//return ;

	Ogre::Camera* pCamera=Application::getSingleton().getMainCamera();
	Ogre::Vector3 camPos= pCamera->getParentNode()->getPosition();
	Ogre::Vector3 facePos=m_pNode->getPosition();


	Ogre::Vector3 dir=camPos-facePos;
	dir.normalise();
	//dir=-dir;

	Ogre::Vector3 up(0.0f,1.0f,0.0f);

	Ogre::Vector3 right=dir.crossProduct(up);

	//m_pNode->setDirection(dir,Ogre::Node::TS_WORLD);

	//Ogre::Quaternion qu(right,up,dir);
	//m_pNode->setOrientation(qu);

	m_pNode->lookAt(camPos,Ogre::Node::TS_WORLD,Ogre::Vector3::UNIT_Z);

	return ;




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

	return ;

}


//----------------------------------------------------------
void  UISelectFaceMode::setVisible(bool b)
{

	UIBase::setVisible(b);

	if(b)
	{
		destroyAllFaceMode();
		initAllFaceMode();


	}

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

	return ;

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

void UISelectFaceMode::initAllFaceMode()
{

	/**创建三个模型用来做为不同脸型的选择*/

	///创建所有选择的脸
	unsigned int FaceSize= m_FaceModeSource.getFaceModeCount();
	const Ogre::String& headMode=g_userInformation.getHeadMode();

	Ogre::Vector3 pos(-2.0f,0.0f,0.0f);
	for(unsigned int i=0;i<FaceSize;++i)
	{

		const Ogre::String& faceMesh=m_FaceModeSource.getFaceMode(i);
		UserSelectMode* pMode=new UserSelectMode(faceMesh,headMode);
		m_FaceModeCollect.push_back(pMode);
		pMode->setPosition(pos.x,pos.y,pos.z);
		pos.x+=2.0f;

	}

}

//---------------------------------------------------------------------
void UISelectFaceMode::update(float time)
{

	FaceModeCollect::iterator it=m_FaceModeCollect.begin();
	FaceModeCollect::iterator itend=m_FaceModeCollect.end();

	for(;it!=itend;++it)
	{
		(*it)->update(time);
	}

}