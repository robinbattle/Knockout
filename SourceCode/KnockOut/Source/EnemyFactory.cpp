#include "EnemyFactory.h"
#include "Enemy.h"
#include "EnemyDragon.h"
#include "EnemyTroll.h"
#include "EnemyBoss1.h"
#include "EnemyBoss2.h"
//#include "ObjectPlacement.h"
namespace KnockOut
{
	//InputHandler *ih = InputHandler::getSingletonPtr();
	//ObjectPlacement *enemyOB = ObjectPlacement::getSingletonPtr();

	EnemyFactory::EnemyFactory()
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		userGUI = UserGUI::getSingletonPtr();
		IDCounter = 0;
		debug = DebugOverlay::getSingletonPtr();
		mRotationSpeed = 1.0;
		mCamera = KnockOutCamera::getSingletonPtr()->mRenderCamera;
		
		hit = false;
	}


	Enemy* EnemyFactory::generate(int type)
	{
		
		Enemy *base;
		if(type == 1){
			base = new Enemy(IDCounter);
			base->setUp();
			
			base->type = 1;
		}else if(type == 2){
			base = new EnemyTroll(IDCounter);
			base->setUp();
			
			base->type = 2;
			base->getSceneNode()->yaw(Degree(90));
		}else if(type == 3){
			base = new EnemyDragon(IDCounter);
			base->setUp();
			
			base->type = 3;
		}else if(type == 4){
			base = new EnemyBoss1(IDCounter);
			base->setUp();
			
			base->type = 4;
		}else if(type == 5){
			base = new EnemyBoss2(IDCounter);
			base->setUp();
			
			base->type = 5;
		}


		
		
		
		//debug->setText("entity: " + entity->getName() + ", Node: " + sceneNode->getName() );
		//enemyList.push_back(base);

		EnemyIterator itr = enemyList.insert(enemyList.end(), base);
		enemyIndex.insert(std::make_pair(base->getName(), itr));

		

		//base->getSceneNode()->yaw(Ogre::Degree(90));

		//debug->setText("size is " + convertInt(enemyList.size()));

		//debug->setText(get(appropriateName(ENTITY).substr(8))->getName());


		IDCounter++;
	
		return  base;
	}

	Enemy* EnemyFactory::get(const std::string &name){
		

		EnemyIndexIterator bi = enemyIndex.find(name);
		if (bi == enemyIndex.end())
			return NULL;

		return *bi->second;
		
		
	}

	void EnemyFactory::update( float time )
	{
		
		
		Enemy* b;
		std::string name;

		for (EnemyIterator ei = enemyList.begin(); ei != enemyList.end(); ){
			b = *ei;
			//name = b->getName();
			//sillyRotation(time, b->getSceneNode());

			//if(hit)
			//	sillyHitCamera(time, b->getSceneNode());

			b->update(time);
			ei++;

			if(b->nearlyDie)
			{
				//update score panel
				if(b->killed)
					userGUI->addMoney(b->worthMoney);

				enemyDeadList.push_back(b);
				enemyList.remove(b);

				
			}
			/*
			if(b->die == true)
			{
				enemyList.remove(b);
				delete b;

			}
			*/
			 
		}

		for (EnemyDeadIterator ei = enemyDeadList.begin(); ei != enemyDeadList.end(); ){
			b = *ei;
			b->update(time);
			ei++;

			if(b->getSceneNode()->getPosition().y > 0)
			{
				b->getSceneNode()->translate(0, -3, 0);
			}

			if(b->die == true)
			{
				//if(enemyOB->mCurrentObject == b->getSceneNode())
				//{
				//	enemyOB->mCurrentObject = 0;
				//}
				
				enemyDeadList.remove(b);
				delete b;
				b = 0; 
			}
		}



		//resetPath();
		//enemyList.clear();
	}

	void EnemyFactory::cleanUp(){
		for (EnemyIterator ei = enemyList.begin(); ei != enemyList.end(); ){
			Enemy* enemy = *ei;
			enemy->nearlyDie = true;
			ei++;
		}
	
	}


	void EnemyFactory::resetPath()
	{
		Ogre::Vector2 v2;
		Enemy *e;

		

		for (EnemyIterator ei = enemyList.begin(); ei != enemyList.end(); ){
			e = *ei;

			//Vector2 current = *(e->ownPathPositionList.);
			Ogre::Vector2 v3= *e->ownPathPositionList.begin();
			//char c[90];
			//sprintf(c, "(%f, %f)", current.x, current.y);
			//debug->setText5(c);
			//pathManager->pathGenerater->getPathMap(current, Vector2(15,15));

			//e->ownPathPositionList.clear();
			//e->ownPathPositionList.push_back(current);

			//make deep copy of path list
			/*
			for (PathGenerater::PositionIterator p = pathManager->pathGenerater->positionList.begin(); p != pathManager->pathGenerater->positionList.end();)
			{
				v2 = *p;
				e->ownPathPositionList.push_back(v2);
				p++;
			}
			*/
			

		
			ei++;
		}
	
	
	
	}



	void EnemyFactory::sillyRotation(float time, Ogre::SceneNode *sceneNode)
	{
	
		Ogre::Radian degrees = Ogre::Radian(time * mRotationSpeed);
		Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);
	
		sceneNode->setOrientation (sceneNode->getOrientation() * tmp);
	
	}


	void EnemyFactory::sillyHitCamera(float time, Ogre::SceneNode *sceneNode)
	{
		Ogre::Vector3 v = calculateDirection(mCamera->getPosition(), sceneNode->getPosition());
		sceneNode->translate(-v  * time);  
		char c[80];
		sprintf(c, "true and V is %f, %f, %f", v.x, v.y, v.z);
		debug->setText(c);
	}


	Ogre::Vector3 EnemyFactory::calculateDirection(Ogre::Vector3 cam, Ogre::Vector3 object)
	{
		return Ogre::Vector3(object.x - cam.x, object.y - cam.y, object.z - cam.z);
	
	}
	


	 bool EnemyFactory::destroy(const std::string &name){
		return true;
	}


	

}