#pragma once
#include "Common.h"
//#include "BaseFactory.h"

namespace KnockOut
{

	using namespace Ogre;

	enum NAME_TYPE
	{
			SCENE_NODE,
			ENTITY,
			PARTICLE
	};

	class BaseObject
	{
		
	

	public:
		BaseObject(int ID)
		{
			mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");	
			debug = DebugOverlay::getSingletonPtr();
			mName = convertInt(ID);
		}

		//virtual ~BaseObject();
		virtual void setUp(){}

		typedef std::list<Vector2>::iterator OwnPathIterator;
		std::list<Vector2> ownPathPositionList;

		inline std::string getName() const { return mName; }
		virtual Ogre::SceneNode* getSceneNode(){return sceneNode;}
		virtual Ogre::Entity* getEntity(){return entity;}
		virtual BaseObject* getObject(){return this;}

		virtual void update(float time){}

		virtual void destroy(){}

		int ID;

	protected:
		
		SceneNode* sceneNode;
		Entity* entity;
		std::string mName;
		SceneManager *mSceneManager;

		
		DebugOverlay *debug;

		virtual std::string convertInt(int n)
		{
			StringStream ss;
			ss << n;
			return ss.str();
		
		}
		

	};
}