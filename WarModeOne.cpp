
#include "pch.h"
#include "WarModeOne.h"
#include "Application.h"
#include "UIWarone.h"
#include "EnemyQueue.h"
#include "UIWarTwoBalance.h"



//----------------------------------------------------------------------------
WarModeOne::WarModeOne(GameState* pGameState)
:WarMode(pGameState),m_pWarManager(NULL),m_pSceneMrg(NULL),m_GameLeft(60.0f),
m_CurrentTime(0.0f),m_needCreate(false),m_pUI(NULL),m_Minx(-90.0f),m_Maxx(90.0f),
m_Miny(-60.0f),m_Maxy(60.0f),m_Minz(1.5f),m_Maxz(5.0f),m_KillCount(0),m_LostCount(0),
m_EnemyLeftTime(3.0f),m_pUIBalance(NULL),m_Score(0),m_ContinualKill(0),m_CreateIndex(0)
{

   initUI();
	
}


//----------------------------------------------------------------------------
WarModeOne::~WarModeOne()
{

	destroyUI();

}


//----------------------------------------------------------------------------
void WarModeOne::start()
{

	m_pWarManager=WarManager::getSingletonPtr();

	m_pWarManager->startWar();
	m_pWarManager->addListener(this);

	m_pSceneMrg=Application::getSingleton().getMainSceneManager();

	//重置摄像机
	Application::getSingleton().getMainCamera()->getParentSceneNode()->resetOrientation();

    initEnemyFormat();
	m_CurrentTime=0.0f;
	m_needCreate=true;

	m_KillCount=0;
	m_LostCount=0;
    m_CreateIndex=0;
	m_Score=0;
	m_pFireBulletCollect.clear();


	m_pUI->setVisible(true);
	m_pUIBalance->setVisible(false);
    m_pUI->reset();
	m_ContinualKill=0;

}


//----------------------------------------------------------------------------
void WarModeOne::end()
{
	m_pWarManager->removeListener(this);

}

//----------------------------------------------------------------------------
void WarModeOne::update(float time)
{

	
	m_CurrentTime+=time;
	if(m_CurrentTime>m_GameLeft)
	{
		///结束比赛
		if(WarManager::getSingleton().isGameEnd()==false)
		{
			WarManager::getSingleton().endWar();
			m_pUI->setVisible(false);
			m_pUIBalance->setVisible(true);
			m_pUIBalance->setScore(m_Score);
		}
		

		return ;
	}


	if(m_pUI!=NULL)
	{
		m_pUI->setTime(m_GameLeft-m_CurrentTime);
	}


	if(m_needCreate)
	{
		_createEnemyQueue();
	}



	return ;

}

//----------------------------------------------------------------------------
void WarModeOne::updateAccelerometer()
{

	Ogre::SceneNode* pCameraNode=Application::getSingleton().getMainCameraNode();

	Ogre::Vector3 gyrco=InputListen::getSingleton().getGyroscopeData();
	float yawtem=gyrco.y;
	float pitch=gyrco.z;

	pitch+=Ogre::Math::PI*0.5f;

	if(pCameraNode!=NULL )
	{
		pCameraNode->resetOrientation();
		pCameraNode->pitch(Ogre::Radian(-pitch));
		pCameraNode->yaw(Ogre::Radian(yawtem),Ogre::Node::TS_WORLD);

	}

	return ;
}



//----------------------------------------------------------------------------
void  WarModeOne::initUI()
{

	m_pUI=new UIWarone();
    m_pUI->init();
	Application::getSingleton().registerUI(m_pUI);

	m_pUIBalance=new UIWarTowModeBalance(this);
	m_pUIBalance->init();
	m_pUIBalance->setVisible(false);
	Application::getSingleton().registerUI(m_pUIBalance);

}

//----------------------------------------------------------------------------
void  WarModeOne::destroyUI()
{
	Application::getSingleton().destroyUI(m_pUI);
	m_pUI=NULL;

	Application::getSingleton().destroyUI(m_pUIBalance);
	m_pUIBalance=NULL;


}


//----------------------------------------------------------------------------
void  WarModeOne::initEnemyFormat()
{


	m_EnemyFormatCollect.clear();

	Ogre::DataStreamPtr pDataStream=Ogre::ResourceGroupManager::getSingleton().openResource("EnemyFormatMode1.cfg","General");
	
	
	if(pDataStream.isNull())
	{
		OGRE_EXCEPT(0,"can't find warmode1 enemyFormat file","WarModeOne::initEmemyFormat()");
	}


	Ogre::ConfigFile cf;

	cf.load(pDataStream);




	///循环取出所有的队列和位置信息
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String sec, type, arch;

	//获取所有阵型
	while (seci.hasMoreElements())
	{
		sec = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		if(settings->empty())
			continue;



		if(sec.find("Format")!=Ogre::String::npos)
		{

		EnemyFormat enemyFormat;
		m_EnemyFormatCollect.push_back(enemyFormat);
		}

		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;

			///如果是设置范围大小的
			if(sec=="Enemylimits")
			{
				if(type=="Minx")
				{
					m_Minx=Ogre::StringConverter::parseReal(arch);
				}else if(type=="Maxx")
				{
					m_Maxx=Ogre::StringConverter::parseReal(arch);
				}else if(type=="Miny")
				{
					m_Miny=Ogre::StringConverter::parseReal(arch);
				}else if(type=="Maxy")
				{
					m_Maxy=Ogre::StringConverter::parseReal(arch);
				}else if(type=="Minz")
				{
					m_Minz=Ogre::StringConverter::parseReal(arch);
				}else if(type=="Maxz")
				{
					m_Maxz=Ogre::StringConverter::parseReal(arch);
				}else if(type=="LeftTime")
				{
					m_EnemyLeftTime=Ogre::StringConverter::parseReal(arch);
				}else if(type=="gametime")
				{
					m_GameLeft=Ogre::StringConverter::parseReal(arch);
				}



			}else
			{

			
				Ogre::Vector3 Pos=Ogre::StringConverter::parseVector3(arch);
				if(type=="Enemy")
				{	
					m_EnemyFormatCollect.back().m_EnemyCollect.push_back(Pos);
				}else if(type=="Friend")
				{
					m_EnemyFormatCollect.back().m_FriendCollect.push_back(Pos);
				}
			}

		}


	}





	return ;

}


/**创建一个队列*/
//----------------------------------------------------------------------------
void  WarModeOne::_createEnemyQueue()
{

	///逃跑数和打死数之合就是创建的队数总数
	unsigned int createindex=m_CreateIndex;

	///如果小于队列数就按队列出
	if(createindex>=m_EnemyFormatCollect.size())
	{
		::srand( time(0) );    //设定随机数种子
		createindex=::rand()%m_EnemyFormatCollect.size();
	}

	EnemyQueue* pQueue= WarManager::getSingleton().createEnemyQueue(m_Minx,m_Maxx,m_Miny,m_Maxy,m_Minz,m_Maxz,m_EnemyFormatCollect[createindex].m_EnemyCollect,
		m_EnemyFormatCollect[createindex].m_FriendCollect);
	pQueue->setLeftTime(m_EnemyLeftTime);

	


	//Active* pActive=new MoveToActive(pQueue->getSceneNode(),Ogre::Vector3(0.0f,0.0f,-10.0f),1.5f);
	//pQueue->runActive(pActive);

	++m_CreateIndex;
	m_needCreate=false;
	return ;

}

//----------------------------------------------------------------------------
void WarModeOne::onKillEnemyQueue(EnemyQueue* pEnemyQueue)
{
	m_needCreate=true;
	++m_KillCount;
  
	m_pUI->onKillEnemyQueue(pEnemyQueue);
   
}

//----------------------------------------------------------------------------
void WarModeOne::onLostEnemyQueue(EnemyQueue* pEnemyQueue)
{
   ++m_LostCount;
	m_needCreate=true;
    m_ContinualKill=0;
	m_pUI->onLostEnemyQueue(pEnemyQueue);
}



//----------------------------------------------------------------------------
void WarModeOne::onCrateEnemyQueue(EnemyQueue* pEnemyQueue)
{
	m_pUI->onCrateEnemyQueue(pEnemyQueue);
}



//----------------------------------------------------------------------------
void WarModeOne::beginTouch(int x,int y)
{

	WarManager::getSingleton().fire();
}


//---------------------------------------------------
void  WarModeOne::onHitEnemy(Enemy* pEnemy,bool hitMouth,Bullet* pBullet)
{
	if(m_pFireBulletCollect.empty()==false&&pBullet==m_pFireBulletCollect[0]&&m_pFireBulletCollect.size()<10)
	{
		++m_ContinualKill;
		m_pFireBulletCollect.erase(m_pFireBulletCollect.begin());
	}else
	{
		m_ContinualKill=1;
		m_pFireBulletCollect.clear();
	}

	int Score=50;
	if(hitMouth==true)
	{
		Score=100;
	}
		m_Score+=Score*m_ContinualKill;
	 m_pUI->setScore(m_Score);

}

//---------------------------------------------------------
void WarModeOne::onfire(Bullet* pBullet)
{
	m_pFireBulletCollect.push_back(pBullet);

	return ;
}