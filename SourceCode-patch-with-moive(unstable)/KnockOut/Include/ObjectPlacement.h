#ifndef OBJECTPLACEMENT_H
#define OBJECTPLACEMENT_H


#include "Common.h"
#include "KnockOutCamera.h"
#include "ObstacleFactory.h"
#include "PathManager.h"

#include "Common.h"

#include<math.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "TowerFactory.h"
#include "UserGUI.h"
#include "EnemyFactory.h"

namespace KnockOut
{


	class ObjectPlacement : public SingletonT<ObjectPlacement>
	{
		SINGLETON_DEFINE(ObjectPlacement)
		
		

	public:
		ObjectPlacement();

		bool ObjectPlaceOnMousePressed();
		bool ObjectPlaceOnMouseMoved();
		bool ObjectPlaceOnMouseReleased();
		QueryFlags currentType;             //current type

		Ogre::SceneNode *mCurrentObject;	//pointer to our currently selected object         //it need to be set to 0 when clear all
		//Ogre::Entity *mCurrentEntity;
	protected:

		Ogre::Vector3 getNewPosition(Ogre::Vector3 origin, Ogre::Vector3 direction, Ogre::Real distance);

		KnockOutWorld *mWorld;
		KnockOutCamera *mKnockOutCamera;
		Ogre::RenderWindow *mRenderWindow;
		
		Ogre::SceneManager *mSceneMgr; 
		Ogre::RaySceneQuery* mRayScnQuery;	//pointer to our ray scene query
		
		CEGUI::Renderer* mGUIRenderer;		//our CEGUI renderer
		Ogre::Vector3 origin;
	
		Ogre::Vector3 direction;
		int mCount;						//number of objects created

		ObstacleFactory* obstacleFactory;
		PathManager* pathManager;
		TowerFactory *towerFactory;
		UserGUI *userGUI;
		EnemyFactory *enemyFactory;
		QueryFlags myCurrentSelectType;

		int towerBullet;
		int towerFire;
		int towerArea;
		int towerFrost;
		int magicPickup;

		Enemy* findThisEnemy();


		bool currentIsEnemy;

		Real uplift;
	};

}

#endif