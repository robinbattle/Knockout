#ifndef WALLFACTORY_H
#define WALLFACTORY_H

#include "Common.h"
#include "BaseFactory.h"
#include "DebugOverlay.h"
#include "Wall.h"


namespace KnockOut
{
	using namespace Ogre;

	class WallFactory : public BaseFactory, public SingletonT<WallFactory>
	{
		SINGLETON_DEFINE(WallFactory)
		

			

	public:
		WallFactory();

		typedef std::list<Wall*>::iterator WallIterator;
		
		std::list<Wall*> WallList;
		
		

		Wall* generate();

		virtual void update( float timeSinceLastFrame );

		bool hit;
		virtual void cleanUp();
	protected:
		

	
		virtual bool destroy(const std::string &name);

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		int IDCounter;


		void resetPath();


	

		Ogre::SceneManager *mSceneManager;


		DebugOverlay* debug;
		
	};

	
}

#endif