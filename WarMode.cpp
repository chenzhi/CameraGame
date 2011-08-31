#include "pch.h"
#include "WarMode.h"
#include "Widget.h"
#include "UIWarTwo.h"
#include "Application.h"
#include "enemy.h"
#include "Config.h"
#include "WarManager.h"
#include "UIWarTwoBalance.h"
#include "ogreapp/inputListen.h"
#include "EnemyQueue.h"

//--------------------------------------------------------
WarModeTwo::WarModeTwo(GameState* pGameState)
:WarMode(pGameState),m_pSceneMrg(NULL),m_KillCount(0),m_LostCount(0),
m_pUIBalance(NULL),m_Minx(-90.0f),m_Maxx(90.0f),
m_Miny(-60.0f),m_Maxy(60.0f),m_Minz(1.5f),m_Maxz(5.0f),m_EnemyLeftTime(3.0f),
m_Score(0),m_ContinualKill(0)
{
	m_pSceneMrg=Application::getSingleton().getMainSceneManager();

	initUI();

}


//--------------------------------------------------------
WarModeTwo::~WarModeTwo()
{
	destroyUI();
}


//--------------------------------------------------------
void WarModeTwo::start()
{

	///重置杀死人数
	m_KillCount=0;
	m_LostCount=0;
	m_ContinualKill=0;
	m_Score=0;
	m_pFireBulletCollect.clear();


	///初始化所有的阵列
	initEmemyFormat();

	WarManager::getSingleton().addListener(this);
	WarManager::getSingleton().startWar();

	createEnemyQueue();
    
    m_pUIBalance->setVisible(false);
	m_pUI->setVisible(true);
	m_pUI->reset();


	m_pUIBalance->setVisible(false);
	m_pUI->setVisible(true);
	m_pUI->reset();


	///得置摄像机位置
	Application::getSingleton().getMainCamera()->getParentSceneNode()->resetOrientation();


}

//--------------------------------------------------------
void WarModeTwo::end()
{

	
	WarManager::getSingleton().removeListener(this);
	//WarManager::getSingleton().destroyAllEnemyQueue();

}

//--------------------------------------------------------
void WarModeTwo::update(float time)
{

	if(m_needCreate)
	{
		_createEnemyQueue();
	}

}


//--------------------------------------------------------
void WarModeTwo::beginTouch(int x,int y)
{




}

//--------------------------------------------------------
void  WarModeTwo::endTouch(int x,int y)
{

}

///--------------------------------------------------------
void  WarModeTwo::moveTouch(int x,int y)
{

}

//---------------------------------------------------------
void WarModeTwo::initUI()
{

	m_pUI=new UIWarModeTwo();
	m_pUI->init();
	Application::getSingleton().registerUI(m_pUI);

	m_pUIBalance=new UIWarTowModeBalance(this);
	m_pUIBalance->init();
	m_pUIBalance->setVisible(false);
	Application::getSingleton().registerUI(m_pUIBalance);


	m_pUIBalance->setVisible(false);
	m_pUI->setVisible(true);
	m_pUI->reset();


}


//---------------------------------------------------------
void WarModeTwo::destroyUI()
{

	Application::getSingleton().destroyUI(m_pUI);
	m_pUI=NULL;
	Application::getSingleton().destroyUI(m_pUIBalance);
	m_pUIBalance=NULL;

}

//----------------------------------------------------------------
void  WarModeTwo::onKillEnemyQueue(EnemyQueue* pEnemyQueue)
{
	m_pUI->onKillEnemyQueue(pEnemyQueue);
	++m_KillCount;

	///继续创建新的队列

	createEnemyQueue();



}

//----------------------------------------------------------------
void  WarModeTwo::onLostEnemyQueue(EnemyQueue* pEnemyQueue)
{
	m_pUI->onLostEnemyQueue(pEnemyQueue);
	++m_LostCount;
	///如果大于三个逃跑游戏结束。

	//*/
	if(m_LostCount>=3)
	{
	///结束比赛
	WarManager::getSingleton().endWar();
	///显示结算界面
	m_pUIBalance->setVisible(true);
	m_pUIBalance->setVisible(m_Score);
	m_pUI->setVisible(false);
	

	}///继续创建新的队列
	else  //*/
	{

		createEnemyQueue();

	}


}

//----------------------------------------------------------------
void WarModeTwo::onCrateEnemyQueue(EnemyQueue* pEnemyQueue)
{

	m_pUI->onCrateEnemyQueue(pEnemyQueue);
}

//----------------------------------------------------------------
void  WarModeTwo::onHitFriend(Enemy* pEnemy)
{
	return ;

}

void WarModeTwo::onHitEnemy(Enemy* pEnemy,bool hitMouth,Bullet* pBullet)
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

void WarModeTwo::onfire(Bullet* pBullet)
{

 m_pFireBulletCollect.push_back(pBullet);
 return; 

}



//-----------------------------------------------------------------------
void   WarModeTwo::_createEnemyQueue()
{

	///逃跑数和打死数之合就是创建的队数总数
	unsigned int createindex=m_LostCount+m_KillCount;

	///如果小于队列数就按队列出
	if(createindex>=m_EnemyFormatCollect.size())
	{
		::srand( time(0) );    //设定随机数种子
		createindex=::rand()%m_EnemyFormatCollect.size();
	}

	EnemyQueue* pQueue= WarManager::getSingleton().createEnemyQueue(m_Minx,m_Maxx,m_Miny,m_Maxy,m_Minz,m_Maxz,m_EnemyFormatCollect[createindex].m_EnemyCollect,
		m_EnemyFormatCollect[createindex].m_FriendCollect);
	pQueue->setLeftTime(m_EnemyLeftTime);


	m_needCreate=false;
	return ;

}

//-----------------------------------------------------------------------
void WarModeTwo::updateAccelerometer()
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


//-----------------------------------------------------------------------
void WarModeTwo::initEmemyFormat()
{

	Ogre::DataStreamPtr pDataStream=Ogre::ResourceGroupManager::getSingleton().openResource("EnemyFormatMode2.cfg","General");


	if(pDataStream.isNull())
	{
		OGRE_EXCEPT(0,"can't find warmode1 enemyFormat file","WarModeOne::initEmemyFormat()");
	}



	m_EnemyFormatCollect.clear();


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