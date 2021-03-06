

#pragma  once


#include "UIBase.h"
#include "UILLayout.h"




class ImageButton;
class TimeImageButton;
class UISelectUser :public UILayout
{

public:

	UISelectUser();

	~UISelectUser();



	virtual void init();


	/**设置有多少个用户数据*/
	void setUserList(Ogre::StringVectorPtr pUserList);


	///每帧更新
	 virtual void update(float time);
    
    /**设置是否可见*/
    void  setVisible(bool b);

protected:

	/**手指离开*/
	virtual void onEndTouch(int x,int y);

	///重新载入用用列表
	void updateUserList();


	/**删除现有的所有的用户图*/
	void destroyAllUserList();


	///按钮回调事件
	virtual void buttonHit(Widget* button);

	/**重置所有的照片按钮状态*/
	void   resetUserFaceButton();
    
    




	///用户列表
	Ogre::StringVectorPtr m_UserList;


	typedef std::vector<TimeImageButton*> ImageButtonCollect;
	ImageButtonCollect  m_UserButtonCollect;



	std::vector<Widget*>              m_FaceMaskCollect;///脸的遮罩层




	///返回到捕人脸按钮
	ImageButton* m_ToCaptureButton;
	ImageButton* m_pReturnButton;

	bool         m_NeedUpdate;///是否刷新



};