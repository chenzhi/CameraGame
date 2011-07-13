
#include "pch.h"
#include "inputListen.h"
#include "Application.h"


template<> InputListen* Ogre::Singleton<InputListen>::ms_Singleton=NULL;

//---------------------------------------------------------
InputListen::InputListen(HWND wnd)
:m_wnd(wnd)
{

	setupInput();

}


//---------------------------------------------------------
InputListen::~InputListen()
{

	destroyInputDevices();

}


//---------------------------------------------------------
void  InputListen::setupInput()
{


	OIS::ParamList pl;
	size_t windowHnd = (size_t)m_wnd;
	std::ostringstream windowHndStr;
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	pl.insert(std::make_pair(std::string("w32_mouse"),		std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_mouse"),		std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"),	std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"),	std::string("DISCL_NONEXCLUSIVE")));

	mInputManager = OIS::InputManager::createInputSystem(pl);
	try
	{
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));

		RECT rect;
		::GetClientRect(m_wnd,&rect);
		const OIS::MouseState& mouseState = mMouse->getMouseState();
		mouseState.width = rect.right-rect.left;
		mouseState.height =rect.bottom-rect.top;
		// mKeyboard->isKeyDown()

	}
	catch (OIS::Exception e)
	{
		mInputManager->destroyInputObject(mMouse);
		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);
		OGRE_EXCEPT(0,"init OIS Failed","InputSystem::InputSystem")

	}

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);


}


//---------------------------------------------------------
void InputListen::TouchBegan(int x, int y)
{

	 Application::getSingleton().TouchBegan(x,y);

}


//---------------------------------------------------------
void InputListen::TouchEnd(int x, int y)
{
	Application::getSingleton().TouchEnd(x,y);

}

//---------------------------------------------------------
void InputListen::TouchMove(int x, int y)
{

 Application::getSingleton().TouchMove(x,y);
}



//---------------------------------------------------------
void InputListen::Captuer()
{

	if (m_wnd!=NULL&&IsIconic(m_wnd)==false)
	{
		// 捕获鼠标和键盘消息
		mKeyboard->capture();
		mMouse->capture();
	}
	return ;


}





void  InputListen::createInputDevices()
{

}


/**销毁所有的输入设备*/
void  InputListen::destroyInputDevices()
{

	if (mInputManager)
	{
		mInputManager->destroyInputObject(mMouse);
		mInputManager->destroyInputObject(mKeyboard);
		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = 0;
	}

}


/**OIS回调函数*/
bool  InputListen::mouseMoved(const OIS::MouseEvent &arg)
{

	return true;
}

bool  InputListen::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{

	    TouchBegan(arg.state.X.abs,arg.state.Y.abs);
		return true;
}

bool  InputListen::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{

		return true;
}

bool  InputListen::keyPressed(const OIS::KeyEvent &arg)
{

		return true;
}

bool  InputListen::keyReleased(const OIS::KeyEvent &arg)
{

		return true;
}