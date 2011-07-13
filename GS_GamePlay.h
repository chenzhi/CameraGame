
/****************************************************
开始游戏状态。play界面


********************************************************/






#pragma  once


#include "GameState.h"
#include "UIManager.h"


class GSGamePlay :public GameState
{

public:

	GSGamePlay();


	~GSGamePlay();


	 
    /*
     *状态开始函数,
     */
	virtual void  begin( );
    
	/*
     *状态结束函数
     */
	virtual void  end( );
    
    
	/**更新函数*/
	virtual StateType update(float time);




protected:


	/**初始化相关ui*/
	void initUI();

	/**销毁相关ui*/
	void destroyUI();


protected:


	UICollect m_UICollect;



};



