#include "World.h"
#include "Ogre.h"
#include "OgreMath.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "Constants.h"
#include "OgreSphere.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "EnemyFactory.h"
#include "BaseObject.h"
#include "TowerFactory.h"
#include "BulletFactory.h"

#include "PlayerFactory.h"
#include "EnemyFactory.h"
#include "BaseObject.h"
#include "TowerFactory.h"
#include "BulletFactory.h"
#include "ObstacleFactory.h"
#include "WallFactory.h"
#include "PathManager.h"
#include "AIManager.h"
#include "UserGUI.h"
#include "InputHandler.h"
//#include "UtilsOgreDshow.h"
using namespace Ogre;
using namespace std;

namespace KnockOut{

	//some global vars
	TextAreaOverlayElement *textArea;
	OverlayManager *olm;
	OverlayContainer *panel ;
	Overlay *overlay;
	int existNo = 8;

	PlayerFactory *playerFactory;
		
	BulletFactory *bulletFactory ;
	EnemyFactory *enemyFactory;
	ObstacleFactory *obstacleFactory;
	TowerFactory *towerFactory;
	WallFactory *wallFactory ;
	PathManager *pathManager;
	AIManager *aiManager;
	UserGUI *userGUI;
	InputHandler *inputHandler;

	//OgreUtils::DirectShowMovieTexture* dshowMovieTextureSystem;
	Ogre::MaterialPtr mat;
	Ogre::TextureUnitState* tex;

	KnockOutWorld::KnockOutWorld()

	{
		debug = DebugOverlay::getSingletonPtr();
		mWindow = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		playerFactory = PlayerFactory::getSingletonPtr();
		bulletFactory = BulletFactory::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		obstacleFactory = ObstacleFactory::getSingletonPtr();
		towerFactory = TowerFactory::getSingletonPtr();
		wallFactory = WallFactory::getSingletonPtr();
		pathManager = PathManager::getSingletonPtr();
		aiManager = AIManager::getSingletonPtr();
		userGUI = UserGUI::getSingletonPtr();
		inputHandler = InputHandler::getSingletonPtr();
		ifStart = false;
		win = false;
		nextLevelClick = false;
		waitForNextLevelClick = false;
		
		//SetupDefaultGame();
	}

	void KnockOutWorld::cleanUpAll(){
		inputHandler->objectPlacement->mCurrentObject = 0;
		playerFactory->cleanUp();
		bulletFactory->cleanUp();
		enemyFactory->cleanUp();
		obstacleFactory->cleanUp();
		towerFactory->cleanUp();
		wallFactory->cleanUp();
		delete playerFactory->myPlayer;
		playerFactory->myPlayer = NULL;
		if(pathManager->pathGenerater->pathNodeCount > 0)
			pathManager->pathGenerater->freeOldPathNode();
		
	}

	void KnockOutWorld::SetupDefaultGame()
	{
		Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
		mSceneManager->setAmbientLight(ColourValue(1,1,1));
	    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
		Ogre::Entity* entGround = mSceneManager->createEntity("GroundEntity", "ground");
		SceneNode* myGound = mSceneManager->getRootSceneNode()->createChildSceneNode();
		myGound->attachObject(entGround);

		//entGround->setMaterialName("test2");
		entGround->setMaterialName("Examples/Rockwall");
		entGround->setCastShadows(false);
		
		//mSceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);
		
		
		
		ParticleSystem* ps;
        ps = mSceneManager->createParticleSystem("Fireworks", "PEExamples/blast");

		
		pathManager->readMap(1);

		SceneNode* sn = mSceneManager->getRootSceneNode()->createChildSceneNode("homeSceneNode1");
		Ogre::Entity* homeEntity = mSceneManager->createEntity("homeEntity1", "slycastle2.mesh");
		sn->setPosition(Ogre::Vector3(750, 0, 600));
		sn->attachObject(homeEntity);
		sn->scale(30, 30, 30); 
		sn->yaw(Degree(-90));
		homeEntity->setQueryFlags(NONE_MASK);
		homeText = new MovableText(convertInt(homeHealth), convertInt(homeHealth), "StarWars"); 

		//sn->attachObject(ps);
		sn->attachObject(homeText);
		homeText->setLocalTranslation(Vector3(0,600,0));

		SceneNode* sn2 = mSceneManager->getRootSceneNode()->createChildSceneNode("EnemHomeSceneNode1");
		Ogre::Entity* EnemyHomeEntity = mSceneManager->createEntity("EnemHomeEntity1", "cano1.mesh");
		sn2->setPosition(Ogre::Vector3(-820, 0, -820));
		sn2->attachObject(EnemyHomeEntity); 
		sn2->scale(30, 30, 30);
		homeEntity->setQueryFlags(NONE_MASK);

		

		
		SceneNode* middle2 = mSceneManager->getRootSceneNode()->createChildSceneNode("hahaha");
		Ogre::Entity* middle = mSceneManager->createEntity("littlegirl", "littlegirl.mesh");

		middle2->attachObject(middle);
		middle2->translate(Ogre::Vector3(0,50,0));

		middle2->attachObject(ps);
		ps->getWorldBoundingBox();
		ifStart = true;


		hasDefault = true;
		playerFactory->generate();


		Ogre::Light* spotLight = mSceneManager->createLight("spotLight");
		spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight->setDiffuseColour(0, 0, 1.0);
		spotLight->setSpecularColour(0, 0, 1.0);
 
		spotLight->setDirection(0, -1, 0);
		spotLight->setPosition(Ogre::Vector3(-1500, 300, -1500));

		Ogre::Light* spotLight2 = mSceneManager->createLight("spotLight2");
		spotLight2->setType(Ogre::Light::LT_SPOTLIGHT);
		spotLight2->setDiffuseColour(0, 0, 1.0);
		spotLight2->setSpecularColour(0, 0, 1.0);
 
		spotLight2->setDirection(0, -1, 0);
		spotLight2->setPosition(Ogre::Vector3(1500, 300, 1500));
 
		spotLight2->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

		Ogre::Light* directionalLight = mSceneManager->createLight("directionalLight");
		directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
		directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, .25));
		directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, .25));
		directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); 

		

		ParticleSystem* ps2;
		ps2 = mSceneManager->createParticleSystem("penta", "PEExamples/pentagram");
		middle2->attachObject(ps2);
		//TowerFactory *tt = TowerFactory::getSingletonPtr();
		//tt->generate();

		//SetupLevel1();
		SetupLevel1();
		//enemyFactory->generate(2);
		//enemyFactory->generate(3);
	}



	void KnockOutWorld::SetupLevel1()
	{
		pathManager->readMap(1);
		aiManager->setLevel(1, 20);
		aiManager->generateEnemy = true;
		userGUI->addMoney(700);
		homeHealth = 500;
	}
	void KnockOutWorld::SetupLevel2()
	{
		pathManager->readMap(2);
		aiManager->setLevel(2, 30);
		aiManager->generateEnemy = true;
		userGUI->addMoney(1000);
	}
	void KnockOutWorld::SetupLevel3()
	{
		pathManager->readMap(3);
		aiManager->setLevel(3, 40);
		aiManager->generateEnemy = true;
		userGUI->addMoney(1200);
	}


	String KnockOutWorld::convertInt(int n)
	{
		StringStream ss;
		ss << n;
		return ss.str();
	}

	void KnockOutWorld::Setup()
	{

	}

	void KnockOutWorld::newGame(){
		cleanUpAll();
		win = false;
		userGUI->lose = false;
		userGUI->lifeValue = 1000;
		userGUI->resetHealthBar(0);
		userGUI->setMoney(0);
		aiManager->levelFinished = false;
		nextLevelClick = false;
		waitForNextLevelClick = false;

		SetupLevel1();
		
		inputHandler->next_level->hide();
	}


	void 
	KnockOutWorld::Think(float time)
	{
		//dshowMovieTextureSystem->updateMovieTexture();

		//if lose
		if(userGUI->lose){
			inputHandler->next_level->hide();
			userGUI->loseP->show();
			cleanUpAll();
			
		}
		else
			userGUI->loseP->hide();

		//if win
		if(win && showStatus)
		{
			cleanUpAll();
			showStatus = false;
			userGUI->winP->show();
			inputHandler->next_level->show();
		}


		if(aiManager->levelFinished && !nextLevelClick)
		{
			if(!userGUI->lose)
				inputHandler->next_level->show();
			waitForNextLevelClick = true;
		}


		//if make any level through
		if(aiManager->levelFinished && nextLevelClick)
		{
			cleanUpAll();
			
			int currentLevel = aiManager->getLevel();

			if(currentLevel == 1)
			{
				SetupLevel2();
				
				//debug->setText4("win");
			}
			else if(currentLevel == 2)
			{
				SetupLevel3();
			}else if (currentLevel == 3)
			{
				showStatus = true;
				win = true;
				inputHandler->next_level->hide();
				return;
			}
				
			nextLevelClick = false;
			aiManager->levelFinished = false;
			waitForNextLevelClick = false;;
		}
	
	
	}

	void
	KnockOutWorld::DoSometing(){ //this one is only used to crash program, so carefully used it
		mSceneManager->setAmbientLight(ColourValue(1,1,1));
		Entity* ball = mSceneManager->createEntity("cube2", "MyCube.mesh");
		SceneNode *mBall = mSceneManager->getRootSceneNode()->createChildSceneNode();
		mBall->attachObject(ball);
		mBall->setPosition(50,50,0);
		ball = mSceneManager->createEntity("cube2", "MyCube.mesh"); //create same thing twice

	}
}


