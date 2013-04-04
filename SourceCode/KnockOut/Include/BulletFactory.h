#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include "Common.h"
#include "BaseFactory.h"
#include "DebugOverlay.h"
#include "Bullet.h"
#include "LightChain.h"

namespace KnockOut
{
	using namespace Ogre;



	class BulletFactory : public BaseFactory, public SingletonT<BulletFactory>
	{
		SINGLETON_DEFINE(BulletFactory)
		
		
			

	public:
		BulletFactory();

		typedef std::list<Bullet*>::iterator BulletIterator;
		
		std::list<Bullet*> bulletList;
		
		Bullet *bullet;

		Bullet* generate(Vector3 position, Quaternion orientation, BULLET_TYPE type);

		virtual void update( float timeSinceLastFrame );

		virtual void cleanUp();

	protected:
		

	
		virtual bool destroy(const std::string &name);

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		int IDCounter;



		Ogre::SceneManager *mSceneManager;


		DebugOverlay* debug;
		
	};

	
}

#endif