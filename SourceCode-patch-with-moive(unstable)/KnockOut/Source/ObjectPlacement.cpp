#include "ObjectPlacement.h"
#include "DebugOverlay.h"
#include "World.h"


namespace KnockOut
{
	KnockOutWorld *MOWorld;
	DebugOverlay *debug;
	ObjectPlacement::ObjectPlacement()
	{
		mKnockOutCamera = KnockOutCamera::getSingletonPtr();
		mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		mRenderWindow = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();
		mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());
		obstacleFactory = ObstacleFactory::getSingletonPtr();
		pathManager = PathManager::getSingletonPtr();
		towerFactory = TowerFactory::getSingletonPtr();
		userGUI = UserGUI::getSingletonPtr();
		debug = DebugOverlay::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		mCount = 0;
		mCurrentObject = 0;
		currentIsEnemy = false;
		currentType = TOWER_BULLET_MASK;

		towerBullet = 50;
		towerFire = 100;
		towerArea = 500;
		towerFrost = 400;
		magicPickup = 0;

		uplift = 20;

		MOWorld = KnockOutWorld::getSingletonPtr();
	
	}

	Enemy* ObjectPlacement::findThisEnemy()
	{
		Enemy* enemy;
		for (EnemyFactory::EnemyIterator e = enemyFactory->enemyList.begin(); e != enemyFactory->enemyList.end(); e++ ){
			enemy = *e;
			if(enemy->getSceneNode() == mCurrentObject && !enemy->nearlyDie ) //compare if ptr is equal
			{
				return enemy;
			}
		}
		
		return NULL;
	}


	bool ObjectPlacement::ObjectPlaceOnMousePressed()
	{
			if(MOWorld->waitForNextLevelClick == true)
				return true;

			if(currentIsEnemy && mCurrentObject && !findThisEnemy())
			{
				mCurrentObject = 0;
				currentIsEnemy = false;
			}

			if(mCurrentObject)
			{
				mCurrentObject->showBoundingBox(false);
			}


			//find the current mouse position
			CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
 
		
		

			//then send a raycast straight out from the camera at the mouse's position
			Ogre::Ray mouseRay = mKnockOutCamera->mRenderCamera->getCameraToViewportRay(mousePos.d_x/mRenderWindow->getWidth(), mousePos.d_y/mRenderWindow->getHeight());
			//Ogre::Ray mouseRay = mTankWarCamera->mRenderCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
		
			//if(mousePos.d_x/mRenderWindow->getWidth() >0.75 )
			//	return true;

				
			mRayScnQuery->setRay(mouseRay);
			mRayScnQuery->setSortByDistance(true);
			//mRayScnQuery->setQueryMask(currentType);   //to current type


		
			//This next chunk finds the results of the raycast
			//If the mouse is pointing at world geometry we spawn a robot at that position
		
			Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
			Ogre::RaySceneQueryResult::iterator iter = result.begin();
 

			direction = mouseRay.getDirection();
			origin = mouseRay.getOrigin();

			// Get results, create a node/entity on the position
	
			
			
			// Get results, create a node/entity on the position
			for ( iter; iter != result.end(); iter++ )
			{
				if (iter->movable && iter->movable->getName().substr(0, 5) != "tile[")
				{

					if(currentType == CATCHUP_MASK && iter->movable->getParentSceneNode()->getName().substr(0,5) == "Enemy")
					{
						mCurrentObject = iter->movable->getParentSceneNode();
						Enemy *e = findThisEnemy();
						if(e != NULL){
							e->caught = true;
							currentIsEnemy = true;
							break;
						}else
						{
							mCurrentObject = 0;
						}
						
						
					}


					if(iter->movable->getParentSceneNode()->getName().substr(0,5) == "Tower"){   //onlye pick up tower, if have time will deal with enemy
						
						//sprintf(c, "%s", iter->movable->getParentSceneNode()->getName());

						//debug->setText4(c);
						//debug->setText4(iter->movable->getParentSceneNode()->getName());
						mCurrentObject = iter->movable->getParentSceneNode();
						break;
					}

					if(iter->movable->getName().substr(0,8) == "RockWall"){
						//Ogre::Entity *ent;
						//char name[16];

						
								

						if(currentType != NONE_MASK)
						{
							BaseObject *base;
							if(currentType == TOWER_BULLET_MASK)
							{
								if(userGUI->ifSubstractMoney(towerBullet))
									userGUI->substractMoney(towerBullet);
								else
									return true;

								base = towerFactory->generate(TOWER_BULLET_MASK);
								mCurrentObject = base->getSceneNode();
								base->getEntity()->setQueryFlags(TOWER_BULLET_MASK);

								//mCurrentObject->scale(3,3,3);
							}else if(currentType == TOWER_FIRE_MASK)
							{
								/*
								sprintf(name, "Tree%d", mCount++);
								Entity *ent;
								ent = mSceneMgr->createEntity(name, "tree.mesh"); //ogre
								mCurrentObject = mSceneMgr->createSceneNode();
								mCurrentObject->attachObject(ent);
								mCurrentObject->scale(2,2,2);
								*/
						

								if(userGUI->ifSubstractMoney(towerFire))
									userGUI->substractMoney(towerFire);
								else
									return true;

								base = towerFactory->generate(TOWER_FIRE_MASK);
								mCurrentObject = base->getSceneNode();
								base->getEntity()->setQueryFlags(TOWER_FIRE_MASK);

								


								//base = obstacleFactory->generate();
								//mCurrentObject = base->getSceneNode();
								//base->getEntity()->setQueryFlags(TOWER_BULLET_MASK);
							}else if(currentType == TOWER_FROST_MASK)
							{
								/*
								sprintf(name, "Tree%d", mCount++);
								Entity *ent;
								ent = mSceneMgr->createEntity(name, "tree.mesh"); //ogre
								mCurrentObject = mSceneMgr->createSceneNode();
								mCurrentObject->attachObject(ent);
								mCurrentObject->scale(2,2,2);
								*/
						

								if(userGUI->ifSubstractMoney(towerFrost))
									userGUI->substractMoney(towerFrost);
								else
									return true;

								base = towerFactory->generate(TOWER_FROST_MASK);
								mCurrentObject = base->getSceneNode();
								base->getEntity()->setQueryFlags(TOWER_FROST_MASK);

								


								//base = obstacleFactory->generate();
								//mCurrentObject = base->getSceneNode();
								//base->getEntity()->setQueryFlags(TOWER_BULLET_MASK);
							}else if(currentType == OBSTACLE_MASK)
							{
								Obstacle *b = obstacleFactory->generate();
								b->getEntity()->setQueryFlags(OBSTACLE_MASK);
								mCurrentObject = b->getSceneNode();
							}else if(currentType == CATCHUP_MASK)
							{
								
							}
						
						}else //NONE_MASK
							break;

						

						//mCurrentObject = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::String(name) + "Node");
						//mCurrentObject->attachObject(ent);
						//Ogre::Vector3 v = getNewPosition(origin, direction, iter->distance);
						//if(currentType != OBSTACLE_MASK)
						//	v.y += uplift;
						
						if(mCurrentObject)
						{
							if(currentType == CATCHUP_MASK && findThisEnemy())
							{
								Ogre::Vector3 v = getNewPosition(origin, direction, iter->distance);
								v.y += 120;
								mCurrentObject->setPosition(v);
								currentIsEnemy = true;
								//debug->setText4("no");
							}else //tower place
							{
								Ogre::Vector3 v = iter->movable->getParentNode()->getPosition();
								v.y += 60;
								mCurrentObject->setPosition(v);
								//debug->setText4("yes");
							}				
						}
						
						break;
					}

					

					/*
					if(iter->movable->getParentSceneNode()->getName().substr(0,5) == "Tower"){   //onlye pick up tower, if have time will deal with enemy
						
						//sprintf(c, "%s", iter->movable->getParentSceneNode()->getName());

						//debug->setText4(c);
						//debug->setText4(iter->movable->getParentSceneNode()->getName());
						mCurrentObject = iter->movable->getParentSceneNode();
						break;
					}
					*/
						
				} // if
				
				
			} // for


			

		
		return true;
	}
	bool ObjectPlacement::ObjectPlaceOnMouseMoved()
	{
		if(MOWorld->waitForNextLevelClick == true)
				return true;

		if(currentIsEnemy && mCurrentObject && !findThisEnemy())
		{
				mCurrentObject = 0;
				currentIsEnemy = false;
		}

		//find the current mouse position
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();

		if(mCurrentObject)
		{
			//create a raycast straight out from the camera at the mouse's location
			Ogre::Ray mouseRay = mKnockOutCamera->mRenderCamera->getCameraToViewportRay(mousePos.d_x/mRenderWindow->getWidth(), mousePos.d_y/mRenderWindow->getHeight());
			mRayScnQuery->setRay(mouseRay);
			mRayScnQuery->setSortByDistance(true);
			direction = mouseRay.getDirection();
			origin = mouseRay.getOrigin();

			Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
			Ogre::RaySceneQueryResult::iterator iter = result.begin();
 
			//check to see if the mouse is pointing at the world and put our current object at that location
			for (iter; iter != result.end(); iter++)
			{
					if (iter->worldFragment)   //not gonna work for this project
					{
							mCurrentObject->setPosition(iter->worldFragment->singleIntersection);
							break;
					} // if
					else if(iter->movable->getName().substr(0,12) == "GroundEntity" && currentIsEnemy){

						if(mCurrentObject == 0)
								return true;

						if(currentType == CATCHUP_MASK && findThisEnemy())
						{
							Ogre::Vector3 v = getNewPosition(origin, direction, iter->distance);
							v.y += 120;
							mCurrentObject->setPosition(v);
							currentIsEnemy = true;
							break;
							//debug->setText4("no");
						}

					}
					else if(iter->movable->getName().substr(0,8) == "RockWall"){
							if(currentType != NONE_MASK)
							{

								if(mCurrentObject == 0)
									return true;

								if(currentType == CATCHUP_MASK && findThisEnemy())//hand pickup
								{
									currentIsEnemy = true;
									Ogre::Vector3 v = getNewPosition(origin, direction, iter->distance);
									v.y += 120;
									mCurrentObject->setPosition(v);
									debug->setText4("smooth");

								}else //tower place
								{
									Ogre::Vector3 v = iter->movable->getParentNode()->getPosition();
									v.y += 60;
									mCurrentObject->setPosition(v);
								}

								/*
								Ogre::Real r= iter->distance;
								//Ogre::Vector3 v = getNewPosition(origin, direction, iter->distance);
								Ogre::Vector3 v = iter->movable->getParentNode()->getPosition();
								//if(currentType != OBSTACLE_MASK)
								v.y += 60;
								mCurrentObject->setPosition(v);
								*/
							}	
							break;
					}

					if(iter->movable->getName().substr(0,13) == "goundEntity"){
						
					}
				

			}	
		
		
		}
 
		



		return true;
	}
	bool ObjectPlacement::ObjectPlaceOnMouseReleased()
	{
		if(MOWorld->waitForNextLevelClick == true)
				return true;

		if(mCurrentObject)
		{
			if(currentType == OBSTACLE_MASK)
				pathManager->pathGenerater->writeInBitMap(mCurrentObject->getPosition());
			else if(currentType == CATCHUP_MASK)
			{
				Enemy *e = findThisEnemy();
				if(e != NULL)
				{
					e->caught = false;
					e->nearlyDie = true;
					e->killed = true;
					mCurrentObject = 0;
					currentIsEnemy = false;
					e->fall = true;
				}
			
			}
		}


		return true;
	}


	Ogre::Vector3 ObjectPlacement::getNewPosition(Ogre::Vector3 origin, Ogre::Vector3 direction, Ogre::Real distance)
	{
		Ogre::Real k = sqrt(distance*distance/(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z));

		return Ogre::Vector3(origin.x + direction.x * k, origin.y + direction.y * k, origin.z + direction.z * k);

	}

}