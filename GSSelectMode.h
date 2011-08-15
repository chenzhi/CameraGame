
#pragma once


#include "GameState.h"



class GSSelectMode :public GameState
{
public:

	GSSelectMode();

	~GSSelectMode();



		 
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


     ///创建ui
	void initUI();

	///销毁ui
	void DestroyUI();


protected:

	UIBase* m_pUI;


};