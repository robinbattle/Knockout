

#ifndef USERGUIMANAGER_H
#define USERGUIMANAGER_H

#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI.h>
#include <Ogre.h>

#include "Common.h"
//#include "InputHandler.h"
//#include "ObjectPlacement.h"
namespace KnockOut{

	


	class UserGUI: public SingletonT<UserGUI>
	{
		SINGLETON_DEFINE(UserGUI)
		
	public:
		
		
		void resetHealthBar(Real val);
		void update(float time);

		void addMoney(int val);
		void setMoney(int val){moneyVal = val;}
		void substractMoney(int val);

		int getMoney();
		bool ifSubstractMoney(int val);

		OverlayContainer *tower1;
		OverlayContainer *tower2;
		OverlayContainer *tower3;
		OverlayContainer *tower4;

		OverlayContainer *tnextLevel;

		bool ifShow;

		void hide();
		void show();

		void HideOrShow();
		OverlayContainer *loseP;
		OverlayContainer *winP;
		Real lifeValue;
		//void UserGUI::showLosePic();
		//void UserGUI::showWinPic();
		bool lose;
		OverlayContainer *controlPic;

	protected:
		UserGUI();
		bool ifGUI;

		int moneyVal;

		Ogre::Root *mRoot;
		Ogre::RenderWindow* mWindow;
		Ogre::SceneManager* mSceneMgr;
		
		CEGUI::OgreRenderer* mRenderer;
		
		//CEGUI::WindowManager &wmgr;
		CEGUI::Window *sheet;
		
		CEGUI::Window *next_wave;
		CEGUI::Window *load_classic;
		CEGUI::Window *battle_editor;
		CEGUI::Window *quit;

		CEGUI::Window *mini_map;

		void resetTowerMoneyCostColour();


		bool nextWave(const CEGUI::EventArgs &e);
	

		void miniMap();
		Ogre::Camera *cam;
		
	private:
		
		void initGUI();
		
		void setupMenuGUI();
		
		OverlayManager *olmGUI;
		OverlayContainer *panelGUI ;
		Overlay *overlayGUI;
		TextAreaOverlayElement *textAreaGUI;
		String szElementGUI;
		OverlayContainer *panelGUI2 ;
		Overlay *overlayGUI2;
		TextAreaOverlayElement *textAreaGUI2;
		TextAreaOverlayElement *textAreaGUIMoney;

		TextAreaOverlayElement *tower1Money;
		TextAreaOverlayElement *tower2Money;
		TextAreaOverlayElement *tower3Money;
		TextAreaOverlayElement *tower4Money;

		
		
		OverlayContainer *tankExp;
		OverlayContainer *money;
	
		std::string convertInt(int n);
		//ObjectPlacement *objectPlacement;

		
	};
}

#endif