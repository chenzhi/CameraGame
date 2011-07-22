/**************************************************
选择用户用用脸型界面。这个界面实际是3d场景,选择胖瘦脸的模型
**************************************************/



#include "UIBase.h"



///用户选择脸和头套类
class UserSelectMode
{
public:

	/**构造函数 
	*@param faceMesh 脸的mesh文件名
	*@param 头套的文件名
	*/
	UserSelectMode(const Ogre::String& faceMesh,const Ogre::String&headMesh);

	~UserSelectMode();

	///每帧更新
	void update(float time);

	/**设置脸部模型*/
	void setFaceMesh(const Ogre::String& faceMesh);

	/**设置头套模型*/
	void setHeadMesh(const Ogre::String& headMesh);


	///是否与射线相交，用来做拾取
	bool isIntersect(const  Ogre::Ray& ray); 


	/**重置*/
	void reset();


	///移动到指定位置
	void translate(const Ogre::Vector3& pos);


	/**设置是否可见*/
	void setVisible(bool b);


	/**设置位置*/
	void setPosition(float x,float y,float z);

protected:

	
	/**更新位置
	*@param precent 0--1.0之间
	*/
	void updatePos(float precent);


	Ogre::Vector3  m_orginPos;///原始位置

	Ogre::Vector3  m_targetPos;//目标位置

	float          m_currentTime;///移动时间
	bool           m_isRoll;     ///是否移动

	Ogre::SceneNode* m_pNode;    
	Ogre::Entity*    m_pFaceEntity;
	Ogre::Entity*    m_pHeadEntity;



};






class UISelectFaceMode :public UIBase
{


public:


	
	UISelectFaceMode();


	~UISelectFaceMode();




protected:

	void init();


	/**设置是否可见*/
	virtual void  setVisible(bool b);


	///设置用户选择模型 是否可以 
	void setUserSelctModeVisible(bool b);


	/**手指离开*/
	virtual void onEndTouch(int x,int y);


protected:

	///销毁所有脸部模型
	void destroyAllFaceMode();


	typedef std::vector<UserSelectMode*>FaceModeCollect;
	FaceModeCollect          m_FaceModeCollect;


	





};