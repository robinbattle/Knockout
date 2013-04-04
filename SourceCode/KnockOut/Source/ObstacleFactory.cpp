#include "ObstacleFactory.h"
#include "Obstacle.h"


namespace KnockOut
{
	//InputHandler *ih = InputHandler::getSingletonPtr();

	ObstacleFactory::ObstacleFactory()
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		IDCounter = 0;
		debug = DebugOverlay::getSingletonPtr();
		mRotationSpeed = 1.0;
		mCamera = KnockOutCamera::getSingletonPtr()->mRenderCamera;
		hit = false;
	}


	Obstacle* ObstacleFactory::generate()
	{
		
		
		
		
		Obstacle *base = new Obstacle(IDCounter);
		base->setUp();
		//debug->setText("entity: " + entity->getName() + ", Node: " + sceneNode->getName() );
		//ObstacleList.push_back(base);

		ObstacleIterator itr = ObstacleList.insert(ObstacleList.end(), base);
		ObstacleIndex.insert(std::make_pair(base->getName(), itr));

		base->getSceneNode()->scale(3,3,3);
		//debug->setText("size is " + convertInt(ObstacleList.size()));

		//debug->setText(get(appropriateName(ENTITY).substr(8))->getName());


		IDCounter++;
	
		return  base;
	}

	Obstacle* ObstacleFactory::get(const std::string &name){
		

		ObstacleIndexIterator bi = ObstacleIndex.find(name);
		if (bi == ObstacleIndex.end())
			return NULL;

		return *bi->second;
		
		
	}

	void ObstacleFactory::cleanUp(){
		Obstacle* b;
		for (ObstacleIterator ei = ObstacleList.begin(); ei != ObstacleList.end(); )
		{
			b = *ei;
			b->die = true;
			ei++;
		
		}
	
	}


	void ObstacleFactory::update( float time )
	{
		
		
		Obstacle* b;
		std::string name;

		for (ObstacleIterator ei = ObstacleList.begin(); ei != ObstacleList.end(); ){
			b = *ei;
			b->update(time);
			ei++;
			if(b->die)
			{
				delete b;
				b = 0;
			}


			
			name = b->getName();
			sillyRotation(time, b->getSceneNode());

			if(hit)
				sillyHitCamera(time, b->getSceneNode());

			
		}


		if(!hit)
			debug->setText("false");

		//resetPath();
		//ObstacleList.clear();
	}

	void ObstacleFactory::resetPath()
	{
		Ogre::Vector2 v2;
		Obstacle *e;

		

		for (ObstacleIterator ei = ObstacleList.begin(); ei != ObstacleList.end(); ){
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



	void ObstacleFactory::sillyRotation(float time, Ogre::SceneNode *sceneNode)
	{
	
		Ogre::Radian degrees = Ogre::Radian(time * mRotationSpeed);
		Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);
	
		sceneNode->setOrientation (sceneNode->getOrientation() * tmp);
	
	}


	void ObstacleFactory::sillyHitCamera(float time, Ogre::SceneNode *sceneNode)
	{
		Ogre::Vector3 v = calculateDirection(mCamera->getPosition(), sceneNode->getPosition());
		sceneNode->translate(-v  * time);  
		char c[80];
		sprintf(c, "true and V is %f, %f, %f", v.x, v.y, v.z);
		debug->setText(c);
	}


	Ogre::Vector3 ObstacleFactory::calculateDirection(Ogre::Vector3 cam, Ogre::Vector3 object)
	{
		return Ogre::Vector3(object.x - cam.x, object.y - cam.y, object.z - cam.z);
	
	}
	


	 bool ObstacleFactory::destroy(const std::string &name){
		return true;
	}


	

}