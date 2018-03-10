/***********************************************

�����ά������ҳ����������ڣ���Ҫ��������ҳ���ǰ�ˡ���ť����
��̨���ݵĴ��ݣ���Ҫָ�ӵ���Ϣ��Ƥ����Ϣ�����ݸ�DataM��

***********************************************/

#include "data\Global.h"
#include "scene\SceneM.h"
#include "SkillScene.h"
#include "data\ChineseFonts.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);

void SkillScene::onExit()
{
	Layer::onExit();
	removeAllChildrenWithCleanup(true);
}

void SkillScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	scheduleUpdate();
}

bool SkillScene::init()
{
	//���ݳ�ʼ��
	detailLayer = false;
	option = 0;
	row = 0;
	col = 0;
	skinMax = 3;
	dataM = DataM::getInstance();
	skillDetail = SkillDetail::getInstance();
	skinId = DataM::getInstance()->getSkinId();
	heroType = (HeroType)DataM::getInstance()->getHType();
	skinNum = SuccessData::getInstance()->updateSkin();
	DataM::getInstance()->getAllSPMatrix(SP, SPMax, SPNeed, SPDepend);


	Sprite *skillSceneBG = Sprite::create("LevelBackground.jpg");
	skillSceneBG->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(skillSceneBG, 0);

	Label *skillLabel = Label::create(FontToUTF8("����"), "Simple.ttf", 70);
	skillLabel->setPosition(Vec2(SCREEN_WIDTH*0.25, 703));
	this->addChild(skillLabel, 1);

	Label *skinLabel = Label::create(FontToUTF8("Ƥ��"),"Simple.ttf",70);
	skinLabel->setPosition(Vec2(SCREEN_WIDTH*0.75, 703));
	this->addChild(skinLabel, 1);

	rectBG = Sprite::create("SkillBGRect.png");
	rectBG->setPosition(Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5));
	this->addChild(rectBG, 0);

	//�Ϸ����
	upSelectedRect = ui::Scale9Sprite::create("Normal.png");
	upSelectedRect->setContentSize(Size(200, 80));
	upSelectedRect->setPosition(SCREEN_WIDTH *(0.25 + option*0.5), 703);
	this->addChild(upSelectedRect, 2, "customSelectedRect");
	upSelectedRect->setVisible(!detailLayer);

	//�·����
	downSelectedRect = Sprite::create("SelectedRect.png");
	downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));
	this->addChild(downSelectedRect, 2);
	downSelectedRect->setVisible(detailLayer);

	//��������ʼ��
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (0 != SPMax[i][j])
			{
				String *unitSpriteName = String::createWithFormat("Skill%d_%d_%d.png", heroType, i, j);
				Sprite *unitSprite = Sprite::create(unitSpriteName->getCString());
				unitSprite->setPosition(Vec2(168 + j * 173, 582 - 126 * i));
				this->addChild(unitSprite, 1, i * 10 + j);

				//��Ӱ
				Sprite *shadowRect = Sprite::create("Shadow.png");
				shadowRect->setPosition(Vec2(50, 50));
				unitSprite->addChild(shadowRect, 2, "shadow");
				shadowRect->setVisible(!(bool)SP[i][j]);

				//��ͨ���
				Sprite *normalRect = Sprite::create("Normal.png");
				normalRect->setPosition(Vec2(50, 50));
				unitSprite->addChild(normalRect, 3);

				if (0 == j)
				{
					Sprite *fontBG = Sprite::create("skillRect.png");
					fontBG->setPosition(Vec2(80, 10));
					unitSprite->addChild(fontBG, 2, "fontBG");
					fontBG->setVisible((bool)SP[i][j]);
					
					String *skillLevelName = String::createWithFormat("%d/%d", SP[i][j], SPMax[i][j]);
					Label *skillLevelLabel = Label::create(skillLevelName->getCString(), "Simple.ttf", 19);
					fontBG->addChild(skillLevelLabel, 2, "skillLevel");
					skillLevelLabel->setPosition(20, 10);
					skillLevelLabel->setColor(Color3B(76, 76, 76));
				}
			}
		}
	}

	//����������ͷ
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (0 != SPDepend[i][j])
			{
				Sprite *tempUnitSprite = static_cast<Sprite *> (this->getChildByTag(i * 10 + j));
				auto tempUnitSpritePos = tempUnitSprite->getPosition();
				if (0 != (SPDepend[i][j] & 1))
				{
					Sprite *arrow = Sprite::create("rightArrow.png");
					arrow->setPosition(Vec2(-85 + tempUnitSpritePos.x, tempUnitSpritePos.y));
					//��ֹ�ӵ���������˸,��������Ϊ�·����ο�ĺ���
					rectBG->addChild(arrow, 1);
				}
				if (0 != (SPDepend[i][j] & 8))
				{
					Sprite *arrow = Sprite::create("downArrow.png");
					arrow->setPosition(Vec2(tempUnitSpritePos.x, 63 + tempUnitSpritePos.y));
					//��ֹ�ӵ���������˸,��������Ϊ�·����ο�ĺ���
					rectBG->addChild(arrow, 1);
				}
				//�˴������·����Ҳ������������Ϊ��ʱ����Ϸ�л�û��������������֣���������ˣ����Բο������������Ӧ�úܺ�д
			}
		}
	}

	//����
	starAll = Sprite::create("Star1.png");
	starAll->setPosition(800, 90);
	rectBG->addChild(starAll, 1, "star0");

	starNeed = Sprite::create("Star1.png");
	starNeed->setPosition(550, 90);
	rectBG->addChild(starNeed,1,"star1");

	starAllNum = dataM->getSP();
	String *starAllNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("ʣ��"), starAllNum);
	starAllNumLabel = Label::create(starAllNumLabelString->getCString(), "Simple.ttf", 30);
	rectBG->addChild(starAllNumLabel);
	starAllNumLabel->setPosition(790, 90);

	starNeedNum = SPNeed[row][col];
	//String *starNeedNumLabelString = String::createWithFormat("%s         X%02d", FontToUTF8("����"), starNeedNum);
	//starNeedNumLabel = Label::create(starNeedNumLabelString->getCString(), "Simple.ttf", 30);
	starNeedNumLabel = Label::create("", "Simple.ttf", 30);
	rectBG->addChild(starNeedNumLabel);
	starNeedNumLabel->setPosition(540, 90);
	
	starNeedNumLabel->setVisible(false);
	starNeed->setVisible(false);

	//��������,ê��Ϊ0,0
	skillDiscribeLabel = Label::create("", "Simple.ttf", 30);
	skillDiscribeLabel->setAnchorPoint(Vec2::ZERO);
	skillDiscribeLabel->setPosition(180, 20);
	rectBG->addChild(skillDiscribeLabel);
	skillDiscribeLabel->setVisible(false);

	//��������,ê��Ϊ0,0
	skillNameLabel = Label::create("", "Simple.ttf", 30);
	skillNameLabel->setAnchorPoint(Vec2::ZERO);
	skillNameLabel->setPosition(180, 75);
	rectBG->addChild(skillNameLabel);
	skillNameLabel->setVisible(false);

	//Ƥ��ҳ��,��ǩ101
	Sprite *currentSkin = Sprite::create(String::createWithFormat("Skin%d_%d.png", (int)heroType, skinId)->getCString());
	currentSkin->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(currentSkin, 1, 101);
	currentSkin->setVisible(false);
	currentSkin->setScale(0.4);
	//Ƥ������
	Label *skinName = Label::create(SkillDetail::getInstance()->getSkinName(), "Simple.ttf", 42);
	skinName->setPosition(SCREEN_WIDTH/2, 100);
	this->addChild(skinName, 1, "skinName");
	skinName->setVisible(false);
	//���ͷ����ǩ100
	Sprite *leftArrow = Sprite::create("skinArrow.png");
	leftArrow->setPosition(53, SCREEN_HEIGHT * 0.5);
	this->addChild(leftArrow, 1, 100);
	leftArrow->setName("leftArrow");
	leftArrow->setVisible(false);
	//�Ҽ�ͷ����ǩ102
	Sprite *rightArrow = Sprite::create("skinArrow.png");
	rightArrow->setPosition(SCREEN_WIDTH - 53, SCREEN_HEIGHT * 0.5);
	this->addChild(rightArrow, 1, 102);
	rightArrow->setRotation(180);
	rightArrow->setVisible(false);
	rightArrow->setName("rightArrow");
	//Ƥ����Բ
	Sprite *bigCircle = Sprite::create("FullBigCircle.png");
	bigCircle->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(bigCircle, 0, "bigCircle");
	bigCircle->setScale(2.0f);
	bigCircle->setVisible(false);

	return true;
}

void SkillScene::update(float dt)
{
	if (true == g_keySelect)
	{
		g_keySelect = false;
		if (detailLayer)
		{
			detailLayer = false;
			//�·������ʧ
			downSelectedRect->setVisible(detailLayer);

			//�Ϸ�������
			upSelectedRect->setVisible(!detailLayer);

			//��ʧ��Բ
			Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
			bigCircle->setVisible(detailLayer);

			if (0 == option)
			{
				//��������
				starNeedNumLabel->setVisible(false);
				starNeed->setVisible(false);

				//��������
				skillDiscribeLabel->setVisible(false);

				//��������
				skillNameLabel->setVisible(false);

				//�����Ϸ����
				upSelectedRect->setVisible(!detailLayer);

				//�رմ�Բ
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
		else
		{
			this->unscheduleUpdate();
			SceneM::getInstance()->changeScene(kHeroScene, kTransitionCrossFade);
		}
	}

	if (true == g_keyStart)
	{
		g_keyStart = false;
		if (detailLayer)
		{
			if (0 == option)
			{
				bool isDependReady = true;  //ǰ���Ƿ�׼����
				if ((0 != (SPDepend[row][col] & 8)) && (0 == SP[row - 1][col]))
				{
					isDependReady = false;
				}
				if ((0 != (SPDepend[row][col] & 1)) && (0 == SP[row][col - 1]))
				{
					isDependReady = false;
				}
				//�˴������·����Ҳ������������Ϊ��ʱ����Ϸ�л�û��������������֣���������ˣ����Բο������������Ӧ�úܺ�д


				//�Ӽ���
				if (dataM->getSP() >= SPNeed[row][col] && isDependReady)  //��SP�ж�
				{
					int spDecreament = dataM->addSkill(row, col);

					//ˢ��͸��
					auto tempUnitSprite = static_cast<Sprite *>(this->getChildByTag(row * 10 + col));
					Sprite *tempShadowRect = static_cast<Sprite *>(tempUnitSprite->getChildByName("shadow"));
					tempShadowRect->setVisible(!(bool)SP[row][col]);

					if (0 == col)
					{
						//ˢ�����½ǿ��
						Sprite *currentFontBG = static_cast<Sprite *>(tempUnitSprite->getChildByName("fontBG"));
						currentFontBG->setVisible((bool)SP[row][col]);

						Label *cuttentskillLevel = static_cast<Label *>(currentFontBG->getChildByName("skillLevel"));
						String *skillLevelName = String::createWithFormat("%d/%d", SP[row][col], SPMax[row][col]);
						cuttentskillLevel->setString(skillLevelName->getCString());
					}

					//ˢ��ʣ�༼�ܵ�
					auto tempStarAllNum = dataM->getSP();
					String *tempStarAllNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("ʣ��"), tempStarAllNum);
					starAllNumLabel->setString(tempStarAllNumLabelString->getCString());
					//ˢ�����輼�ܵ�
					auto tempStarNeedNum = SPNeed[row][col];
					String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("����"), tempStarNeedNum);
					starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());
					//ˢ�¼�������
					char *tempSkillName = skillDetail->getSkillName(row, col);
					skillNameLabel->setString(tempSkillName);

					//�����ܳɾ�
					SuccessData::getInstance()->updateIsSkillMax();

					//�ɾ͸���
					SuccessData::getInstance()->updateAlldata();

					if (spDecreament != 0)
					{
						//���ܶ���
						tempUnitSprite->stopAllActions();
						auto blink = Blink::create(1.5f, 2);
						auto changeToVisible = [&](Node * tempNode) {tempNode->setVisible(true); };
						auto seq = Sequence::create(blink, CallFuncN::create(changeToVisible), NULL);
						tempUnitSprite->runAction(seq);
						starAllNumLabel->runAction(seq->clone());
						starNeedNumLabel->runAction(seq->clone());
						auto star0 = static_cast<Sprite *>(rectBG->getChildByName("star0"));
						auto star1 = static_cast<Sprite *>(rectBG->getChildByName("star1"));
						star0->stopAllActions();
						star1->stopAllActions();
						star0->runAction(seq->clone());
						star1->runAction(seq->clone());
					}
					else
					{
						//����Ч
						SimpleAudioEngine::getInstance()->playEffect("noCanDoInSkillScene.mp3", false);

					}

				}
				else
				{
					//����Ч
					SimpleAudioEngine::getInstance()->playEffect("noCanDoInSkillScene.mp3", false);

				}
			}
			if (1 == option)
			{
				this->removeAllChildrenWithCleanup(true);
				this->removeFromParent();
				SceneM::getInstance()->changeScene(kMenuScene);
			}
		}
		else //detailLayer = false,�������;
		{
			detailLayer = true;
			if (0 == option)
			{
				//�·�������
				downSelectedRect->setVisible(detailLayer);

				//�Ϸ������ʧ
				upSelectedRect->setVisible(!detailLayer);

				//ˢ�����輼�ܵ�
				auto tempStarNeedNum = SPNeed[row][col];
				String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("����"), tempStarNeedNum);
				starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());
				starNeedNumLabel->setVisible(true);
				starNeed->setVisible(true);

				//��������
				char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
				skillDiscribeLabel->setString(tempSkillDiscribe);
				skillDiscribeLabel->setVisible(true);

				//��������
				char *tempSkillName = skillDetail->getSkillName(row, col);
				skillNameLabel->setString(tempSkillName);
				skillNameLabel->setVisible(true);
			}
			if (1 == option)
			{

				//�Ϸ������ʧ
				upSelectedRect->setVisible(!detailLayer);

				//���ִ�Բ
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
	}

	if (true == g_keyUp)
	{
		g_keyUp = false;

		//����Ч
		SimpleAudioEngine::getInstance()->playEffect("buttonMouseMoveOverInSikllScene.mp3", false);

		if (detailLayer)
		{
			if (0 == option)
			{
				if (0 == row)
				{
					detailLayer = false;
					//�·������ʧ
					downSelectedRect->setVisible(detailLayer);

					//�Ϸ�������
					upSelectedRect->setVisible(!detailLayer);


					//��������
					starNeedNumLabel->setVisible(false);
					starNeed->setVisible(false);

					//��������
					skillDiscribeLabel->setVisible(false);

					//��������
					skillNameLabel->setVisible(false);
				}
				else
				{
					--row;
					while (0 == SPMax[row][col])  //��֤�м���
					{
						--col;
					}

					//�ƶ����
					downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));

					//ˢ�����輼�ܵ�
					auto tempStarNeedNum = SPNeed[row][col];
					String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("����"), tempStarNeedNum);
					starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());

					//��������
					char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
					skillDiscribeLabel->setString(tempSkillDiscribe);

					//��������
					char *tempSkillName = skillDetail->getSkillName(row, col);
					skillNameLabel->setString(tempSkillName);
				}
			}
			else  //1==option
			{
				detailLayer = false;
				//�Ϸ�������
				upSelectedRect->setVisible(!detailLayer);

				//��ʧ��Բ
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
	}

	if (true == g_keyDown)
	{
		g_keyDown = false;

		//����Ч
		SimpleAudioEngine::getInstance()->playEffect("buttonMouseMoveOverInSikllScene.mp3", false);

		if (detailLayer)
		{
			if (0 == option) 
			{
				if (row <= 2)//row=3ʱ������Ч
				{
					++row;
					while (0 == SPMax[row][col])  //��֤�м���
					{
						++col;
					}

					//�ƶ����
					downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));

					//ˢ�����輼�ܵ�
					auto tempStarNeedNum = SPNeed[row][col];
					String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("����"), tempStarNeedNum);
					starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());

					//��������
					char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
					skillDiscribeLabel->setString(tempSkillDiscribe);

					//��������
					char *tempSkillName = skillDetail->getSkillName(row, col);
					skillNameLabel->setString(tempSkillName);
				}
			}
		}
		else //detailLayer ==false
		{
			detailLayer = true;
			if (0 == option)
			{
				//�·�������
				upSelectedRect->setVisible(!detailLayer);
				//�Ϸ������ʧ
				downSelectedRect->setVisible(detailLayer);

				row = 0;
				col = 0;

				//ˢ�����輼�ܵ�
				auto tempStarNeedNum = SPNeed[row][col];
				String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("����"), tempStarNeedNum);
				starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());
				starNeedNumLabel->setVisible(true);
				starNeed->setVisible(true);

				//��������
				char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
				skillDiscribeLabel->setString(tempSkillDiscribe);
				skillDiscribeLabel->setVisible(true);

				//��������
				char *tempSkillName = skillDetail->getSkillName(row, col);
				skillNameLabel->setString(tempSkillName);
				skillNameLabel->setVisible(true);
			}
			else  //1==option
			{
				//�Ϸ������ʧ
				upSelectedRect->setVisible(!detailLayer);

				//���ִ�Բ
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
	}

	if (true == g_keyLeft || true == g_keyRight)
	{
		int move = (true == g_keyLeft) ? (-1) : (1);  //�����moveΪ-1���Ҽ�Ϊ1
		g_keyLeft = false;
		g_keyRight = false;

		//����Ч
		SimpleAudioEngine::getInstance()->playEffect("buttonMouseMoveOverInSikllScene.mp3", false);

		if (detailLayer)
		{
			if (0 == option)
			{
				do
				{
					col += move;
					if (col < 0)
					{
						col += 5;
					}
					col = col % 5;
				} while (0 == SPMax[row][col]);

				//�ƶ����
				downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));

				//ˢ�����輼�ܵ�
				auto tempStarNeedNum = SPNeed[row][col];
				String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("����"), tempStarNeedNum);
				starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());

				//��������
				char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
				skillDiscribeLabel->setString(tempSkillDiscribe);

				//��������
				char *tempSkillName = skillDetail->getSkillName(row, col);
				skillNameLabel->setString(tempSkillName);

			}
			else //1 ==option
			{

				skinId+=move;
				if (skinId < 0)
				{
					skinId += skinMax;
				}
				if (skinId >= skinMax)
				{
					skinId -= skinMax;
				}
				Sprite *currentSkin = static_cast<Sprite *>(this->getChildByTag(101));
				Label *skinName = static_cast<Label *>(this->getChildByName("skinName"));
				if (skinId < skinNum)
				{
					//����Id
					dataM->updateSkinId(skinId);
					//�޸�Ƥ��
					currentSkin->setTexture(String::createWithFormat("Skin%d_%d.png", (int)heroType, skinId)->getCString());
					//Ƥ������
					skinName->setString(SkillDetail::getInstance()->getSkinName());
				}
				else 
				{
					currentSkin->setTexture(String::createWithFormat("Skin%d_%d_1.png", (int)heroType, skinId)->getCString());
					if (skinId == skinMax - 1)
					{
						skinName->setString(FontToUTF8("������гɾͿ�����Ƥ��"));
					}
					else
					{
						skinName->setString(FontToUTF8("��ɲ��ֳɾͿ�����Ƥ��"));
					}
				}

			}
		}
		else  //detailLayer == false
		{
			option ^= 1;
			upSelectedRect->setPosition(SCREEN_WIDTH *(0.25 + option*0.5), 703);
			bool isVisited = (bool)option; //isVisited ΪfalseʱƤ��ҳ��Ϊfalse
			{
				//Ƥ��ҳ��,��ǩ101
				auto currentSkin = this->getChildByTag(101);
				currentSkin->setVisible(isVisited);
				Label *skinName = static_cast<Label *>(this->getChildByName("skinName"));
				skinName->setVisible(isVisited);
				//���ͷ����ǩ100
				auto leftArrow = this->getChildByTag(100);
				leftArrow->setVisible(isVisited);
				//�Ҽ�ͷ����ǩ102
				auto rightArrow = this->getChildByTag(102);
				rightArrow->setVisible(isVisited);

				//��������ʼ��
				for (int i = 0; i < 5; ++i)
				{
					for (int j = 0; j < 5; ++j)
					{
						if (0 != SPMax[i][j])
						{
							auto tempUnitSprite = this->getChildByTag(i * 10 + j);
							tempUnitSprite->setVisible(!isVisited);
						}
					}
				}
				//����ҳ���·���
				rectBG->setVisible(!isVisited);
			}
		}
	}

	//����Ч
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		unsigned int randNum = rand() % 6;
		SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("skillScene%d.mp3", randNum)->getCString(), false);
	}

}