
#pragma once



/************************************
游戏模式基类
*************************************/

class GameState;


class  GameMode
{
public:

	GameMode(GameState* pGameState)
	:m_end(false),m_pGameState(pGameState){}

	virtual ~GameMode(){}

	
	/**开始游戏*/
	virtual void start()=0;

	/**游戏结束*/
    virtual	void end()=0;

	/**每帧更新*/
	virtual void update(float time)=0;


	/**点击按下事件*/
	virtual  void beginTouch(int x,int y)=0;

	/**点击离开事件*/
	virtual void  endTouch(int x,int y)=0;

	/**点击移动事件*/
	virtual void  moveTouch(int x,int y){}


	/**判断游戏是否结束*/
	bool    isEnd()const{return m_end;}



protected:

	


	GameState*       m_pGameState;

	bool             m_end;////true为游戏结束



};







/***************************************************
游戏模式2
****************************************************/
class GameModeTwo :public GameMode
{


public:

	GameModeTwo(GameState* pGameState);


	virtual ~GameModeTwo();


	/**开始游戏*/
	virtual void start();

	/**游戏结束*/
	virtual	void end();

	/**每帧更新*/
	virtual void update(float time);


	/**点击按下事件*/
	virtual  void beginTouch(int x,int y);

	/**点击离开事件*/
	virtual void  endTouch(int x,int y);

	/**点击移动事件*/
	virtual void  moveTouch(int x,int y);


protected:

	///初始化ui游戏开始
	void initUI();

	///销毁ui
	void destroyUI();





};