#pragma once
#include "Common.h"
#include "World.h"
#include "SingletonT.h"
#include "PathGenerater.h"
#include "PathGenerater.h"
#include "EnemyFactory.h"

namespace KnockOut
{


	class PathManager : public SingletonT<PathManager>
	{
		SINGLETON_DEFINE(PathManager)

	public:
		// You may want to add parameters to the AI Manager constructor
		PathManager();
		~PathManager();

		// Go through all of the AIs, and call think on each one
		void Think(float time);

		void showPath();

		float holdGenerate;
		float CD_MAX;

		bool pathExist;

		void update(float time);

		void readMap(int ID);

		PathGenerater *pathGenerater;

		bool reCalculatePath();

		void clearAndCalculatePath(Vector2 vF, Vector2 vT);

	protected:
		KnockOutWorld *mWorld;
		EnemyFactory *enemyFactory;



		// Probablay want a list of individual AI classes here ...
	};


}



 