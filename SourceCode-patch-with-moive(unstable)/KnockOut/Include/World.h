#pragma once

#include "OgreVector3.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "Common.h"
#include "Node.h"
#include "DebugOverlay.h"
#include "PathGenerater.h"
#include "PlayerFactory.h"
#include "MovableText.h"

namespace Ogre {
    class SceneNode;
    class SceneManager;
}



namespace KnockOut{



	class KnockOutWorld : public SingletonT<KnockOutWorld>

	{
		SINGLETON_DEFINE(KnockOutWorld)


	public:
	
		KnockOutWorld();

		// You'll want various methods to access & change your world here
    
		void Think(float time);
    
		void Setup();

		void SetupDefaultGame();

		void newGame();

		void cleanUpAll();
	
		void DoSometing();

		bool ifStart;

		bool win;

		bool hasDefault;

		void SetupLevel1();
		void SetupLevel2();
		void SetupLevel3();

		bool showStatus;
		
		bool nextLevelClick;

		bool waitForNextLevelClick;
		
	 
		// You are going to want to keep track of your entities, in some kind 
		//  of list, map, table, set, or combination of lists, maps tables & sets.

		// For our example, we will just have a single instance variable.  You should
		//  Replace this with something else!

		Ogre::SceneManager *mSceneManager; 
		Ogre::RenderWindow* mWindow;
		Ogre::SceneNode *mBall;
		int **mapArray;
		DebugOverlay *debug;
		PlayerFactory *playerFactory;




		MovableText *homeText;
		String convertInt(int n);
		int homeHealth;
		bool idle;
	};




}

