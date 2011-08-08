
/**********************
 状态机的状态基类
 ***********************/

#pragma once


/**状态机类型*/
enum StateType
{
    ST_NONE,

	ST_GAMEPLAY=1,    //开始游戏
	ST_SELECTMODE,    ///选择模式
    ST_CAPTUREFACE,//捕获脸部
    
    ST_WAR,///战斗状态
    
};




class State
{
    
    
protected:
    
	///自身的状态
	StateType m_type;
    
	///下一帧的游戏状态
	StateType m_NextType;
    
	///是否暂停一个状态
	bool m_stopState;
    
    
    
public:
    
	State( StateType type)
    :m_type(type),m_NextType(type),m_stopState(false)
	{
      
	}
    
	virtual ~State(){}
    
	
	/**每帧更新函数
     *@param time 上一帧到当前帧的时间
     *@return 返回下帧的自动驾驶状态，如果与当前状态不一样表示需要更换状态 
     */
	virtual StateType update(float time)
    {
        return m_NextType;
    }
    
	/**开始状态初始化*/
	virtual void begin()
    {
        m_NextType = getType();
    }
    
	/**状态结束清除初始化的内容*/
	virtual void  end(){}
    
	/**返回当前状态的类型*/
	StateType getType()const
    { 
        return m_type;
    }
    
	///设置下一帐状态
	void setNextStateType(StateType stype)
    {
        m_NextType=stype;
    }
    
	///暂停游戏状态
	void stopGameState()
	{
		m_stopState=!m_stopState;
	}
    

    
	
    
};


