/**************************************************
选择用户用用脸型界面。这个界面实际是3d场景,选择胖瘦脸的模型
**************************************************/



#include "UIBase.h"



class SelectFaceMode :public UIBase
{
public:


	
	SelectFaceMode();


	~SelectFaceMode();




protected:

	void init();


	/**设置是否可见*/
	virtual void  setVisible(bool b);


	/**判断是否可见,如果不同见不响应手指事件*/
	virtual bool   isVisible()const ;






};