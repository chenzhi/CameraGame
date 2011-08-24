

/***********************************************
¶¯×÷Àà
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



