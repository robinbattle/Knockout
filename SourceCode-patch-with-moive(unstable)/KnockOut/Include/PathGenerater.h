#pragma once
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include "Ogre.h"
#include "PathFinding.h"
#include "DebugOverlay.h"
#include "WallFactory.h"




namespace KnockOut
{
	using namespace Ogre;
	class PathGenerater
	{

	
	

	public:
		PathGenerater(int m, int n);

		typedef std::list<Vector2>::iterator PositionIterator;
		std::list<Vector2> positionList;

		void update(float time);
	
		bool readInt(int val, int i, int j);

		int** getPathMap(Vector2 vB, Vector2 vF);

		bool allocate(int m, int n);

		bool deallocate(int n);

		bool obstaclePlaced(int offsetX, int offsetY, int offsetZ);
		bool pathPlaced(int offsetX, int offsetY, int offsetZ);

		int q;
		PathFinding *pf;
		int **mapArray;

		bool ifgenerated;
		float generateNodeCD;

		SceneManager *mSceneManager;
		Entity* ent;							
		SceneNode* mCurrentObject;

		int pathNodeCount;

		bool freeOldPathNode();

		bool yes;
		bool placed;
		std::string convertInt(int n);

		void writeInBitMap(Vector3 position);

		WallFactory* wallFactory;
	};





}
