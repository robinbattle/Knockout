#pragma once
#include "Common.h"
#include "BaseObject.h"

namespace KnockOut
{


	class BaseFactory
	{
		//SINGLETON_DEFINE(BaseFactory)
	public:
		BaseFactory(){}

		virtual BaseObject* generate(){return NULL;}

		virtual void update( float timeSinceLastFrame ){}

	protected:
		
		virtual void cleanUp(){}

		//virtual Object* get(const std::string &name) = 0;

	
		virtual bool destroy(const std::string &name){return NULL;}

		

		std::string convertInt(int n){return NULL;}

		Ogre::SceneManager *mSceneManager;

		
	};
}