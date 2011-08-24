#pragma  once



#include "Active.h"

class Active;


class ActiveContainer
{

public:

	ActiveContainer()
		:m_pCurrentActive(NULL)
	{}


	virtual ~ActiveContainer()
	{
		if(m_pCurrentActive!=NULL)
		{
			m_pCurrentActive->end();
			SafeDelete(m_pCurrentActive);
		}
	}

	/**Ö´ÐÐ¶¯×÷*/
	void runActive(Active* pActive)
	{
		if(m_pCurrentActive!=NULL)
		{
			m_pCurrentActive->end();
			SafeDelete(m_pCurrentActive);
			m_pCurrentActive->begin();

		}
	}

	void update(float time)
	{
		if(m_pCurrentActive!=NULL)
		{
			if(m_pCurrentActive->update(time)==false)
			{
				m_pCurrentActive->end();
				SafeDelete(m_pCurrentActive);
			};

		}
	}



protected:

	Active* m_pCurrentActive;


};