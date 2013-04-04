#include "CollisionManager.h"

#include "Ogre.h"


#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"

using namespace Ogre;


namespace KnockOut
{
	int i = 0;

	//CollisionManager::CollisionManager(Ogre::SceneManager *sceneManager):mSceneManager(sceneManager)
	CollisionManager::CollisionManager()
	{
		playerScore = 0;
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		wallFactory = WallFactory::getSingletonPtr();
		playerFactory = PlayerFactory::getSingletonPtr();
		debug = DebugOverlay::getSingletonPtr();
		bulletFactory = BulletFactory::getSingletonPtr();
		towerFactory = TowerFactory::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();

	}



	void CollisionManager::update(float time){
		detectPlayerValidStep();
		detectBulletVsEnemy();
		//detectFireTowerVsEnemy();
		//detectEnemyVsHome();
	}

	void CollisionManager::detectEnemyVsHome()
	{
	
		for (EnemyFactory::EnemyIterator e = enemyFactory->enemyList.begin(); e != enemyFactory->enemyList.end(); e++ ){
			enemy = *e;
			if(enemy->nearlyDie)
				continue;

			if(enemy->reachHome)
				enemy->nearlyDie = true; 

		}


	
	}

	void CollisionManager::detectFireTowerVsEnemy()
	{
		for (EnemyFactory::EnemyIterator e = enemyFactory->enemyList.begin(); e != enemyFactory->enemyList.end(); e++ ){
			enemy = *e;
			if(enemy->nearlyDie)
				continue;

			for (TowerFactory::TowerAIterator e = towerFactory->towerAList.begin(); e != towerFactory->towerAList.end(); e++ )
			{
				tower = *e;
				if(tower->die)
					continue;

				if(calculateDistanceSquare(tower->getSceneNode()->getPosition(), enemy->getSceneNode()->getPosition())) //in range
				{
					//W
				}
		
		
			}

		}


		
	
	}


	bool CollisionManager::calculateDistanceSquare(Vector3 p, Vector3 q)
	{
		Vector3 distance = p - q;
		
		if(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z < 10000)
			return true;
		else 
			return false;
	
	}


	void CollisionManager::detectBulletVsEnemy(){
		for (EnemyFactory::EnemyIterator e = enemyFactory->enemyList.begin(); e != enemyFactory->enemyList.end(); e++ ){
			enemy = *e;
			if(enemy->nearlyDie)
				continue;
			pBox = enemy->getEntity()->getWorldBoundingBox();
			for (BulletFactory::BulletIterator b = bulletFactory->bulletList.begin(); b != bulletFactory->bulletList.end(); b++ ){

				bullet = *b;
				qBox = bullet->getEntity()->getWorldBoundingBox();


				if(pBox.intersects(qBox)) //hit on
				{
					bullet->currentTarget = 0;
					bullet->die = true;

					enemy->lifeValue -= 20;      //substract life
					if(enemy->lifeValue <= 0){   
						enemy->nearlyDie = true; //die animation alarm
						enemy->killed = true;
					}
					
					

					//break;
				}
			}
		}
		
	
	}


	void CollisionManager::detectPlayerValidStep(){
		
		player = playerFactory->myPlayer;

		if (player == NULL)
			return;

		//char c[60];
		//char d[60];
		
		pBox = player->getEntity()->getWorldBoundingBox(); //Player
		for (WallFactory::WallIterator i = wallFactory->WallList.begin(); i != wallFactory->WallList.end(); i++ ){
			wall = *i;
			Vector3 pP = player->getSceneNode()->getPosition();
			//sprintf(c, "player p: %f, %f, %f", pP.x, pP.y, pP.z);
			//debug->setText4(c);

			Vector3 pQ = player->getSceneNode()->getPosition();
			//sprintf(d, "wall p: %f, %f, %f", pQ.x, pQ.y, pQ.z);
			//debug->setText5(d);

			qBox = wall->getEntity()->getWorldBoundingBox(); //Wall
			if(pBox.intersects(qBox)){
				//reset to last valid position
				player->getSceneNode()->setPosition(playerFactory->myPlayer->lastValidStep);
				//debug->setText4("detect");
			}else
			{  //store last valid position
				player->lastValidStep = playerFactory->myPlayer->getSceneNode()->getPosition();
				//debug->setText5("fine");
			}
		
		}
	
	
	}

}