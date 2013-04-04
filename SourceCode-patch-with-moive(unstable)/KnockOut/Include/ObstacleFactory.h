#ifndef OBSTACLEFACTORY_H
#define OBSTACLEFACTORY_H

#include "Common.h"
#include "BaseFactory.h"
#include "DebugOverlay.h"
#include "Obstacle.h"
#include "KnockOutCamera.h"



namespace KnockOut
{
	using namespace Ogre;

	class ObstacleFactory : public BaseFactory, public SingletonT<ObstacleFactory>
	{
		SINGLETON_DEFINE(ObstacleFactory)
		

			

	public:
		ObstacleFactory();

		typedef std::list<Obstacle*>::iterator ObstacleIterator;
		typedef std::map<std::string, ObstacleIterator>::iterator ObstacleIndexIterator;
		std::list<Obstacle*> ObstacleList;
		std::map<std::string, ObstacleIterator> ObstacleIndex;	

		virtual void cleanUp();

		Obstacle* generate();

		virtual void update( float timeSinceLastFrame );

		bool hit;

	protected:
		


		virtual Obstacle* get(const std::string &name);

	
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

		

		DebugOverlay* debug;
		
	};

	
}

#endif