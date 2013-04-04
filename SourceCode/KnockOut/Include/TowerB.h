#pragma once
#include "Common.h"
#include "BaseTower.h"


namespace KnockOut
{

	using namespace Ogre;

	class TowerB : public BaseTower
	{
		
	public:
		TowerB(int ID): BaseTower(ID)
		{
			//setUp();
		}
		~TowerB();

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

