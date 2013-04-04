#pragma once
#include "InputHandler.h"
#include "OgreFrameListener.h"
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "Common.h"
#include "InputHandler.h"
#include "World.h"
#include "AIManager.h"
#include "BaseFactory.h"
#include "Common.h"
#include "EnemyFactory.h"
#include "KnockOutCamera.h"
#include "PathManager.h"
#include "PlayerFactory.h"
#include "CollisionManager.h"
#include "BulletFactory.h"
#include "TowerFactory.h"
#include "ObstacleFactory.h"
#include "WallFactory.h"
#include "UserGUI.h"
namespace KnockOut
{



	class KnockOutFrameListener : public Ogre::FrameListener,  public SingletonT<KnockOutFrameListener>
	{
		SINGLETON_DEFINE(KnockOutFrameListener)
	public:
		KnockOutFrameListener() ;

		virtual bool frameStarted(const Ogre::FrameEvent &evt);
		

	protected:
		InputHandler *mInputHandler;
		AIManager *mAIManager;
		KnockOutWorld *mWorld;
		KnockOutCamera *mKnockOutCamera;
		EnemyFactory *ef;
		PathManager *pathManager;
		PlayerFactory *playerFactory;
		CollisionManager *collisionManager;
		BulletFactory *bulletFactory;
		TowerFactory *towerFactory;
		ObstacleFactory *obstacleFactory;
		WallFactory *wallFactory;
		UserGUI *userGUI;
	};



}
