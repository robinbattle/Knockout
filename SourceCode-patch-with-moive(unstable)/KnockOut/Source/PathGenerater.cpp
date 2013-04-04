#include "PathGenerater.h"

#include <stdint.h>
using namespace std;
namespace  KnockOut

{
	PathGenerater::PathGenerater(int m, int n)
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		generateNodeCD = 0.2;
		ifgenerated = false;
		q = 0;
		mapArray = 0;
		pathNodeCount = 0;
		allocate(m, n);
		yes = false;
		placed = false;
		wallFactory = WallFactory::getSingletonPtr();
	}

	bool PathGenerater::readInt(int val, int i, int j)
	{
		mapArray[i][j] = val;
		return true;
	}

	int** PathGenerater::getPathMap(Vector2 vB, Vector2 vF)
	{
	
		int i,j;


		pf = new PathFinding();

		srand(time(NULL));

		// create empty map
		for(int y=0;y<m;y++)
		{
			for(int x=0;x<n;x++) 
				pf->map[x][y]=0;
		}

		// fillout the map matrix with a '+' pattern
		for(int x=n/8;x<n*7/8;x++)
		{
			pf->map[x][m/2]=1;
		}
		for(int y=m/8;y<m*7/8;y++)
		{
			pf->map[n/2][y]=1;
		}

		//obstacle
		for(int i = 0; i < 15; i ++)
			for(int j = 0; j < 15; j ++)
			{
				if(mapArray[i][j] == 1)
					pf->map[i][j] = 1;
			}


   
		int xA, yA, xB, yB;


		xA = vB.x, yA = vB.y;
		xB = vF.x, yB = vF.y;

		cout<<"Map Size (X,Y): "<<n<<","<<m<<endl;
		cout<<"Start: "<<xA<<","<<yA<<endl;
		cout<<"Finish: "<<xB<<","<<yB<<endl;
		// get the route
		clock_t start = clock();
		//PathFinding *pf = new PathFinding();
		string route=pf->pathFind(xA, yA, xB, yB);
		if(route=="") cout<<"An empty route generated!"<<endl;
		clock_t end = clock();
		double time_elapsed = double(end - start);
		cout<<"Time to calculate the route (ms): "<<time_elapsed<<endl;
		cout<<"Route:"<<endl;
		cout<<route<<endl<<endl;

		// follow the route on the map and display it 
		if(route.length()>0)
		{
			int j; char c;
			int x=xA;
			int y=yA;
			pf->map[x][y]=2;
			for(int i=0;i<route.length();i++)
			{
				c =route.at(i);
				j=atoi(&c); 
				x=x+dx[j];
				y=y+dy[j];
				pf->map[x][y]=3;
				positionList.push_back(Vector2(x, y));
			}
		   pf-> map[x][y]=4;
    
			// display the map with the route
			for(int y=0;y<m;y++)
			{
				for(int x=0;x<n;x++)
					if(pf->map[x][y]==0)
						cout<<".";
					else if(pf->map[x][y]==1)
						cout<<"O"; //obstacle
					else if(pf->map[x][y]==2)
						cout<<"S"; //start
					else if(pf->map[x][y]==3)
						cout<<"R"; //route
					else if(pf->map[x][y]==4)
						cout<<"F"; //finish
				cout<<endl;
			}
		}

		
		
		if(route == "")
			return NULL;
		else
		{
		
			for(int i = 0; i < 15; i ++)
				for(int j = 0; j < 15; j ++)
					mapArray[i][j] = pf->map[i][j];
			return mapArray;

		}

	
		return NULL;
		}

		bool PathGenerater::allocate(int m, int n)
		{
			mapArray = new int*[n];
			for(int i = 0;i < n;i++)
				mapArray[i]=new int[m];

			return true;
		}

		bool PathGenerater::deallocate(int n)
		{
			 int i;
			 for(i=0;i<n;i++)
				delete[] mapArray[i];
			 delete[] mapArray;
	
			 return true;
		}

		bool PathGenerater::freeOldPathNode()
		{
			for(int i = 0; i < pathNodeCount; i++)
			{
				mSceneManager->destroyEntity("PathNodeEntity"+ convertInt(i));
				mSceneManager->destroySceneNode("PathNodeSceneNode"+ convertInt(i));
			}
			pathNodeCount = 0;
			yes = true;
			return true;
		}

		bool PathGenerater::pathPlaced(int offsetX, int offsetY, int offsetZ)
		{
			

			Ogre::Vector3 position;

			
		

			if(mapArray != NULL)
			{
				for(int i = 0; i < 15; i ++)
				{
	
					for(int j = 0; j < 15; j ++)
					{
		
						if(mapArray[i][j] == 3)
						{
							
							
							ent = mSceneManager->createEntity("PathNodeEntity"+ convertInt(pathNodeCount), "tree.mesh");
							mCurrentObject = mSceneManager->getRootSceneNode()->createChildSceneNode("PathNodeSceneNode"+ convertInt(pathNodeCount));
							mCurrentObject->attachObject(ent);
							position.x = i * 100 - offsetX;
							position.y = offsetY;
							position.z = j * 100 - offsetZ;
							mCurrentObject->setPosition(position);
							
						
							mCurrentObject->scale(5, 10, 5);
							
							
							pathNodeCount++;
						}
						
					}

				}
		
			}
		ifgenerated = true;
		return true;
	}
	
	std::string PathGenerater::convertInt(int n)
	{
		std::stringstream ss;
		ss << n;
		return ss.str();
	}


	void PathGenerater::update(float time)
	{

	
	}

	bool PathGenerater::obstaclePlaced(int offsetX, int offsetY, int offsetZ)
	{

		
		

		Entity* ent;
		SceneNode* mCurrentObject;
		
		Vector3 position;
			
		if(mapArray != NULL)
		{
			for(int i = 0; i < 15; i ++)
			{

				for(int j = 0; j < 15; j ++)
				{
	
					if(mapArray[i][j] == 1)
					{
						mCurrentObject = wallFactory->generate()->getSceneNode();
						position.x = i * 100 - offsetX;
						position.y = offsetY;
						position.z = j * 100 - offsetZ;
						mCurrentObject->setPosition(position);
						
						/*
						ent = mSceneManager->createEntity("mytank.mesh"); //razor
						mCurrentObject = mSceneManager->getRootSceneNode()->createChildSceneNode();
						mCurrentObject->attachObject(ent);
						position.x = i * 100 - offsetX;
						position.y = offsetY;
						position.z = j * 100 - offsetZ;
						mCurrentObject->setPosition(position);
						mCurrentObject->scale(3, 3, 3);
						*/
					}
					//
				}

			}
		
		}
		return true;
	}

	void PathGenerater::writeInBitMap(Vector3 newPosition)
	{
		DebugOverlay * debug = DebugOverlay::getSingletonPtr();
		int weightMin, weightMax, heightMin, heightMax;
		Ogre::Vector3 position;
		
		for(int i = 0; i < 15; i ++)
		{
			

				for(int j = 0; j < 15; j ++)
				{
					position.x = i * 100.0f - 750.0f;
					position.z = j * 100.0f - 750.0f;

					weightMin = position.x - 50.0f;
					weightMax = position.x + 50.0f;
					heightMin = position.z - 50.0f;
					heightMax = position.z + 50.0f;

					if(weightMin < newPosition.x && 
					   newPosition.x < weightMax && 
					   heightMin < newPosition.z && 
					   newPosition.z < heightMax)
					{
						mapArray[i][j] = 1;
						placed = true;
						DebugOverlay * debug = DebugOverlay::getSingletonPtr();
						debug->setText4("Found it");
					}
				}
		}

		//check if re-calculate path
		if(placed)
		{
			getPathMap(Vector2(0,0),Vector2(15,15));
			//aiManager->reCalculatePath();
		
		}
			
	}
	

}