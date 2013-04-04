#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H


#include "Ogre.h"
#include "World.h"
#include "EnemyFactory.h"
#include "PlayerFactory.h"
#include "WallFactory.h"
#include "Common.h"
#include "TowerFactory.h"
#include "BulletFactory.h"
namespace Ogre {
    class SceneNode;
    class SceneManager;
}


namespace KnockOut
{


	class CollisionManager : public SingletonT<CollisionManager>
	{
		SINGLETON_DEFINE(CollisionManager)

	public: CollisionManager();

			//update
			void update(float time);
			
			float playerScore;

	protected:
			Ogre::SceneManager *mSceneManager;
			Ogre::AxisAlignedBox pBox;
			Ogre::AxisAlignedBox qBox;
			
			WallFactory *wallFactory;
			PlayerFactory *playerFactory;
			BulletFactory *bulletFactory;
			TowerFactory *towerFactory;
			EnemyFactory *enemyFactory;
			
			Player *player;
			Wall *wall;
			BaseTower *tower;
			Bullet *bullet;
			Enemy *enemy;

			DebugOverlay *debug;

	private:
			
			void detectPlayerValidStep();
			void detectBulletVsEnemy();
			void detectFireTowerVsEnemy();
			void detectEnemyVsHome();

			bool calculateDistanceSquare(Vector3 p, Vector3 q);

	};

}

#endif