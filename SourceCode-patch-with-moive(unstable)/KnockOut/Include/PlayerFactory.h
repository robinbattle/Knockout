#pragma once
#include "Common.h"
#include "Player.h"

namespace KnockOut
{


	class PlayerFactory : public SingletonT<PlayerFactory>
	{
		SINGLETON_DEFINE(PlayerFactory)
	public:
		PlayerFactory();

		virtual Player* generate();

		virtual void update( float timeSinceLastFrame );
		Player *myPlayer;
		virtual void cleanUp(){}

		bool allowRebirth;

	protected:
		
		int IDCounter;

		//virtual Object* get(const std::string &name) = 0;

	
		
		
		

		std::string convertInt(int n){return NULL;}

		Ogre::SceneManager *mSceneManager;

		float reBirthWaiting;

		void tryBirthPlayer();

		
	};
}