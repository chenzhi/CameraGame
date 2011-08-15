#include "pch.h"
#include "GS_Test.h"
#include  "application.h"





//---------------------------------------------------------
GSTest::GSTest()
:GameState(ST_TEST)
{


}

//---------------------------------------------------------
GSTest::~GSTest()
{


}


//---------------------------------------------------------
void GSTest::begin( )
{
	Ogre::SceneManager* pMrg=Application::getSingleton().getMainSceneManager();
	Ogre::SceneNode* pNode=pMrg->getRootSceneNode();
		 for(int i=-2;i<3;++i)
		 {

			 	// for(int j=-5;j<5;++j)
				 {
					 Ogre::Vector3 pos(i,0,1);


					 //Ogre::Vector3 temPos(i,j,0);
					 Enemy* pEnemy=new Enemy("face_test_4.mesh","head_test_4.mesh",pos,pNode);
					 pEnemy->playAnimation("aw",true,0);
					 m_EnemyCollect.push_back(pEnemy);

				 }

		 }

	




}

//---------------------------------------------------------
void  GSTest::end( )
{

	

}

//---------------------------------------------------------
StateType GSTest::update(float time)
{

    //*/
	size_t size=m_EnemyCollect.size();
	for(size_t i=0;i<size;++i)
	{
		m_EnemyCollect[i]->update(time);
	}
    //*/
	return GameState::update(time);

}