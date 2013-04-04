#pragma once
#include "Common.h"
#include "BaseTower.h"


namespace KnockOut
{

	using namespace Ogre;

	class towerC : public BaseTower
	{
		
	public:
		towerC(int ID): BaseTower(ID)
		{
			//setUp();
		}
		~towerC();

		virtual void setUp();
		void update(float time);
		void destroy();

		bool die;
		
		Vector3 targetPosition;
		Vector3 currentDirection;
		Vector3 currentPosition;

		



	protected:
		virtual std::string appropriateName(NAME_TYPE type);
		ParticleSystem* ps;
	};
}

