#include "LevelScene.h"
#include "data/Global.h"
#include "SceneM.h"
#include "data/DataM.h"
#include "ui\UIScale9Sprite.h"
#include "data\ChineseFonts.h"
using namespace std;
using namespace ui;

void LevelScene::onExit()
{
	Layer::onExit();
	removeAllChildrenWithCleanup(true);
}

void LevelScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();
}

bool LevelScene::init()
{
	//�ؿ�_id��ʼ��
	_id = 1;
	isCustom = false;

	auto dataM = DataM::getInstance();
	//����ͼ
	Sprite *levelBG = Sprite::create("LevelBackground.jpg");
	levelBG->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(levelBG, 0);
	
	//15��ͼ��
	//ע�⣬i=0 j=0Ϊ��һ��
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			Sprite *rectBG = Sprite::create("Normal.png");  //����С���鱳��
			rectBG->setPosition(Vec2(166 + 173 * j, 557 - 173 * i));
			this->addChild(rectBG, 1);

			//�ؿ����
			String *levelNumName = String::createWithFormat("Level%d.png", i * 5 + j + 1);
			Sprite *levelNum = Sprite::create(levelNumName->getCString());
			levelNum->setPosition(Vec2(166 + 173 * j, 544 - 173 * i));
			this->addChild(levelNum, 1);

			if (5 * i + j + 1 > dataM->maxLevelCanPlayed)
			{
				Sprite *shadow = Sprite::create("Shadow.png");
				shadow->setPosition(Vec2(166 + 173 * j, 557 - 173 * i));
				this->addChild(shadow, 2);
			}
			
			if (5 * i + j + 1 < dataM->maxLevelCanPlayed || 5 * i + j + 1 == 15 && dataM->levelMaxScoreArray[15] != 0)
			{
				//��������
				String *name = String::createWithFormat("Star%d.png", dataM->levelMaxScoreArray[5 * i + j + 1]); //�˴���1����Ϊarray�е�һ��������0���ڶ��������ǵ�һ�ص������� 
				Sprite *star = Sprite::create(name->getCString());
				star->setPosition(Vec2(166 + 173 * j, 630 - 173 * i));
				this->addChild(star, 1);
			}
		}
	}

	//ѡ��
	selectedRect = Sprite::create("SelectedRect.png");
	selectedRect->setPosition(Vec2(166, 557));
	this->addChild(selectedRect, 3, "selectedRect");
	selectedRect->setVisible(!isCustom);

	//�Զ���
	//�����Ժ���д,�˴�ûд�� ע�⣡
	isCanCustom = true;
	//��������
	auto customBG = ui::Scale9Sprite::create("Normal.png");
	customBG->setContentSize(Size(350, 70));
	customBG->setPosition(SCREEN_WIDTH / 2, 80);
	this->addChild(customBG, 1);

	//ѡ���
	auto customSelectedRect = ui::Scale9Sprite::create("SelectedRect.png");
	customSelectedRect->setContentSize(Size(390, 110));
	customSelectedRect->setPosition(SCREEN_WIDTH / 2, 80);
	this->addChild(customSelectedRect, 1, "customSelectedRect");
	customSelectedRect->setVisible(isCustom);

	//����
	Label *customString = Label::create(FontToUTF8("�Զ�����Ϸ"), "Simple.ttf", 50);
	customString->setPosition(SCREEN_WIDTH / 2, 80);
	this->addChild(customString);
	
	//��Ӱ��
	auto customShadowBG = ui::Scale9Sprite::create("Shadow.png");
	customShadowBG->setContentSize(Size(350, 70));
	customShadowBG->setPosition(SCREEN_WIDTH / 2, 80);
	this->addChild(customShadowBG, 1);

	customShadowBG->setVisible(!isCanCustom);

	return true;
}

void LevelScene::update(float dt)
{
	if (!isCustom)  //�����Զ��尴ť
	{
		if (g_keyRight)
		{
			g_keyRight = false;
			/*_interval = 0.0f;*/
			_id = _id + 1;
			if (16 == _id)
			{
				_id = 1;
			}
			if (DataM::getInstance()->maxLevelCanPlayed < _id)
			{
				_id = 1;
			}
			this->setOption();
		}
		else if (g_keyLeft)
		{
			g_keyLeft = false;
			/*_interval = 0.0f;*/
			if (_id > 1)
			{
				_id--;
				/*	this->updateLevel();*/
			}
			else
			{
				_id = DataM::getInstance()->maxLevelCanPlayed;
			}
			this->setOption();
		}
		else if (g_keyUp)
		{
			g_keyUp = false;
			/*	_interval = 0.0f;*/
			if (_id > 5)
			{
				_id = _id - 5;
				/*this->updateLevel();*/
			}
			else
			{
				_id = ((int)((DataM::getInstance()->maxLevelCanPlayed - _id) / 5)) * 5 + (_id - 1) % 5 + 1;
			}
			this->setOption();
		}
		else if (g_keyDown)
		{
			g_keyDown = false;
			/*	_interval = 0.0f;*/
			if (_id < 11 && _id + 5 <= DataM::getInstance()->maxLevelCanPlayed)
			{
				_id = _id + 5;
				/*this->updateLevel();*/
			}
			else
			{
				isCustom = true;
				Sprite *customSelectedRect = static_cast<Sprite *>(this->getChildByName("customSelectedRect"));
				customSelectedRect->setVisible(isCustom);
				Sprite *selectedRect = static_cast<Sprite *>(this->getChildByName("selectedRect"));
				selectedRect->setVisible(!isCustom);
				//_id = (_id - 1) % 5 + 1;
			}
			this->setOption();
		}
		else if (g_keyStart && (DataM::getInstance()->maxLevelCanPlayed >= _id))
		{
			g_keyStart = false;
			DataM::getInstance()->set_id(_id);
			/*AudioM::play2d(A_START);*/
			//removeAllChildren();
			this->unscheduleUpdate();
			SceneM::getInstance()->changeScene(kSelectHeroScene, kTransitionCrossFade);
		}
		else if (g_keySelect)
		{
			g_keySelect = false;
			/*AudioM::play2d(A_START);*/
			this->unscheduleUpdate();
			SceneM::getInstance()->changeScene(kMenuScene, kTransitionFade);
		}
	}
	else //isCustom
	{
		if (g_keyUp)
		{
			g_keyUp = false;
			isCustom = false;
			Sprite *customSelectedRect = static_cast<Sprite *>(this->getChildByName("customSelectedRect"));
			customSelectedRect->setVisible(isCustom);
			Sprite *selectedRect = static_cast<Sprite *>(this->getChildByName("selectedRect"));
			selectedRect->setVisible(!isCustom);
		}
		else if (g_keySelect)
		{
			g_keySelect = false;
			this->unscheduleUpdate();
			/*AudioM::play2d(A_START);*/
			SceneM::getInstance()->changeScene(kMenuScene, kTransitionFade);
		}
		else if (g_keyStart && (DataM::getInstance()->maxLevelCanPlayed >= _id))
		{
			g_keyStart = false;
			_id = -1;
			DataM::getInstance()->set_id(_id);
			this->unscheduleUpdate();
			/*AudioM::play2d(A_START);*/
			SceneM::getInstance()->changeScene(kCustomScene);
		}
	}
}

void LevelScene::setOption() 
{
	//i��j��0Ϊ��ʼ
	int i = ((int)(_id - 1) / 5);
	int j = _id - i * 5 - 1;
	selectedRect->setPosition(Vec2(166 + 173 * j, 557 - 173 * i));
	//_select->setPosition(Vec2(x, y));
}