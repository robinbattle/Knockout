#include "Obstacle.h"



namespace KnockOut
{

	void Obstacle::setUp()
	{
		
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "MyObstacle.mesh");
		entity->setQueryFlags(OBSTACLE_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(0.3,0.3,0.3);

		moveCD = 0.8f;
		allowMoving = false;
		die = false;
	}

	
	std::string Obstacle::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "ObstacleScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "ObstacleEntity" + convertInt(ID);
		
		return NULL;
	}



	void Obstacle::update(float time)
	{
		
		if(die)
			return;


		moveCD -= time;
		if(moveCD < 0)
		{
			moveCD = 0.8f;
			allowMoving = true;
		}
		//char c[80];

		if(ownPathPositionList.empty())
			allowMoving = false;

		if(allowMoving)
		{
			Ogre::Vector2 v2= *ownPathPositionList.begin();
			sceneNode->setPosition(Ogre::Vector3(v2.x * 100 - 750, 70, v2.y * 100 - 750));
			
			
			ownPathPositionList.pop_front();
			
			//char c[80];
			//sprintf(c, "to (%f, %f, %f)", v2.x * 100, 40, v2.y * 100);
			//debug->setText5(c);

			allowMoving = false;
		}
		
	}
}

