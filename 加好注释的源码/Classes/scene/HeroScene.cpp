/***********************************************

���������˵���ɫѡ������Ľ�ɫ��ť����תҳ�棬
��Ҫ���ܰ�����Ч������ť�������˵��ͼ���ҳ�����ת

***********************************************/

#include "HeroScene.h"
#include "data\Global.h"
#include "SceneM.h"
#include "data\DataM.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);

void HeroScene::onExit()
{
	Layer::onExit();
	removeAllChildrenWithCleanup(true);
}

void HeroScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();

	//����Ч
	unsigned int randNum = rand() % 6;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("skillScene%d.mp3", randNum)->getCString(), false);

}

bool HeroScene::init()
{
	Sprite *heroBG = Sprite::create("LevelBackground.jpg");
	heroBG->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);	
	this->addChild(heroBG, 0);

	Sprite *threeTanks = Sprite::create("ThreeTanks.png");
	threeTanks->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(threeTanks, 2);
	
	//tag Ϊ0
	bigCircle0 = Sprite::create("BigCircle.png");
	bigCircle0->setPosition(216, 417);
	this->addChild(bigCircle0, 1, 0);

	//tag Ϊ1
	bigCircle1 = Sprite::create("FullBigCircle.png");
	bigCircle1->setPosition(512, 417);
	this->addChild(bigCircle1, 1, 1);

	//tag Ϊ2
	bigCircle2 = Sprite::create("FullBigCircle.png");
	bigCircle2->setPosition(815, 417);
	this->addChild(bigCircle2, 1, 2);

	return true;
}

void HeroScene::update(float dt)
{
	//ԲȦת��
	Sprite *selectedBigCircle = static_cast<Sprite *>(getChildByTag(heroOption));
	selectedBigCircle->setRotation(selectedBigCircle->getRotation() - 90 * dt);

	if (g_keyRight || g_keyLeft)
	{
		int move; //�ƶ�����
		if (g_keyRight)
		{
			move = 1;
		}
		else
		{
			move = -1;
		}
		g_keyRight = false;
		g_keyLeft = false;
		Sprite *currentBigCircle = static_cast<Sprite *>(getChildByTag(heroOption));
		currentBigCircle->setTexture("FullBigCircle.png");
		currentBigCircle->setRotation(0); //ԲȦ��λ
		heroOption = heroOption + move;
		if (heroOption < 0)
		{
			heroOption += 3;
		}
		heroOption = heroOption % 3;
		Sprite *nextOverBigCircle = static_cast<Sprite *>(getChildByTag(heroOption));
		nextOverBigCircle->setTexture("BigCircle.png");
	}
	if (g_keyStart)
	{
		g_keyStart = false;
		this->unscheduleUpdate();
		auto sceneM = SceneM::getInstance();
		DataM::getInstance()->setHType((HeroType)heroOption);
		sceneM->changeScene(kSkillScene, kTransitionCrossFade);
	}
	if (g_keySelect)
	{
		g_keySelect = false;
		this->unscheduleUpdate();
		SceneM::getInstance()->changeScene(kMenuScene, kTransitionZoomFlipAngular_LEFT_OVER);
	}

	//����Ч
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		unsigned int randNum = rand() % 6;
		SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("skillScene%d.mp3", randNum)->getCString(), false);
	}
}