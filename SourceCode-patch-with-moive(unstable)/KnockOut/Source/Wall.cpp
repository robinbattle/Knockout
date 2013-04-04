#include "Wall.h"



namespace KnockOut
{

	void Wall::setUp()
	{
		
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "mywall.mesh");
		entity->setQueryFlags(NONE_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(2,2,2);

		entity->setQueryFlags(OBSTACLE_MASK);
		die = false;
	}


	Wall::~Wall(){
	
		mSceneManager->destroyEntity(appropriateName(ENTITY));
		mSceneManager->destroySceneNode(appropriateName(SCENE_NODE));
	
	}
	
	std::string Wall::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "RockWallScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "RockWallEntity" + convertInt(ID);
		
		return NULL;
	}



	void Wall::update(float time)
	{
		if(die)
			return;
		
		
	}
}

