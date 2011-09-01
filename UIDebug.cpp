#include "pch.h"
#include "UIDebug.h"
#include "Application.h"

//-------------------------------------------------------
UIDebug::UIDebug()
:UIBase("UIDebeg",""),m_pParamsPanel(NULL),m_pFpsLabel(NULL)
{


}


//-------------------------------------------------------
UIDebug::~UIDebug()
{

}

//-------------------------------------------------------
void UIDebug::init()
{
	UIBase::init();


	
	m_pFpsLabel=new Label("UIDebug/FpsLabel","FPS:",180.0f);
	registerWidget(m_pFpsLabel);
	m_pFpsLabel->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pFpsLabel->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pFpsLabel->setTop(-50.0f);

	m_pParamsPanel = new ParamsPanel("UIDebug/panel", 180, 0);
	registerWidget(m_pParamsPanel);
	Ogre::StringVector stats;
	stats.push_back("Average FPS");
	stats.push_back("Best FPS");
	stats.push_back("Worst FPS");
	stats.push_back("Triangles");
	stats.push_back("Batches");
	m_pParamsPanel->setAllParamNames(stats);

	m_pParamsPanel->setHorizontalAlignment(Ogre::GHA_LEFT);
	m_pParamsPanel->setVerticalAlignment(Ogre::GVA_BOTTOM);
	m_pParamsPanel->setTop(-100.0f);
	m_pParamsPanel->setHeight(180);



}


//-------------------------------------------------------
void UIDebug::update(float time)
{
	UIBase::update(time);

	Ogre::RenderTarget* pWindow=Application::getSingleton().getRenderWindows();
	Ogre::RenderTarget::FrameStats stats = pWindow->getStatistics();

	std::ostringstream oss;
	Ogre::String s;

	oss << "FPS: " << std::fixed << std::setprecision(1) << stats.lastFPS;
	s = oss.str();
	for (int i = s.length() - 5; i > 5; i -= 3) 
	{ 
		s.insert(i, 1, ','); 
	}
	m_pFpsLabel->setCaption(s);


	Ogre::StringVector values;

	oss.str("");
	oss  << std::setprecision(1) << stats.avgFPS;
	Ogre::String str = oss.str();
	for (int i = str.length() - 5; i > 0; i -= 3) { str.insert(i, 1, ','); }
	values.push_back(s);

	oss.str("");
	oss << std::fixed << std::setprecision(1) << stats.bestFPS;
	str = oss.str();
	for (int i = str.length() - 5; i > 0; i -= 3) { str.insert(i, 1, ','); }
	values.push_back(s);

	oss.str("");
	oss << std::fixed  << std::setprecision(1) << stats.worstFPS;
	str = oss.str();
	for (int i = str.length() - 5; i > 0; i -= 3) { str.insert(i, 1, ','); }
	values.push_back(str);

	str = Ogre::StringConverter::toString(stats.triangleCount);
	for (int i = str.length() - 3; i > 0; i -= 3) { str.insert(i, 1, ','); }
	values.push_back(str);

	str = Ogre::StringConverter::toString(stats.batchCount);
	for (int i = str.length() - 3; i > 0; i -= 3) { str.insert(i, 1, ','); }
	values.push_back(str);

	m_pParamsPanel->setAllParamValues(values);

	return ;

}