

/***********************************************
动作类
****************************************************/

#pragma  once 

class Active
{

public:

	Active(){}

	virtual ~Active(){}

	virtual void  begin(){}

	virtual bool   update(float time){ return true;}

	virtual void  end(){}

protected:


};
typedef  std::vector<Active*> ActitveVector;




/**动作队列，把多个动作连成一个大动作，队列里所有的动作依次
运行，直到所有动作都完成了，整个动作动队列结束*/

class ActiveQueue :public Active
{
public:

	ActiveQueue();

    virtual 	~ActiveQueue();


protected:



	ActitveVector m_ActiveVector;


};











///旋转动作
class RotateActive :public Active
{
public:

	RotateActive();

	~RotateActive();



protected:



};