#pragma once
#include "Common.h"
#include "BaseTower.h"


namespace KnockOut
{

	using namespace Ogre;

	class TowerA : public BaseTower
	{
		
	public:
		TowerA(int ID): BaseTower(ID)
		{
			//setUp();
		}
		~TowerA();

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

