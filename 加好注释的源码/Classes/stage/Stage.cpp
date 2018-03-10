/***********************************************

�����ά����Ϸ�ھ����������ڣ�������ͼԪ�صĴ�����ˢ�£�
ͬʱ�ж���ͼԪ���Ƿ�ɴ򣬿��ƶ�
HP���������Ĺ�����Ϸ����ͼ��Ĺ����������Ƿ����Ҳ�ڸ����й���

***********************************************/

#include "Stage.h"
#include "data\Global.h"
#include <string>
#include <sstream>
#include "data\DataM.h"
#include "PauseLayer.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


void Stage::onExit()
{
	Layer::onExit();
	bigSkillAnimate->release(); //��ʼ����retain��

}

bool Stage::init()
{
	this->LayerColor::init();
	_id = DataM::getInstance()->get_id();
	_bg = LayerColor::create(Color4B(254, 184, 137, 255));
	_bg->setPosition(Vec2::ZERO);
	this->addChild(_bg, 0);

	_enemyID = 0;  //��ʼ��

	this->initMap();
	return true;
}

void Stage::initInfo()
{
	// �·���ɫ����
	auto rectangle = Sprite::create("Rectangle.png");
	rectangle->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(rectangle, 0);
	
	// �߿�
	for (int i = 0; i < 16; ++i)
	{
		Sprite* borderSprite1 = Sprite::create("Border.png");
		borderSprite1->setPosition(Vec2(i * 64 + 32, SCREEN_HEIGHT - 32));
		_bg->addChild(borderSprite1, 0);
	}
	for (int i = 0; i < 11; ++i)
	{
		Sprite* borderSprite2 = Sprite::create("Border.png");
		borderSprite2->setPosition(Vec2(32, i * 64 + 32));
		_bg->addChild(borderSprite2, 0);
		Sprite* borderSprite3 = Sprite::create("Border.png");
		borderSprite3->setPosition(Vec2(SCREEN_WIDTH - 32, i * 64 + 32));
		_bg->addChild(borderSprite3, 0);
	}

	// ����ͼ��
	heroType = DataM::getInstance()->getHType();				// Ӣ������
	Sprite *bigSkillImage = Sprite::create();
	auto bigSkillName = String::createWithFormat("BigSkill%d_0.png", (int)heroType)->getCString();
	bigSkillImage->initWithSpriteFrameName(bigSkillName);
	bigSkillImage->setPosition(828, 60);
	this->addChild(bigSkillImage, 0, "bigSkillImage");

	//���ж���
	//����֡����
	Vector<SpriteFrame *> bigSkillFrames(2);
	auto cache = SpriteFrameCache::getInstance();
	//��������
	for (auto i = 0; i < 2; ++i)
	{
		auto bigSkillImageFrameName = String::createWithFormat("BigSkill%d_%d.png", (int)heroType, i)->getCString();
		auto frame = cache->getSpriteFrameByName(bigSkillImageFrameName);
		bigSkillFrames.pushBack(frame);
	}
	//��������
	auto animation = Animation::createWithSpriteFrames(bigSkillFrames, 0.16, CC_REPEAT_FOREVER);
	bigSkillAnimate = Animate::create(animation);
	bigSkillAnimate->retain(); //��ֹ�Զ��ͷ�

	// hp������
	hpSlider = Slider::create();
	hpSlider->loadProgressBarTexture("HP1.png");
	hpSlider->loadBarTexture("HP0.png");
	this->addChild(hpSlider, 1);
	hpSlider->setPercent(100);
	hpSlider->setPosition(Vec2(360, 86));
	hpSlider->setTouchEnabled(false);

	// mp������
	mpSlider = Slider::create();
	mpSlider->loadProgressBarTexture("MP1.png");
	mpSlider->loadBarTexture("MP0.png");
	this->addChild(mpSlider, 1);
	mpSlider->setPercent(1);
	mpSlider->setPosition(Vec2(360, 38));
	mpSlider->setTouchEnabled(false);
	readyInterval = TankData::getInstance()->getReadyInterval();  //��ȴʱ��

	isReady = false;
	// MPר��
	this->schedule(schedule_selector(Stage::MPUpdate), float(readyInterval / 100));

	// �ؿ�������
	progressSlider = Slider::create();
	progressSlider->loadProgressBarTexture("Progress0.png");
	progressSlider->loadBarTexture("Progress1.png");
	this->addChild(progressSlider, 1);
	progressSlider->setPercent(0);
	progressSlider->setPosition(Vec2(627, 58));
	progressSlider->setTouchEnabled(false);
	progressSlider->setRotation(-90);

	// HP�ͽ��Ⱥ��α�ı仯 ��ʱ��
	this->schedule(schedule_selector(Stage::sliderUpdate));

	// Ruler
	auto ruler = Sprite::create("Ruler.png");
	ruler->setPosition(Vec2(671, 58));
	this->addChild(ruler, 1);

	// �α�
	cursor = Sprite::create("Cursor.png");
	cursor->setPosition(Vec2(666, 20));
	this->addChild(cursor, 2);
}

void Stage::initMap()
{
	stringstream file1;
	auto id = (DataM::getInstance()->get_id());  //��ȡ�ؿ���Ϣ

	String *name;
	if (id > 0)
	{
		name = String::createWithFormat("map%d.txt", id);
	}
	else
	{
		//�Զ����ͼд������
		name = String::createWithFormat("%s.txt", DataM::getInstance()->getMapName().c_str());
	}

	auto data = FileUtils::getInstance()->getStringFromFile(name->getCString());  //��ùؿ���Ϣ
	file1.str(data);
	for (auto i = MAP_ROW - 1; i >= 0; --i)
	{
		for (auto j = 0; j < MAP_COL; j++)
		{
			file1 >> _map[i][j];
			if (_map[i][j] == BRICK)
			{
				_map[i][j] |= 0xf0;  //����Ϊ����ש��
			}
		}
	}

	// �˴�Ϊ�˼Ӻ���߽磬�صض�д��һ��ѭ��
	for (auto i = MAP_ROW - 1; i >= 0; --i)
	{
		for (auto j = 0; j < MAP_COL; j++)
		{
			this->createMapCell(i, j, _map[i][j]);
		}
	}

	stringstream file2;
	id = _id > LEVEL_NUM ? LEVEL_NUM : _id; // ���һ��֮�󣬵���̹�����������һ��һ�� 
	if (id > 0)
	{
		name = String::createWithFormat("enemy%d.txt", id);
	}
	else
	{
		//�Զ����ͼ
		name = String::createWithFormat("EnemyDifficulty%d.txt", DataM::getInstance()->getEnemyDifficulty());
	}

	data = FileUtils::getInstance()->getStringFromFile(name->getCString());
	file2.str(data);
	for (auto i = 0; i < ENEMY_NUM; ++i)
	{
		file2 >> _type[i];
	}
}

void Stage::createMapCell(int row, int col, int type)
{
	Sprite* cell = NULL;
 	auto zorder = 1;

	if (type == WATER)
	{
		// ˮ����
		cell = Sprite::createWithSpriteFrameName("Water1.png");
		cell->setName("water");
		Vector<SpriteFrame*> animFrames(2);
		auto cache = SpriteFrameCache::getInstance();
		for (auto i = 0; i < 2; i++)
		{
			auto name = String::createWithFormat("Water%d.png", i)->getCString();
			auto frame = cache->getSpriteFrameByName(name);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
		cell->runAction(RepeatForever::create(Animate::create(animation)));
	
		//ˮ�߽�
		if (row - 1 < 0 || _map[row - 1][col] != WATER)
		{
			auto waterBorder = Sprite::create("WaterBorder.png");
			waterBorder->setRotation(180);
			waterBorder->setPosition(Vec2(CELL_WIDTH / 2, CELL_HEIGHT / 2));
			cell->addChild(waterBorder);
		}
		if (row + 1 <= MAP_ROW-1 && _map[row + 1][col] != WATER)
		{
			auto waterBorder = Sprite::create("WaterBorder.png");
			waterBorder->setRotation(0);
			waterBorder->setPosition(Vec2(CELL_WIDTH / 2, CELL_HEIGHT / 2));
			cell->addChild(waterBorder);
		}
		if (col - 1 >= 0 && _map[row][col - 1] != WATER)
		{
			auto waterBorder = Sprite::create("WaterBorder.png");
			waterBorder->setRotation(270);
			waterBorder->setPosition(Vec2(CELL_WIDTH / 2, CELL_HEIGHT / 2));
			cell->addChild(waterBorder);
		}
		if (col + 1 <= MAP_COL-1 && _map[row][col + 1] != WATER)
		{
			auto waterBorder = Sprite::create("WaterBorder.png");
			waterBorder->setRotation(90);
			waterBorder->setPosition(Vec2(CELL_WIDTH / 2, CELL_HEIGHT / 2));
			cell->addChild(waterBorder);
		}

	}
	else
	{
		string name;
		if ((type & 0x0f) != BRICK)
		{
			name = this->getSpriteName(type);
		}
		else
		{
			name = String::createWithFormat("Brick%d.png", ((row + col) % 2))->getCString();
		}

		if (type == GRASS)
		{
			zorder = 4;		// ����̹���Ϸ�������Ҫ�޸���Ⱦ�㼶 
		}
		if (name != "" && type != HOME1 && type != HOME3)
		{
			cell = Sprite::create(name);
		}
	}
	if (cell)
	{
		auto tag = row * 100 + col;  //ש���ǩ
		cell->setAnchorPoint(Vec2(0.5f, 0.5f));  //�е�
		cell->setPosition(getPos(row, col));

		if (type == HOME2 || type == HOME4)
		{
			auto tempPos = cell->getPosition();
			cell->setPosition(Vec2(tempPos.x + CELL_WIDTH / 2, tempPos.y - CELL_HEIGHT / 2));
		}

		_bg->addChild(cell, zorder, tag);
	}
}

string Stage::getSpriteName(int type)
{
	string name;
	switch (type & 0x0f)
	{
	case GRID1:
		name = "Grid1.png";
		break;
	case GRID2:
		name = "Grid2.png";
		break;
	case GRID3:
		name = "Grid3.png";
		break;
	case GRID4:
		name = "Grid4.png";
		break;
	case GRASS:
		name = "Grass.png";
		break;
	case HOME2:
		name = "Home0.png";
		break;
	case HOME4:
		name = "Home1.png";
		break;
	default:
		break;
	}
	return name;
}

bool Stage::isCanHit(int row, int col)
{
	if (row < 0 || row >= MAP_ROW || col < 0 || col >= MAP_COL)
		return false;
	switch (_map[row][col] & 0x0f)
	{
	case BRICK:
	case GRID1:
	case GRID2:
	case GRID3:
	case GRID4:
	case HOME3:
	case HOME4:
		return true;
	default:
		return false;
	}
}

bool Stage::isCanWalk(int row, int col)
{
	if (row < 0 || row >= MAP_ROW || col < 0 || col >= MAP_COL)
		return false;
	switch (_map[row][col] & 0x0f)
	{
	case LAND:
	case GRASS:
		return true;
	default:
		return false;
	}
}

void Stage::pauseGame()
{
	pauseLayer = PauseLayer::create();
	this->addChild(pauseLayer, 1, 100);
	this->pause();
}

void Stage::resumeGame()
{
	pauseLayer->removeFromParent();
	this->resume();
}

void Stage::sliderUpdate(float dt)
{
	int hpPercent = GameScene::getTankM()->remainedHP();
	if (hpPercent < 0)
	{
		hpPercent = 0;
	}
	if (hpPercent > 100)
	{
		hpPercent = 100;
	}
	hpSlider->setPercent(hpPercent);

	int progressPercent = GameScene::getTankM()->getProgress();
	if (progressPercent < 0)
	{
		progressPercent = 0;
	}
	if (progressPercent > 100)
	{
		progressPercent = 100;
	}
	progressSlider->setPercent(progressPercent);

	cursor->setPositionY((int)(progressPercent*0.76) + 20);

}

void Stage::MPUpdate(float dt)
{
	int currentMPPercent = mpSlider->getPercent();
	if (100 == currentMPPercent)
	{
		isReady = true;
		this->unschedule(schedule_selector(Stage::MPUpdate));
		Sprite *bigSkillImage = static_cast<Sprite *>(this->getChildByName("bigSkillImage"));
		if (TypeSPE != DataM::getInstance()->getHType())
		{
			bigSkillImage->runAction(bigSkillAnimate);
		}
		else //��ֹ������˸bug
		{
			auto bigSkillName = String::createWithFormat("BigSkill2_1.png")->getCString();
			bigSkillImage->setTexture(bigSkillName);
		}
		
		//����Ч
		SimpleAudioEngine::getInstance()->playEffect("bigSkillReady.mp3", false);

		return;
	}
	else
	{
		mpSlider->setPercent(mpSlider->getPercent() + 1);
	}
}

bool Stage::changeIsKReady()
{
	if (isReady)
	{
		isReady = false;
		mpSlider->setPercent(1);
		this->schedule(schedule_selector(Stage::MPUpdate), float(readyInterval / 100));
		//ֹͣ����ͼ����˸
		Sprite *bigSkillImage = static_cast<Sprite *>(this->getChildByName("bigSkillImage"));

		if (TypeSPE != DataM::getInstance()->getHType())
		{
			bigSkillImage->stopAction(bigSkillAnimate);
		}

		auto bigSkillName = String::createWithFormat("BigSkill%d_0.png", (int)heroType)->getCString();
		bigSkillImage->setTexture(bigSkillName);

		return true;
	}
	else
	{
		return false;
	}
}


void Stage::updateMapCell(int row, int col)
{
	auto type = _map[row][col];  //��ǰ��λ
	auto tag = row * 100 + col;  
	auto cell = (Sprite*)_bg->getChildByTag(tag);
	if (type == LAND)
	{
		if (cell)
		{
			cell->removeFromParent();
		}
	}
	else if ((type & 0x0f) == BRICK && (type & 0xf0) != 0xf0) // ��ȱ��ש�� 
	{
		//auto left = 0, right = CELL_WIDTH, bottom = 0, top = CELL_HEIGHT;
		//auto pos = getPos(row, col);
		//if ((type & 0x30) == 0) // �±�Ϊ�� 
		//{
		//	top -= CELL_HEIGHT / 2;
		//}
		//if ((type & 0xc0) == 0) // �ϱ�Ϊ�� 
		//{
		//	bottom += CELL_HEIGHT / 2;
		//	pos.y -= bottom;  //?
		//}
		//if ((type & 0x50) == 0) // �ұ�Ϊ�� 
		//{
		//	right -= CELL_WIDTH / 2;
		//}
		//if ((type & 0xa0) == 0) // ���Ϊ�� 
		//{
		//	left += CELL_WIDTH / 2;
		//	pos.x += left;		//?
		//}
		//cell->setTextureRect(Rect(left, bottom, right - left, top - bottom));
		//cell->setPosition(pos); // ê��Ϊ���Ͻǣ�����߻��ϱ�Ϊ��ʱ��Ҫ�ı����� 

		// �����������������Ͻ�Ϊԭ�� ,Rect�����Ͻ�Ϊԭ��
		auto left = 0, right = CELL_WIDTH, top = 0, bottom = CELL_HEIGHT;

		auto pos = getPos(row, col);
		
		if ((type & 0x30) == 0) // �±�Ϊ�� 
		{
			bottom = bottom / 2;
			pos.y = pos.y + CELL_HEIGHT / 4;
		}
		if ((type & 0xc0) == 0) // �ϱ�Ϊ�� 
		{
			top = CELL_HEIGHT / 2;
			pos.y = pos.y - CELL_WIDTH / 4;
		}
		if ((type & 0x50) == 0) // �ұ�Ϊ�� 
		{
			right = right / 2;
			pos.x = pos.x - CELL_WIDTH / 4;

		}
		if ((type & 0xa0) == 0) // ���Ϊ�� 
		{
			left = CELL_WIDTH / 2;
			pos.x = pos.x + CELL_WIDTH / 4;
		}
		cell->setTextureRect(Rect(left, top, right - left, bottom - top));
		cell->setPosition(pos); // ê��Ϊ�е�
	}
	else
	{
		if (cell)  //ê������
		{
			if (type != WATER)
			{
				cell->setTexture(getSpriteName(type));  //ˮ����ֿհ�
			}
			cell->setPosition(getPos(row, col));

			if(type == HOME2)
			{
				auto tempPos = cell->getPosition();
				cell->setPosition(Vec2(tempPos.x + CELL_WIDTH / 2, tempPos.y - CELL_HEIGHT / 2));
			}

		}
		else
		{
			this->createMapCell(row, col, type);
		}
	}
}