
/***************************************************
战斗模式2的ui界面
*******************************************************/



#pragma  once


#include "UIBase.h"



class RotateImage;

class UIWarModeTwo :public UIBase
{

public:


	UIWarModeTwo();


	~UIWarModeTwo();


	 void init();





	 ///设置敌人所有的方向
	 void setEmemeyDir(float Radian);

protected:



      RotateImage* m_pRotateImage;//指向敌人的方向


};