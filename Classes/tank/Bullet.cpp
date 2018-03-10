#include "Bullet.h"
#include "scene/GameScene.h"
#include "stage\Stage.h"
#include "data\TankData.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
/*����Ϊ�ӵ��࣬��Ҫ�ĺ����д����ӵ��ĺ����������ӵ��ƶ������е���ײ��⣬
�����ͼ�߽硢��ͼ�ϰ���ӵ���̹���������жϼ��*/

//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


Bullet::Bullet(){}

Bullet::~Bullet()
{
}
//�����ӵ�
Bullet* Bullet::create(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance)
{

	Bullet *pRet = new Bullet();
	if (pRet && pRet->init(owner, speed, power, pos, direction, distance))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
//����̹�����ͽ��д�������ͬ��̹���ӵ����Ͳ�ͬ�����õ�̹�˵��ٶȡ�λ�á�������̵Ȳ���
bool Bullet::init(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance)
{
	bool bRet = false;
	do
	{
		this->Sprite::init();  //Ϊ�˳����ȶ������ø��෽��

		Sprite *bulletImage;//��ǰ���ӵ�
		HeroType currentHType = DataM::getInstance()->getHType();
		if (owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
		{
			if (TypeATK == currentHType)
			{
				if (TankData::getInstance()->isAOE())
				{
					bulletImage = Sprite::create("Bullet1.png");
				}
				else //!isAOE
				{
					bulletImage = Sprite::create("Bullet0.png");
				}
			}
			else if (TypeDEF == currentHType)
			{
				bulletImage = Sprite::create("Bullet0.png");
			}
			else if (TypeSPE == currentHType)
			{
				bulletImage = Sprite::create("Bullet2.png");
				auto rotateAction = RotateBy::create(0.5f, -900);
				auto rotateForever = RepeatForever::create(rotateAction);
				bulletImage->runAction(rotateForever);
			}
		}
		else  //�з�̹��
		{
			bulletImage = Sprite::create("Bullet0.png");
		}

		this->addChild(bulletImage);

		_owner = owner;//�ӵ�������̹��
		_power = power;//�ӵ�������
		_speed = speed;//�ӵ����ٶ�
		_distance = distance;//�ӵ������
		_direction = direction;//�ӵ��ķ���
		atk = static_cast<Tank*>(owner)->getATK();  //���ӵ��Ĺ�����
		this->setPosition(pos);//����λ��
		this->setRotation((direction - 1) * 90);//���÷���
		_newPos = pos;//λ��
		this->move();//��ʼ�ƶ�

		Bullet_p_x = this->getPositionX();
		Bullet_p_y = this->getPositionY();

		this->scheduleUpdate();

		bRet = true;
	} while (false);
	return bRet;
}
//���ӵ������ж���ײ��⣬������������ò��ɼ�������ը
void Bullet::update(float dt)
{
	_dt = dt;
	if (_visible)
	{
		this->move();
		this->collide();
	}

	if (abs(_newPos.y - Bullet_p_y) >_distance || abs(_newPos.x - Bullet_p_x)>_distance) {
		this->setVisible(false);
		this->_bomb = true;
	}

	if (_visible)
	{
		this->setPosition(_newPos);
	}
	else
	{
		/*
		if (_bomb)
		{
			GameScene::getBombM()->createBomb(kBulletBomb, _bombPos);
		}*/
		this->removeFromParent();
	}
}
//�ӵ����ƶ�����
void Bullet::move()
{
	if (_direction == UP)//��������
	{
		_newPos.y = _position.y + _speed;
	}
	else if (_direction == DOWN)//��������
	{
		//_newPos.y = _position.y - _speed * 60 * _dt;
		_newPos.y = _position.y - _speed;
	}
	else if (_direction == LEFT)//��������
	{
		//_newPos.x = _position.x - _speed * 60 * _dt;
		_newPos.x = _position.x - _speed;
	}
	else if (_direction == RIGHT)//��������
	{
		//_newPos.x = _position.x + _speed * 60 * _dt;
		_newPos.x = _position.x + _speed;
	}
}
void Bullet::collide()//�ܵ���ײ���
{
	this->collideMap();			// ���ͼ����ײ��� 
	this->collideBullet();		// ���ӵ�����ײ��� 
	this->collideTank();		// ��̹�˵���ײ��� 
}
void Bullet::collideMap()//���ͼ����ײ���
{
	collideBorder();
	collideObstacle();
}

void Bullet::collideObstacle()//���ϰ������ײ���
{
	if (!_visible) return;
	auto col = getColNumberFromPosition(_newPos.x);
	auto row = getRowNumberFromPosition(_newPos.y);
	auto grid = false;
	auto stage = GameScene::getStage();
	int(*map)[MAP_COL] = NULL;
	stage->getMap(map);
	auto dx = 0.0f, dy = 0.0f;
	if (_direction == UP || _direction == DOWN)
	{
		if (!stage->isCanHit(row, col) && !stage->isCanHit(row, col - 1)) return;
		_bomb = true;
		if (_power == 1)	// �ɴ��������ɴ�������ש 
		{
			if ((map[row][col] <= GRID4 && map[row][col] >=GRID1) || (map[row][col] & 0x0f) == BRICK)
			{
				//����Ч
				if(((map[row][col] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}

			}

			if ((map[row][col - 1] <= GRID4 && map[row][col - 1] >= GRID1) || (map[row][col - 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row][col-1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}


		}
		else if (_power == 0) // ���ɴ��������ɴ��ư��ש 
		{
			if ((map[row][col] <= GRID4 && map[row][col] >= GRID1) || (map[row][col - 1] <= GRID4 && map[row][col - 1] >= GRID1))
			{
				grid = true;
			}

			if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()) && TankData::getInstance()->isAOE())
			{ 

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				if ((map[row][col] & 0x0f) == BRICK)
				{

					map[row][col] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if ((map[row][col - 1] & 0x0f) == BRICK)
				{

					map[row][col - 1] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
			else
			{

				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}


				if (_direction == UP && ((map[row][col] & 0x30) != 0 || (map[row][col - 1] & 0x30) != 0)) // �ӵ�������������ש�°벿��Ϊ�� 
				{
					map[row][col] &= 0xcf;		// ����ש���°벿�� 
					map[row][col - 1] &= 0xcf;
				}
				else if (_direction == DOWN && ((map[row][col] & 0xc0) != 0 || (map[row][col - 1] & 0xc0) != 0)) // �ӵ�������������ש�ϰ벿��Ϊ�� 
				{
					map[row][col] &= 0x3f;		// ����ש���ϰ벿�� 
					map[row][col - 1] &= 0x3f;
				}
				else
				{
					if (!grid) // ��������������һ�������Ļ���û���򵽺���ש 
					{
						/* ���ƺ�����ש��ʱ���޸��ӵ���ը��λ�� */
						if (_direction == UP)
						{
							dy = CELL_HEIGHT / 2;
						}
						else
						{
							dy = -CELL_HEIGHT / 2;
						}
						/* ���ƺ�����ש����Ϊǰ���ש�Ѵ��Ʋ��ܴ򵽺���ש�������൱�ڸ�שȫ�����ƣ� */
						map[row][col] &= 0x0f;
						map[row][col - 1] &= 0x0f;
					}
				}
				/* ש�Ľ�ȫ�Ƶ�ʱ���޸�����Ϊ�� */
				if (map[row][col] == BRICK)
				{
					map[row][col] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if (map[row][col - 1] == BRICK)
				{
					map[row][col - 1] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
		}

		if (map[row][col] == HOME3 || map[row][col] == HOME4 || map[row][col - 1] == HOME3 || map[row][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//��ҳɾ� ���ҳɾ�
			SuccessData::getInstance()->updateHomeBreakTime();

			//����Ч
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// �ұ����ƣ�����ʧ��
			NotificationCenter::getInstance()->postNotification("game_fail");
		
		}
		GameScene::getStage()->updateMapCell(row, col);
		GameScene::getStage()->updateMapCell(row, col - 1);
		//AOE���
		checkAOE();
	}
	else if (_direction == LEFT || _direction == RIGHT)
	{
		if (!stage->isCanHit(row, col) && !stage->isCanHit(row - 1, col)) return;
		_bomb = true;
		if (_power == 1)
		{
			if ((map[row][col] <= GRID4 && map[row][col] >= GRID1) || (map[row][col] & 0x0f) == BRICK)
			{
				//����Ч
				if (((map[row][col] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col] <= GRID4 && map[row - 1][col] >= GRID1) || (map[row - 1][col] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row-1][col] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (_power == 0)
		{
			if ((map[row][col] <= GRID4 && map[row][col] >= GRID1) || (map[row - 1][col] <= GRID4 && map[row - 1][col] >= GRID1))
			{
				grid = true;
			}

			if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()) && TankData::getInstance()->isAOE())
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);


				if ((map[row][col] & 0x0f) == BRICK)
				{
					map[row][col] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if ((map[row - 1][col] & 0x0f) == BRICK)
				{
					map[row - 1][col] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
			else
			{
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				}

				if (_direction == RIGHT && ((map[row][col] & 0xa0) != 0 || (map[row - 1][col] & 0xa0) != 0))
				{
					map[row][col] &= 0x5f;		// ����ש����벿�� 
					map[row - 1][col] &= 0x5f;
				}
				else if (_direction == LEFT && ((map[row][col] & 0x50) != 0 || (map[row - 1][col] & 0x50) != 0))
				{
					map[row][col] &= 0xaf;		// ����ש���Ұ벿�� 
					map[row - 1][col] &= 0xaf;
				}
				else
				{
					if (!grid)
					{
						if (_direction == RIGHT)
						{
							dx = CELL_WIDTH / 2;
						}
						else
						{
							dx = -CELL_WIDTH / 2;
						}
						map[row][col] &= 0x0f;
						map[row - 1][col] &= 0x0f;
					}
				}
				if (map[row][col] == BRICK)  //��ǰ��λ�ˣ������ǿ�ש��
				{
					map[row][col] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if (map[row - 1][col] == BRICK)  //��ǰ��λ�ˣ������ǿ�ש��
				{
					map[row - 1][col] = LAND;

					//�ӵ��ɾͣ��ӵ����
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
		}
		if (map[row][col] == HOME3 || map[row][col] == HOME4 || map[row - 1][col] == HOME3 || map[row - 1][col] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//��ҳɾ� ���ҳɾ�
			SuccessData::getInstance()->updateHomeBreakTime();

			//����Ч
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// �ұ����ƣ�����ʧ��
			NotificationCenter::getInstance()->postNotification("game_fail");
		}

		GameScene::getStage()->updateMapCell(row, col);
		GameScene::getStage()->updateMapCell(row - 1, col);
		//AOE���
		checkAOE();
	}

	if (_bomb)
	{
		this->setVisible(false);
		_bombPos.x = _newPos.x + dx;
		_bombPos.y = _newPos.y + dy;
	}
	//if (_owner == GameScene::getTankM()->getPlayerTank())
	//{
	//	if (_power == 0 && grid)
	//	{
	//		/* �������Ҵ���ʱ����Ч */
	//		/*AudioM::play2d(A_HIT_OBSTACLE);*/
	//	}
	//	else
	//	{
	//		/* ����ש����ʱ����Ч */
	//		/*AudioM::play2d(A_OBSTACLE_BOMB);*/
	//	}
	//}
}

//�߽����ײ���
void Bullet::collideBorder()
{
	int(*map)[MAP_COL] = NULL;
	GameScene::getStage()->getMap(map);
	if (_newPos.x <= LEFT_EAGE || _newPos.x >= RIGHT_EAGE ||
		_newPos.y <= BOTTOM_EAGE|| _newPos.y >= TOP_EAGE)
	{
		//if (_owner == GameScene::getTankM()->getPlayerTank())
		//{
		//	AudioM::play2d(A_HIT_OBSTACLE);
		//}
		_bomb = true;
		this->setVisible(false);
		if (_newPos.x < 0)
		{
			_bombPos.x = 0;
		}
		else if (_newPos.x > MAP_WIDTH)
		{
			_bombPos.x = MAP_WIDTH;
		}
		else
		{
			_bombPos.x = _newPos.x;
		}

		if (_newPos.y < 0)
		{
			_bombPos.y = 0;
		}
		else if (_newPos.y > MAP_HEIGHT)
		{
			_bombPos.y = MAP_HEIGHT;
		}
		else
		{
			_bombPos.y = _newPos.y;
		}
	}
}
//��̹�˵���ײ���
void Bullet::collideTank()
{
	Vector<Tank*> &tanks = GameScene::getTankM()->getAllTanks();//��ȡ����̹��
	PlayerTank* playerTank = GameScene::getTankM()->getPlayerTank();//��ȡ���̹��
	for (auto tank : tanks)
	{
		/* �ж��Ƿ������̹���ӵ��򵽵���̹�˻����̹���ӵ������̹�˵���� */
		if ((_owner == playerTank && tank != playerTank) || (_owner != playerTank && tank == playerTank))
		{
			auto otherPos = tank->getPosition();  //̹���е�
			if (_newPos.x <= otherPos.x + CELL_WIDTH && _position.x >= otherPos.x - CELL_WIDTH &&
				_newPos.y <= otherPos.y + CELL_HEIGHT && _position.y >= otherPos.y - CELL_HEIGHT)
			{
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()) && TankData::getInstance()->isAOE())
				{
					checkAOE();  //AOE���,���а�������hit����
				}
				else
				{
					tank->hit(atk);
				}

				this->setVisible(false);
				_bomb = true;
				_bombPos.x = _newPos.x;
				_bombPos.y = _newPos.y;
				break;
			}
		}
	}
}
//���ӵ������ײ���
void Bullet::collideBullet()
{
	auto &bullets = GameScene::getBulletM()->getChildren();
	for (auto bullet : bullets)
	{
		auto collide = false;
		if (bullet == this || !bullet->isVisible()) continue;
		auto playTank = GameScene::getTankM()->getPlayerTank();
		/* �����ӵ����������̹�˷���ģ������ǵ���̹�˷�����ӵ�������̹�˵��ӵ�����֮�䲻���� */
		if (((Bullet*)bullet)->getOwner() != playTank && _owner != playTank) continue;
		/* �ж������ӵ��Ƿ��ཻ */
		if (this->getBoundingBox().intersectsRect(bullet->getBoundingBox()))  //getBoundingBox�������� 
		{
			collide = true;
		}
		else
		{
			/* ����������ӵ�����û�ֱཻ�Ӵ��������Ը�����֮֡��������ϵ�ж� */  //???????? ����
			auto otherPos = bullet->getPosition();
			if (abs(_newPos.x - otherPos.x) < 1)  // �ж��Ƿ�ͬ�У�float���ھ������⣬�����С�ں�С��һ������ʱ����Ϊ��ȣ�  
			{
				if (_position.y < otherPos.y && _newPos.y >= otherPos.y)
				{
					collide = true;
				}
				else if (_position.y > otherPos.y && _newPos.y <= otherPos.y)
				{
					collide = true;
				}
			}
			if (abs(_newPos.y - otherPos.y) < 1)  // �ж��Ƿ�ͬ�� 
			{
				if (_position.x < otherPos.x && _newPos.x >= otherPos.x)
				{
					collide = true;
				}
				else if (_position.x > otherPos.x && _newPos.x <= otherPos.x)
				{
					collide = true;
				}
			}
		}
		if (collide)
		{
			this->setVisible(false);
			bullet->setVisible(false);
		}
	}
}

//����д
void Bullet::checkAOE()
{
	if (_owner != static_cast<void *>(GameScene::getTankM()->getPlayerTank()) || TankData::getInstance()->isAOE() == false)
	{
		return;
	}

	auto col = getColNumberFromPosition(_newPos.x);
	auto row = getRowNumberFromPosition(_newPos.y);
	auto stage = GameScene::getStage();
	int(*map)[MAP_COL] = NULL;
	stage->getMap(map);
	//�˴���������diriction��ö��ֵֻд���º������������������Ϊ�˸���ֱ�ۣ�����4������ж�
	if (row + 1 < MAP_ROW && UP == _direction)
	{
		//���ϰ���ļ��
		if (1 == _power)
		{
			if ((map[row + 1][col] <= GRID4 &&map[row + 1][col] >= GRID1) || (map[row + 1][col] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row+1][col] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row + 1][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row + 1][col - 1] <= GRID4 &&map[row + 1][col - 1] >= GRID1) || (map[row + 1][col - 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row+1][col-1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}


				map[row + 1][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if(0 == _power)
		{
			if ((map[row + 1][col] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row + 1][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row + 1][col - 1] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row + 1][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}


		//��̹�˵ļ��
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //̹���е�
			if (_newPos.x <= tankPos.x + CELL_WIDTH && _newPos.x >= tankPos.x - CELL_WIDTH &&
				_newPos.y <= tankPos.y && _newPos.y >= tankPos.y - 2*CELL_HEIGHT)
			{
				tank->hit(atk);
			}
		}

		if (map[row + 1][col] == HOME3 || map[row + 1][col] == HOME4 || map[row + 1][col - 1] == HOME3 || map[row + 1][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//��ҳɾ� ���ҳɾ�
			SuccessData::getInstance()->updateHomeBreakTime();

			//����Ч
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// �ұ����ƣ�����ʧ��
			NotificationCenter::getInstance()->postNotification("game_fail");

		}
		GameScene::getStage()->updateMapCell(row + 1, col);
		GameScene::getStage()->updateMapCell(row + 1, col - 1);
	}

	if (row - 1 >= 0 && DOWN == _direction)
	{
		//���ϰ���ļ��
		if (1 == _power)
		{
			if ((map[row - 1][col] <= GRID4 &&map[row - 1][col] >= GRID1) || (map[row - 1][col] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row-1][col] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] <= GRID4 &&map[row - 1][col - 1] >= GRID1) || (map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row-1][col-1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (0 == _power)
		{
			if ((map[row - 1][col] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}

		if (map[row -1][col] == HOME3 || map[row -1][col] == HOME4 || map[row - 1][col - 1] == HOME3 || map[row - 1][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//��ҳɾ� ���ҳɾ�
			SuccessData::getInstance()->updateHomeBreakTime();

			//����Ч
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// �ұ����ƣ�����ʧ��
			NotificationCenter::getInstance()->postNotification("game_fail");

		}
		GameScene::getStage()->updateMapCell(row - 1, col);
		GameScene::getStage()->updateMapCell(row - 1, col - 1);

		//��̹�˵ļ��
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //̹���е�
			if (_newPos.x <= tankPos.x + CELL_WIDTH && _newPos.x >= tankPos.x - CELL_WIDTH &&
				_newPos.y <= tankPos.y + 2 * CELL_HEIGHT && _newPos.y >= tankPos.y)
			{
				tank->hit(atk);
			}
		}
	}

	if (col - 1 >= 0 && LEFT == _direction)
	{
		//���ϰ���ļ��
		if (1 == _power)
		{
			if ((map[row][col - 1] <= GRID4 &&map[row][col - 1] >= GRID1) || (map[row][col - 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row][col-1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] <= GRID4 &&map[row - 1][col - 1] >= GRID1) || (map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row-1][col-1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (0 == _power)
		{
			if ((map[row][col - 1] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row][col-1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col - 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		if (map[row][col - 1] == HOME3 || map[row][col - 1] == HOME4 || map[row - 1][col - 1] == HOME3 || map[row - 1][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//��ҳɾ� ���ҳɾ�
			SuccessData::getInstance()->updateHomeBreakTime();

			//����Ч
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// �ұ����ƣ�����ʧ��
			NotificationCenter::getInstance()->postNotification("game_fail");
		}
		GameScene::getStage()->updateMapCell(row, col - 1);
		GameScene::getStage()->updateMapCell(row - 1, col - 1);

		//��̹�˵ļ��
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //̹���е�
			if (_newPos.x <= tankPos.x + 2 * CELL_WIDTH&& _newPos.x >= tankPos.x  &&
				_newPos.y <= tankPos.y + CELL_HEIGHT && _newPos.y >= tankPos.y - CELL_HEIGHT)
			{
				tank->hit(atk);
			}
		}
	}

	if (col + 1 < MAP_COL && RIGHT == _direction)
	{
		//���ϰ���ļ��
		if (1 == _power)
		{
			if ((map[row][col + 1] <= GRID4 &&map[row][col + 1] >= GRID1) || (map[row][col + 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row][col+1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}


				map[row][col + 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col + 1] <= GRID4 &&map[row - 1][col + 1] >= GRID1) || (map[row - 1][col + 1] & 0x0f) == BRICK)
			{

				//����Ч
				if (((map[row-1][col+1] & 0x0f) == BRICK))
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col + 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (0 == _power)
		{
			if ((map[row][col + 1] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row][col + 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col + 1] & 0x0f) == BRICK)
			{

				//����Ч,���㸴�ƣ��ʶ�ע���ڴ�
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col + 1] = LAND;

				//�ӵ��ɾͣ��ӵ����
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}

		if (map[row][col + 1] == HOME3 || map[row][col + 1] == HOME4 || map[row - 1][col + 1] == HOME3 || map[row - 1][col + 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//��ҳɾ� ���ҳɾ�
			SuccessData::getInstance()->updateHomeBreakTime();

			//����Ч
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// �ұ����ƣ�����ʧ��
			NotificationCenter::getInstance()->postNotification("game_fail");
		}
		GameScene::getStage()->updateMapCell(row, col + 1);
		GameScene::getStage()->updateMapCell(row - 1, col + 1);

		//��̹�˵ļ��
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //̹���е�
			if (_newPos.x <= tankPos.x && _newPos.x >= tankPos.x - 2 * CELL_WIDTH  &&
				_newPos.y <= tankPos.y + CELL_HEIGHT && _newPos.y >= tankPos.y - CELL_HEIGHT)
			{
				tank->hit(atk);
			}
		}
	}
}