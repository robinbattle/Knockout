#pragma once
#include "Common.h"
#include "BaseObject.h"


namespace KnockOut
{

	using namespace Ogre;

	class Obstacle : public BaseObject
	{
		
	public:
		Obstacle(int ID): BaseObject(ID)
		{

		}


		virtual void setUp();
		void update(float time);
		bool die;
		float moveCD;
		bool allowMoving;

	protected:
		std::string appropriateName(NAME_TYPE type);
	};
}

