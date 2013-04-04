#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Common.h"
#include "BaseFactory.h"
#include "DebugOverlay.h"
#include "Enemy.h"
#include "KnockOutCamera.h"
#include "UserGUI.h"


namespace KnockOut
{
	using namespace Ogre;

	class EnemyFactory : public BaseFactory, public SingletonT<EnemyFactory>
	{
		SINGLETON_DEFINE(EnemyFactory)
		

			

	public:
		EnemyFactory();

		typedef std::list<Enemy*>::iterator EnemyIterator;
		typedef std::map<std::string, EnemyIterator>::iterator EnemyIndexIterator;
		std::list<Enemy*> enemyList;
		std::map<std::string, EnemyIterator> enemyIndex;	

		typedef std::list<Enemy*>::iterator EnemyDeadIterator;
		std::list<Enemy*> enemyDeadList;

		Enemy* generate(int type);

		virtual void update( float timeSinceLastFrame );

		bool hit;
		virtual void cleanUp();
	protected:
		


		virtual Enemy* get(const std::string &name);

	
		virtual bool destroy(const std::string &name);

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		int IDCounter;
		//std::string convertInt(int n);
		//std::string appropriateName(NAME_TYPE type);

		void resetPath();


		void sillyRotation(float time, Ogre::SceneNode *sceneNode);
		void sillyHitCamera(float time, Ogre::SceneNode *sceneNode);
		Ogre::Vector3 calculateDirection(Ogre::Vector3 cam, Ogre::Vector3 object);

		Ogre::SceneManager *mSceneManager;

		float mRotationSpeed;
		Ogre::Camera* mCamera;
		KnockOutCamera *mKnockOutCamera;

		UserGUI *userGUI;

		DebugOverlay* debug;
		
	};

	
}

#endif