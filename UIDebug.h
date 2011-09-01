/***************************
显示帧数和调试信息窗口
**************************/
#include "UIBase.h"

class ParamsPanel;
class Label;

class UIDebug :public UIBase
{
public:

	UIDebug();

	~UIDebug();


	virtual void  init();

	virtual void update(float time);



protected:

	ParamsPanel*  m_pParamsPanel;                  //总面数。
	Label*        m_pFpsLabel;                     // FPS label



};