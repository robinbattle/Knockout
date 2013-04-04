#pragma once
#include "Common.h"
#include "World.h"
#include "SingletonT.h"
#include "EnemyFactory.h"
#include "PathManager.h"
//#include "World.h"
namespace KnockOut
{


	class AIManager : public SingletonT<AIManager>
	{
		SINGLETON_DEFINE(AIManager)

	public:
		// You may want to add parameters to the AI Manager constructor
		AIManager();
		~AIManager();

		// Go through all of the AIs, and call think on each one
		void Think(float time);

		


		PathManager *pathManager;

		bool reCalculatePath();
		bool release;
		bool playerRelease;
		bool levelFinished;
		bool generateEnemy;
		void setLevel(int level, int number); 
		int getLevel(){return level;}
	protected:
		//KnockOutWorld *mWorld;
		EnemyFactory *enemyFactory;
		DebugOverlay *debug;
		int number;
		
		int level;

		int currentLevelTotalEnemy;

		void updateLevel1(float time);
		void updateLevel2(float time);
		void updateLevel3(float time);
		
		Real releaseCDExternal;
		Real releaseCDInternal;
		// Probablay want a list of individual AI classes here ...
	};


}



 