#ifndef TOWERFACTORY_H
#define TOWERFACTORY_H

#include "Common.h"
#include "DebugOverlay.h"
#include "BaseTower.h"
#include "BaseFactory.h"
#include "TowerA.h"
#include "TowerB.h"
namespace KnockOut
{
	using namespace Ogre;


	class TowerFactory : public BaseFactory, public SingletonT<TowerFactory>
	{
		SINGLETON_DEFINE(TowerFactory)
		

			

	public:
		TowerFactory();

		typedef std::list<BaseTower*>::iterator TowerIterator;
		std::list<BaseTower*> towerList;
		
		typedef std::list<BaseTower*>::iterator TowerAIterator;
		std::list<BaseTower*> towerAList;


		BaseTower* generate(QueryFlags type);

		virtual void update( float timeSinceLastFrame );

		virtual void cleanUp();

	protected:
		
		virtual bool destroy(const std::string &name);

		Ogre::Entity* entity;
		Ogre::SceneNode* sceneNode;

		int IDCounter;
		
		Ogre::Vector3 calculateDirection(Ogre::Vector3 cam, Ogre::Vector3 object);



		DebugOverlay* debug;
		
	};

	
}

#endif