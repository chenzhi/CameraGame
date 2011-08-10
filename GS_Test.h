/***********************************
测试状态
****************************************/


#ifndef  GS_Test_h_h
#define  GS_Test_h_h


#include "GameState.h"
#include "enemy.h"
#include "WarManager.h"



class GSTest :public GameState
{
public:

	GSTest();

	~GSTest();


		 
    /**
     *状态开始函数,
     */
	virtual void  begin( );
    
	/**
     *状态结束函数
     */
	virtual void  end( );
    
    
	/**更新函数*/
	virtual StateType update(float time);




protected:

	
	EnemyCollect m_EnemyCollect;




};



#endif