
/************************************************

window 入口函数
**************************************************/






#include "pch.h"
#include "Application.h"




INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
	


	
	//获得当前进程目录
	char pBuffer[1024];
	ZeroMemory(pBuffer, 1024);
	GetModuleFileName(NULL, pBuffer, 1024);

	//设置当前目录为进程目录，防止通过文件关联打开程序的当前目录不正确
	Ogre::String dirname,filename,extname;
	Ogre::String cc=pBuffer;

	Ogre::StringUtil::splitFullFilename(cc , filename , extname , dirname);
	SetCurrentDirectory(dirname.c_str());
	//////////////////////////////////////////////////////////////////////////



	try
	{

		Application* pApp= new  Application();
		pApp->go();
		delete Application::getSingletonPtr();

	}
	catch(std::exception &e)
	{
		//MessageBox(NULL, e.getFullDescription().c_str(), "Exception", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		MessageBox(NULL, e.what(), "Exception", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		
	}


	return 0;
}




