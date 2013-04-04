#pragma once
#include "Common.h"
#include "BaseObject.h"


namespace KnockOut
{

	using namespace Ogre;

	class Wall : public BaseObject
	{
		
	public:
		Wall(int ID): BaseObject(ID)
		{

		}

		~Wall();



		bool die;
		virtual void setUp();
		void update(float time);


	protected:
		std::string appropriateName(NAME_TYPE type);
	};
}

