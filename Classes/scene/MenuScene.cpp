/***********************************************

��������Ϸ���˵���ҳ�棬
��Ҫ���ܰ�����������ҳ�����ת����Ч�Ĺ���

***********************************************/

#include "MenuScene.h"
#include "data\Global.h"
#include "SceneM.h"
#include "data\ChineseFonts.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;

void MenuScene::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
}

void MenuScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();

	//����Ч
	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


}

//�Լ��̰����������ķ�Ӧ
bool MenuScene::init()
{
	background = Sprite::create("HomePage0.jpg");
	background->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(background, 0);
	
	gear = Sprite::create("gear.png");
	gear->setPosition(Vec2(179, 380));
	this->addChild(gear);

	option = 0;

	return true;
}

void MenuScene::update(float dt)
{
	gear->setRotation(gear->getRotation() - 180 * dt);
	if (g_keyDown)
	{
		g_keyDown = false;
		option = (option + 1) % 3;
		gear->setPositionY(380 - 70 * option);
		String *bgName = String::createWithFormat("HomePage%d.jpg", option);
		background->setTexture(bgName->getCString());
	}
	if (g_keyUp)
	{
		g_keyUp = false;
		if (--option < 0)
		{
			option += 3;
		}
		gear->setPositionY(380 - 70 * option);
		String *bgName = String::createWithFormat("HomePage%d.jpg", option);
		background->setTexture(bgName->getCString());
	}
	if (g_keyStart)
	{
		g_keyStart = false;
		this->unscheduleUpdate();
		auto sceneM = SceneM::getInstance();
		switch (option)
		{
		case start:
			sceneM->changeScene(kLevelScene, kTransitionFade);
			break;
		case hero:
			sceneM->changeScene(kHeroScene, kTransitionZoomFlipAngular_RIGHT_OVER);
			break;
		case success:
			sceneM->changeScene(kSuccessScene, kTransitionPageTurn_false);
			break;
		default:
			break;
		}
	}
}
