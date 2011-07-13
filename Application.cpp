//
//  Application.cpp
//  ogreApp
//
//  Created by iMac on 11-6-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include "pch.h"
#include "Application.h"
#include  "CaptureFaceGS.h"
#include "GameState.h"
#include  "WarGS.h"
#include  "SdkTrays.h"










namespace Ogre
{
  template<> Application* Ogre::Singleton<Application>::ms_Singleton=0;  
}


Application::Application()
:m_pRoot(NULL ),m_pRenderWindow(NULL),m_pViewPort(NULL),m_pCamera(NULL),
m_pSceneManager(NULL)
{

   
}

//----------------------------------------------
Application::~Application()
{
    
    destory();

}




void  Application::initState()
{
    State* pState=new WarGS();
    registerState(pState);
    
    pState= new CaptureFaceGS();
    registerState(pState);
    
    
    
    setBeginState(ST_CAPTUREFACE);
    return;
}




//----------------------------------------------
void Application::init()
{
     initOgreRender();

	 initInputDevice();
    
     initState();
}

bool initOgrePlugs()
{
    return true;

}

//----------------------------------------------
bool Application::initOgreRender()
{



  
   

	///iphone是静态库连接。win32下动态库连接
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE

	m_pRoot=OGRE_NEW Ogre::Root(/*"plugins.cfg","ogre.cfg"*/);
    Ogre::Plugin* pPlugin = OGRE_NEW Ogre::GLESPlugin();
    m_pRoot->installPlugin(pPlugin);
    
   // pPlugin = OGRE_NEW Ogre::ParticleFXPlugin();
    //m_pRoot->installPlugin(pPlugin);

    
   if (!m_pRoot->restoreConfig())
   {
       m_pRoot->showConfigDialog();
   }

   m_pRenderWindow=m_pRoot->initialise(true,"CameraGame");


#else//if  OGRE_PLATFORM == OGRE_PLATFORM_WIN32

	  m_pRoot=OGRE_NEW Ogre::Root("","");

#ifdef  _DEBUG

	m_pRoot->loadPlugin("RenderSystem_Direct3D9_d");
	m_pRoot->loadPlugin("Plugin_ParticleFX_d");
	m_pRoot->loadPlugin("Plugin_OctreeSceneManager_d");
#else

	m_pRoot->loadPlugin("RenderSystem_Direct3D9");
	m_pRoot->loadPlugin("Plugin_ParticleFX");
	m_pRoot->loadPlugin("Plugin_OctreeSceneManager");

#endif

	// 设置渲染系统

	m_pRoot->setRenderSystem(m_pRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem"));
	m_pRenderWindow=m_pRoot->initialise(false);

	int width=960;
	int height=640;
	InitWindow(width,height);

	Ogre::NameValuePairList miscParams;

	miscParams["FSAA"]					="0";
    miscParams["VSync"]					= "No";
	miscParams["VSync Interval"]        ="1";
	miscParams["colourDepth"]			= "32";
	miscParams["externalWindowHandle"]	= Ogre::StringConverter::toString((size_t)mHwnd);

	m_pRenderWindow = m_pRoot->createRenderWindow("GameMainWindow", width, height,false, &miscParams);

#endif

   // mStaticPluginLoader.load();
 

    m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "DummyScene");
    m_pCamera = m_pSceneManager->createCamera("MainCamera");
    m_pCamera->setFarClipDistance(1000);
    m_pCamera->setNearClipDistance(1.0f);
    m_pRenderWindow->addViewport(m_pCamera);
    m_pViewPort=m_pRenderWindow->getViewport(0);
    
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();
    Ogre::Root::getSingleton().clearEventTimes();
    
    m_pCameraNode=m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    m_pCameraNode->attachObject(m_pCamera);
    m_pCameraNode->setPosition(0.0f,0.0f,5.0f);
    
    if(m_pViewPort!=NULL)
    {
      m_pViewPort->setBackgroundColour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));
    }
    
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    m_pFileSystem =new OgreBites::FileSystemLayerImpl(OGRE_VERSION_NAME);
#endif


    
    initResource();
    
    initScene();
    
    
    m_pUIManager =new SdkTrayManager("MainUI",m_pRenderWindow);
    m_pUIManager->showFrameStats(TL_BOTTOMLEFT);
    
    
#ifdef __arm__
    new ofxiPhoneVideoGrabber(480,320);
#endif

    return true;
}








//----------------------------------------------
void Application::initScene()
{

   m_pSceneManager->createEntity("Head", "CameraHead.mesh");
   // pEntity->setVisible(true);
    //m_pSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(pEntity);
    
   // Ogre::Light* pLight=m_pSceneManager->createLight("mainLight");
    
}

//----------------------------------------------
/**初始化输入设备*/
void Application::initInputDevice()
{   
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    m_pInputListen=new InputListen(mHwnd);
#else
    m_pInputListen=new InputListen();
#endif
}

//-------------------------------------------------
void Application::destroyInputDevice()
{
    
	SafeDelete(m_pInputListen);

   // [m_Accelerometer release];
}


//----------------------------------------------
void Application::destroyOgreRender()
{

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    delete m_pFileSystem;
#endif

    delete m_pUIManager;
   // mStaticPluginLoader.unload();
    OGRE_DELETE m_pRoot;
    
    
#ifdef __arm__
    delete ofxiPhoneVideoGrabber::getSingletonPtr();
#endif    
}

//----------------------------------------------
void Application::update(float time)
{
    
    StateMachine::update(time);
    
    //updateVideo();


    m_pInputListen->Captuer();

    m_pUIManager->frameRenderingQueued();
      
    m_pRoot->renderOneFrame(time);
    
    
    
#ifdef __arm__
    ofxiPhoneVideoGrabber::getSingleton().update();
#endif
    
}

//----------------------------------------------
void Application::destory()
{

	///必须先销毁所有的状态
	StateMachine::destroyAllState();
	
	destroyOgreRender();

	destroyInputDevice();

    return ;
}
//--------------------------------------------------------------------
void Application::initResource()
{
    
    // load resource paths from config file
    Ogre::ConfigFile cf;

#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
    Ogre::String tempath=Ogre::macBundlePath();
    cf.load(m_pFileSystem->getConfigFilePath("resources.cfg"));
#else 

	  cf.load("resources.cfg");

#endif
    
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String sec, type, arch;
    
    // go through all specified resource groups
    while (seci.hasMoreElements())
    {
        sec = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        
        // go through all resource paths
        for (i = settings->begin(); i != settings->end(); i++)
        {
            type = i->first;
            arch = i->second;
            
#if OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(arch, "/", false)) // only adjust relative dirs
                arch = Ogre::String(Ogre::macBundlePath() + "/" + arch);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
        }
    }

    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    
    return ;
}



//-------------------------------------------------------
void Application::TouchBegan(int x,int y)
{
    transformInputCoordinate(x,y);
    GameState* pState=static_cast<GameState*>(getCurrentActive());
    if(pState!=NULL)
    {
        pState->beginTouch(x,y);
    }





}


//-------------------------------------------------------
void Application::TouchEnd(int x,int y)
{
    transformInputCoordinate(x,y);
	GameState* pState=static_cast<GameState*>(getCurrentActive());
	if(pState!=NULL)
	{
		pState->endTouch(x,y);
	}
}

/**手指滑动*/
void Application::TouchMove(int x,int y)
{
    

    transformInputCoordinate(x,y);
    
	GameState* pState=static_cast<GameState*>(getCurrentActive());
	if(pState!=NULL)
	{
		pState->moveTouch(x,y);
	}
    
}


//-------------------------------------------------------
void Application::transformInputCoordinate(int&x, int &y)
{

#if OGRE_PLATFORM != OGRE_PLATFORM_IPHONE
	return ;
#endif



    int w = m_pRenderWindow->getViewport(0)->getActualWidth();
    int h = m_pRenderWindow->getViewport(0)->getActualHeight();
    

    
    ///暂时点击数据只取到320*480,所以需要＊2
    int absX =x*2;
    int absY =y*2;
    


    //int relX = state.X.rel;
   // int relY = state.Y.rel;
    
    switch (m_pRenderWindow->getViewport(0)->getOrientationMode())
    {
        case Ogre::OR_DEGREE_0:
            break;
        case Ogre::OR_DEGREE_90:
             x = w - absY;
             y = absX;
   
            break;
        case Ogre::OR_DEGREE_180:
            x = w - absX;
            y = h - absY;
            break;
        case Ogre::OR_DEGREE_270:
            x = absY;
            y = h - absX;
            break;
    }

    return ;
    
    
}




#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32




LRESULT Application::MsgProc(HWND hWnd, DWORD message, WPARAM wParam, LPARAM lParam)
{



	if (message == WM_CREATE)
	{	// Store pointer to Win32Window in user data area
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)(((LPCREATESTRUCT)lParam)->lpCreateParams));
		return 0;
	}

	switch (message)
	{
	case WM_ACTIVATE:
		{

		}
		break;
	}

	//unsigned char code_point = (CEGUI::utf32)wParam;
	//static char     s_tempChar[3]  = "";
	//static wchar_t  s_tempWchar[2] = L"";
	//static bool s_flag = false;
	//unsigned char  uch  = (unsigned char)code_point;

	Application* win = (Application*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (win &&	win->m_pRenderWindow)
	{
		switch (message)
		{
			/*			case WM_ACTIVATE:
			{
			bool active = (LOWORD(wParam) != WA_INACTIVE);
			if( active )
			{
			win->mWindow->setActive( true );
			}
			else
			{
			if( win->mWindow->isDeactivatedOnFocusChange() )
			{
			win->mWindow->setActive( false );
			}
			}
			break;
			}
			*/
		case WM_SYSKEYDOWN:
			switch( wParam )
			{
			case VK_CONTROL:
			case VK_SHIFT:
			case VK_MENU: //ALT
				//return zero to bypass defProc and signal we processed the message
				return 0;
			}
			break;

		case  WM_KEYDOWN:
			  if(wParam==VK_ESCAPE)
			  {
				  ::PostQuitMessage(0);
			  }
			  break;;

		case WM_SYSKEYUP:
			switch( wParam )
			{
			case VK_CONTROL:
			case VK_SHIFT:
			case VK_MENU: //ALT
			case VK_F10:
				//return zero to bypass defProc and signal we processed the message
				return 0;
			}
			break;

		case WM_SYSCHAR:
			// return zero to bypass defProc and signal we processed the message, unless it's an ALT-space
			if (wParam != VK_SPACE)
				return 0;
			break;

		case WM_ENTERSIZEMOVE:
			break;

		case WM_EXITSIZEMOVE:
			break;

		case WM_MOVE:
			//win->mWindow->windowMovedOrResized();
			break;

		case WM_DISPLAYCHANGE:
			//win->mWindow->windowMovedOrResized();
			//win->mFrameListener->windowResized();
			break;

		case WM_SIZE:
			//win->mWindow->windowMovedOrResized();
			//win->mFrameListener->windowResized();

			/**更新inputSystem**/
			//if(InputSystem::getSingletonPtr()!=NULL)
			//{
			//	InputSystem::getSingletonPtr()->setMouseArea(LOWORD(lParam),HIWORD(lParam) );
			//}



			break;

		case WM_GETMINMAXINFO:
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 800;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;
			break;

		case WM_CLOSE:
		//	win->mFrameListener->windowClosed();
			PostQuitMessage(0);
			//win->mWindow->destroy();
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_ERASEBKGND:
			return 1;

		case WM_PAINT:
			//PAINTSTRUCT ps;
			//BeginPaint(hWnd, &ps);
			//EndPaint(hWnd, &ps);
			break;

		case WM_SETCURSOR:
			// 仅在客户区显示自定义鼠标
			if (LOWORD(lParam) == HTCLIENT)
			{
				//CMouseCursorManager::getSingleton().refreshMouseCursor();
				return 1;
			}
			break;
		
		default:
			break;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}









///开始帧循环
void  Application::go()
{
	
	
	init();


	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(TRUE)
	{

		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			// 如果是退出消息,退出
			if(msg.message == WM_QUIT) 
				return;

			// 处理其他消息
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		try
		{
			static DWORD lasttime=::GetTickCount();

			DWORD CurrentTime=::GetTickCount();
            
			float time=(CurrentTime-lasttime)*0.001f;
			update(time);
			lasttime=CurrentTime;


		}
		catch (std::exception& e)
		{
			MessageBox(NULL,e.what(),"捕获异常",MB_OK);
			::PostQuitMessage(0);

		}

	}



}




bool Application::InitWindow(int width, int height)
{
	//GLogManager.logMessage("Creating OgreWinFrame");

	// 保存实例句柄
	mInstance = GetModuleHandle(NULL);

	HCURSOR mCursor = LoadCursor(NULL, IDC_ARROW);

	// 初始化
	WNDCLASS wc;										// 窗口类结构
	wc.style		 =	CS_HREDRAW | CS_VREDRAW |		// 移动时重画
		CS_DBLCLKS | CS_OWNDC;			// 接受双击消息, 并且窗口一直保持自身的DC
	wc.lpfnWndProc	 =	(WNDPROC)MsgProc;				// WndProc处理消息
	wc.cbClsExtra	 =	0;								// 无额外窗口数据
	wc.cbWndExtra	 =	0;								// 无额外窗口数据
	wc.hInstance	 =	mInstance;						// 设置实例
	wc.hIcon		 =	LoadIcon(NULL, IDI_APPLICATION);// 设置图标
	wc.hCursor		 =	mCursor;						// 装入鼠标指针
	wc.hbrBackground =	(HBRUSH)(BLACK_BRUSH);			// 指定系统背景图刷
	wc.lpszMenuName  =	NULL;							// 设置菜单
	wc.lpszClassName =	"OgreWinFrame";					// 设定类名字

	if (RegisterClass(&wc))
	{
		// 窗口信息结构
		CREATESTRUCT cs;
		ZeroMemory(&cs, sizeof(CREATESTRUCT));
		cs.hInstance	= mInstance;
		cs.hwndParent	= HWND_DESKTOP;
		cs.lpszName		= "CameraGame";
		cs.lpszClass	= "OgreWinFrame";
		cs.dwExStyle	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// 扩展窗体风格
		//modified by xumiao,将窗体的最大框取消，并禁止用户改变窗体大小
		cs.style		= WS_OVERLAPPED | WS_MINIMIZEBOX |WS_CAPTION |WS_SYSMENU;//WS_OVERLAPPEDWINDOW;					// 窗体风格 

		//cs.style =WS_POPUP;
		// 居中
		RECT rc = {0, 0, width, height};
		AdjustWindowRectEx(&rc, cs.style, FALSE, cs.dwExStyle);
		width = rc.right - rc.left;
		height = rc.bottom - rc.top;

		// Clamp width and height to the desktop dimensions
		int screenw = GetSystemMetrics(SM_CXSCREEN);
		int screenh = GetSystemMetrics(SM_CYSCREEN);
		if (width > screenw)
			width = screenw;
		if (height > screenh)
			height = screenh;

		cs.x = (screenw - width) / 2;
		cs.y = (screenh - height) / 2;
		cs.cx = width;
		cs.cy = height;

		// 创建窗口
		mHwnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style,
			cs.x, cs.y, cs.cx, cs.cy,
			cs.hwndParent, cs.hMenu, cs.hInstance, this);
		if (mHwnd)
		{
			// 显示窗口
			ShowWindow(mHwnd, SW_SHOW);

			return true;
		}
	}

	return false;
}

#endif