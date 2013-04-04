#include "AIManager.h"

namespace KnockOut
{

	AIManager::AIManager()
	{
		// Any initialization that needs to be done ...
		//mWorld = KnockOutWorld::getSingletonPtr();

		enemyFactory = EnemyFactory::getSingletonPtr();
		pathManager = PathManager::getSingletonPtr();
		number = 0;

		debug = DebugOverlay::getSingletonPtr();
		release = false;
		playerRelease = false;
		releaseCDExternal = 3.0f;
		releaseCDInternal = 1.0f;
		level = 0;
		currentLevelTotalEnemy = 0;
		levelFinished = false;
		generateEnemy = false;
		//mWorld = KnockOutWorld::getSingletonPtr();
	}

	AIManager::~AIManager()
	{
		
	}

	void AIManager::setLevel(int newLevel, int number)
	{
		level = newLevel;
		currentLevelTotalEnemy = number;
	}


	void 
	AIManager::Think(float time)
	{

		if(level == 0)
			return;

		if(level == 1)
			updateLevel1(time);
		else if(level == 2)
			updateLevel2(time);
		else if(level == 3)
			updateLevel3(time);


	
		
	}

	void AIManager::updateLevel1(float time)
	{
		
		if(levelFinished)
			return;

		if(generateEnemy)
		{
		
			releaseCDExternal -= time;

			if(releaseCDExternal <0)
				release = true;

			if(release || playerRelease)
			{
					releaseCDExternal = 5.0f;
					releaseCDInternal -= time;
				

					if(releaseCDInternal < 0)
					{
						releaseCDInternal = 1.0f;
						Enemy* e;
						if(currentLevelTotalEnemy % 10 == 0){
							e = enemyFactory->generate(4);
						}else{
							e = enemyFactory->generate(1);
						}


						
						e->getSceneNode()->setPosition(-750, 0 , -750);
						Ogre::Vector2 v2;
				
						pathManager->clearAndCalculatePath(Vector2(0,0), Vector2(14,14));
						//deep copy path list
						for (PathGenerater::PositionIterator p = pathManager->pathGenerater->positionList.begin(); p != pathManager->pathGenerater->positionList.end();)
						{
							v2 = *p;
							e->ownPathPositionList.push_back(v2);
							p++;
						}
			
						number++;
						currentLevelTotalEnemy --;
					

						if(currentLevelTotalEnemy <= 0)
						{
							playerRelease = false;
							release = false;
							generateEnemy = false;
						}

						if(number >= 10)
						{
							number = 0;
							playerRelease = false;
							release = false;
							releaseCDExternal = 15.0f;
						}
				
					}
		
			}


			if(pathManager->pathGenerater->placed == true)
			{
				reCalculatePath();
				pathManager->pathGenerater->placed = false;
			}
		
		
		}else// not generate
		{
			if(enemyFactory->enemyList.empty())
			{
				levelFinished = true;
			}
		}
	}

	void AIManager::updateLevel2(float time)
	{
		if(levelFinished)
			return;

		if(generateEnemy)
		{
		
			releaseCDExternal -= time;

			if(releaseCDExternal <0)
				release = true;

			if(release || playerRelease)
			{
					releaseCDExternal = 5.0f;
					releaseCDInternal -= time;
				

					if(releaseCDInternal < 0)
					{
						releaseCDInternal = 1.0f;

						Enemy* e;
						if(currentLevelTotalEnemy % 10 == 0){
							e = enemyFactory->generate(4);
						}else if(currentLevelTotalEnemy % 2 == 0){
							e = enemyFactory->generate(2);
						}else {
							e = enemyFactory->generate(1);
						}
						Ogre::Vector2 v2;
						e->getSceneNode()->setPosition(-750, 0 , -750);
						pathManager->clearAndCalculatePath(Vector2(0,0), Vector2(14,14));
						//deep copy path list
						for (PathGenerater::PositionIterator p = pathManager->pathGenerater->positionList.begin(); p != pathManager->pathGenerater->positionList.end();)
						{
							v2 = *p;
							e->ownPathPositionList.push_back(v2);
							p++;
						}
			
						number++;
						currentLevelTotalEnemy --;
					

						if(currentLevelTotalEnemy <= 0)
						{
							playerRelease = false;
							release = false;
							generateEnemy = false;
						}

						if(number >= 10)
						{
							number = 0;
							playerRelease = false;
							release = false;
							releaseCDExternal = 15.0f;
						}
				
					}
		
			}


			if(pathManager->pathGenerater->placed == true)
			{
				reCalculatePath();
				pathManager->pathGenerater->placed = false;
			}
		
		
		}else// not generate
		{
			if(enemyFactory->enemyList.empty())
			{
				levelFinished = true;
			}
		}
	}

	void AIManager::updateLevel3(float time)
	{
		if(levelFinished)
			return;

		if(generateEnemy)
		{
		
			releaseCDExternal -= time;

			if(releaseCDExternal <0)
				release = true;

			if(release || playerRelease)
			{
					releaseCDExternal = 5.0f;
					releaseCDInternal -= time;
				

					if(releaseCDInternal < 0)
					{
						releaseCDInternal = 1.0f;
						Enemy *e;
						if(currentLevelTotalEnemy % 10 == 0){
							e = enemyFactory->generate(5);
						}else if(currentLevelTotalEnemy % 9 == 0){
							e = enemyFactory->generate(4);
						}else if(currentLevelTotalEnemy % 3 == 0){
							e = enemyFactory->generate(3);
						}else if(currentLevelTotalEnemy % 2 == 0){
							e = enemyFactory->generate(2);
						}else {
							e = enemyFactory->generate(1);
						}
						e->getSceneNode()->setPosition(-750, 0 , -750);
						Ogre::Vector2 v2;
				
						pathManager->clearAndCalculatePath(Vector2(0,0), Vector2(14,14));
						//deep copy path list
						for (PathGenerater::PositionIterator p = pathManager->pathGenerater->positionList.begin(); p != pathManager->pathGenerater->positionList.end();)
						{
							v2 = *p;
							e->ownPathPositionList.push_back(v2);
							p++;
						}
			
						number++;
						currentLevelTotalEnemy --;
					

						if(currentLevelTotalEnemy <= 0)
						{
							playerRelease = false;
							release = false;
							generateEnemy = false;
						}

						if(number >= 10)
						{
							number = 0;
							playerRelease = false;
							release = false;
							releaseCDExternal = 15.0f;
						}
				
					}
		
			}


			if(pathManager->pathGenerater->placed == true)
			{
				reCalculatePath();
				pathManager->pathGenerater->placed = false;
			}
		
		
		}else// not generate
		{
			if(enemyFactory->enemyList.empty())
			{
				levelFinished = true;
			}
		}
	}


	bool AIManager::reCalculatePath()
	{
		Ogre::Vector2 v2;
		Enemy *e;

		

		for (EnemyFactory::EnemyIterator ei = enemyFactory->enemyList.begin(); ei != enemyFactory->enemyList.end(); ){
			e = *ei;

			if(e->ownPathPositionList.empty()){
				ei++;
				continue;
				
			}
				

			
			Ogre::Vector2 current= *e->ownPathPositionList.begin();

			pathManager->clearAndCalculatePath(current, Vector2(14,14));
			
			//clear current object path list
			e->ownPathPositionList.clear();
			
			

			//make deep copy of path list
			for (PathGenerater::PositionIterator p = pathManager->pathGenerater->positionList.begin(); p != pathManager->pathGenerater->positionList.end();)
			{
				v2 = *p;
				e->ownPathPositionList.push_back(v2);
				p++;
			}
			
			ei++;
			
		}
		
	
		return true;
	}


}