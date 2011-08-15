#include "pch.h"
#include "WarMode.h"
#include "Widget.h"
#include "UIWarTwo.h"
#include "Application.h"
#include "enemy.h"
#include "Config.h"
#include "WarManager.h"
#include "UIWarTwoBalance.h"


//--------------------------------------------------------
WarModeTwo::WarModeTwo(GameState* pGameState)
:WarMode(pGameState),m_pSceneMrg(NULL),m_KillCount(0),m_LostCount(0),
m_pUIBalance(NULL)
{
	m_pSceneMrg=Application::getSingleton().getMainSceneManager();


}


//--------------------------------------------------------
WarModeTwo::~WarModeTwo()
{
}


//--------------------------------------------------------
void WarModeTwo::start()
{
	


	initUI();

	
	
	///重置杀死人数
	m_KillCount=0;
	m_LostCount=0;

	///初始化所有的阵列
	initEmemyFormat();

	WarManager::getSingleton().addListener(this);
	WarManager::getSingleton().startWar();

	createEnemyQueue();
	


}

//--------------------------------------------------------
void WarModeTwo::end()
{

	destroyUI();
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

	/*/
	if(m_LostCount>=3)
	{
		///结束比赛
		WarManager::getSingleton().endWar();
		///显示结算界面
		m_pUIBalance->setVisible(true);
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

	WarManager::getSingleton().createEnemyQueue(90,60,m_EnemyFormatCollect[createindex].m_EnemyCollect,
		m_EnemyFormatCollect[createindex].m_FriendCollect);


	m_needCreate=false;
	return ;

}


//-----------------------------------------------------------------------
void WarModeTwo::initEmemyFormat()
{


	m_EnemyFormatCollect.clear();


	Ogre::ConfigFile cf;

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE

	OgreBites::FileSystemLayerImpl* pFileSystem=Application::getSingleton().getFileSystem();
	cf.load(pFileSystem->getConfigFilePath(g_EnemyFormat));

#else 
	cf.load(g_EnemyFormat);

#endif


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

		EnemyFormat enemyFormat;
		m_EnemyFormatCollect.push_back(enemyFormat);

		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;
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





	return ;

}