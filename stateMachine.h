/**********************
 状态机类
 ************************/


#ifndef stateMachine_h_h_h
#define stateMachine_h_h_h

#include "State.h"
#include <vector>



class StateMachine
{
public:
    
	/**构造函数*/
	StateMachine();
    
	/**析构函数 */
	virtual ~StateMachine();
    
    
	/**初始化函数，一般在这个函数里注册所有的状态
     *在这个函数里需要手动指定当前活动状态。同时调用活动状态的begin函数
     */
	virtual void  initState()=0;
    
    
	/**每帧更新函数
     *@param time 上一帧到当前帧的时间
     */
	virtual void  update(float time);
    
    
	/**消除所有状态
     *@remark 会删除所有状态的内存 
     */
	void destroyAllState();
    
    
	/**查找指定类型状态
     *@return 如果没找到返回空
     */
	State* findState(StateType type);
    
    
	/**注册一个新的状态
     *@return 如果已经注册了返回false
     */
	bool  registerState(State* pState);
    
    
	/**注销一个状态
     *@return  成功返回真。失败返回假
     *@remark 不会清空状态内存。注销的状态需要用户手工删除
     */
	bool unregisterState(StateType type);
    
    
	/**获取状态的数量*/
	size_t getStateCount()const {return m_stateCollect.size();}
    
    
	/**获取指定索引的状态指针 
     *无返回空
     */
	State* getState(unsigned int index) const ;
    
    
	/**返回当前活动状态*/
	State* getCurrentActive()const {return m_pcurrentState;}
    
	///设置游戏开始的状态
	void setBeginState(StateType GS);
    
    
protected:
    
	typedef std::vector<State*>  StateCollect;
    
	
	/**所有类型状态机容器*/
	StateCollect m_stateCollect;
    
    
	/**保存当前的状态类型*/
	State* m_pcurrentState;
    
};


#endif