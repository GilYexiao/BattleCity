#include "Tank.h"
#include <vector>
#include "scene\GameScene.h"
#include "stage\Stage.h"

/*�������̹���࣬�����̹�˺͵з�̹�˵ĸ��࣬��Ҫ�ĺ�����̹���ƶ���������ƺ���
�������ͼ��̹�˵���ײ���*/
Tank::Tank() {

}

Tank::~Tank() {

}

bool Tank::init() {
	return true;
}
//����̹������
void Tank::setPos(Vec2 pos, Direction direction) {
	_direction = direction;
	this->setPosition(pos);
	_newPos = pos;

}
//�����ƶ�
void Tank::moveUp()
{
	//_newPos.y = _position.y + _speed * 60 * _dt;
	_newPos.y = _position.y + SPE;
	//this->addStep();
}
//�����ƶ�
void Tank::moveDown()
{
	//_newPos.y = _position.y - _speed * 60 * _dt;
	_newPos.y = _position.y - SPE;
	//this->addStep();
}
//�����ƶ�
void Tank::moveLeft()
{
	//_newPos.x = _position.x - _speed * 60 * _dt;
	_newPos.x = _position.x - SPE;
	//this->addStep();
}
//�����ƶ�
void Tank::moveRight()
{
	//_newPos.x = _position.x + _speed * 60 * _dt;
	_newPos.x = _position.x + SPE;
	//this->addStep();
}
//����ת��
void Tank::turnLeft()
{
	if (_direction == UP || _direction == DOWN)
		adjustPosY();
	_direction = LEFT;
	if (this == GameScene::getTankM()->getPlayerTank()) {
		Sprite *tankImage = static_cast<Sprite *>(this->getChildByName("tankSkin"));
		tankImage->setRotation(270);
	}
	else
	{
		Sprite *enemyTankImage = static_cast<Sprite *>(this->getChildByName("enemyTankImage"));
		enemyTankImage->setRotation(90);
	}
	if (isAvoid == true)	this->setOpacity(50);
}
//����ת��
void Tank::turnRight()
{
	if (_direction == UP || _direction == DOWN)
		adjustPosY();
	_direction = RIGHT;
	if (this == GameScene::getTankM()->getPlayerTank()) {
		Sprite *tankImage = static_cast<Sprite *>(this->getChildByName("tankSkin"));
		tankImage->setRotation(90);
	}
	else
	{
		Sprite *enemyTankImage = static_cast<Sprite *>(this->getChildByName("enemyTankImage"));
		enemyTankImage->setRotation(270);
	}
	if (isAvoid == true)	this->setOpacity(50);
}
//����ת��
void Tank::turnUp()
{
	if (_direction == RIGHT || _direction == LEFT)
		adjustPosX();
	_direction = UP;
	if (this == GameScene::getTankM()->getPlayerTank()) {
		Sprite *tankImage = static_cast<Sprite *>(this->getChildByName("tankSkin"));
		tankImage->setRotation(0);
	}
	else
	{
		Sprite *enemyTankImage = static_cast<Sprite *>(this->getChildByName("enemyTankImage"));
		enemyTankImage->setRotation(180);
	}
	if (isAvoid == true)	this->setOpacity(50);
}
//����ת��
void Tank::turnDown()
{
	if (_direction == RIGHT || _direction == LEFT)
		adjustPosX();
	_direction = DOWN;
	if (this == GameScene::getTankM()->getPlayerTank()) {
		Sprite *tankImage = static_cast<Sprite *>(this->getChildByName("tankSkin"));
		tankImage->setRotation(180);
	}
	else
	{
		Sprite *enemyTankImage = static_cast<Sprite *>(this->getChildByName("enemyTankImage"));
		enemyTankImage->setRotation(0);
	}
	if (isAvoid == true)	this->setOpacity(50);
}
//�����е�У׼
void Tank::adjustPosX()//��У׼
{
	float n = (_position.x- MAP_ORIGIN.x) / CELL_WIDTH;
	
	if ((int)(n * 10) % 10 < 5) // �ж�̹������ӽ���һ�� 
	{
		_newPos.x = (int)n * CELL_WIDTH + MAP_ORIGIN.x;
	}
	else
	{
		_newPos.x = (int)(n + 1) * CELL_WIDTH + MAP_ORIGIN.x;
	}
	this->setPositionX(_newPos.x);
}
//�����е�У׼
void Tank::adjustPosY()//��У׼
{
	float n = (_position.y - MAP_ORIGIN.y) / CELL_HEIGHT;
	if ((int)(n * 10) % 10 < 5) // �ж�̹������ӽ���һ�� 
	{
		_newPos.y = (int)n * CELL_HEIGHT + MAP_ORIGIN.y;
	}
	else
	{
		_newPos.y = (int)(n + 1) * CELL_HEIGHT + MAP_ORIGIN.y;
	}
	this->setPositionY(_newPos.y);
}
//���ͼ����ײ���
bool Tank::collideMap()
{
	int row, col;
	auto collide = false;
	auto stage = GameScene::getStage();
	if (_direction == UP)
	{
		col = getColNumberFromPosition(_newPos.x);
		row = getRowNumberFromPosition(_newPos.y);
		if (row > MAP_ROW - 2 || !stage->isCanWalk(row+1, col) || !stage->isCanWalk(row+1, col - 1))
		{
			_newPos.y = getPos(row, col).y - CELL_HEIGHT / 2;
			collide = true;
		}
	}
	else if (_direction == DOWN)
	{
		col = getColNumberFromPosition(_newPos.x);
		row = getRowNumberFromPosition(_newPos.y);
		if (row < 1 || !stage->isCanWalk(row-1, col) || !stage->isCanWalk(row-1, col - 1))
		{
			_newPos.y = getPos(row, col).y  + CELL_HEIGHT / 2;
			collide = true;
		}
	}
	else if (_direction == LEFT)
	{
		col = getColNumberFromPosition(_newPos.x);
		row = getRowNumberFromPosition(_newPos.y);
		if (col < 1 || !stage->isCanWalk(row, col-1) || !stage->isCanWalk(row - 1, col-1))
		{
			_newPos.x = getPos(row, col).x + CELL_WIDTH / 2;
			collide = true;
		}
	}
	else if (_direction == RIGHT)
	{
		col = getColNumberFromPosition(_newPos.x);
		row = getRowNumberFromPosition(_newPos.y);
		if (col > MAP_COL - 2 || !stage->isCanWalk(row, col+1) || !stage->isCanWalk(row - 1, col+1))
		{
			_newPos.x = getPos(row, col-1).x + CELL_WIDTH / 2;
			collide = true;
		}
	}
	return collide;
}
//��̹�˵���ײ���
bool Tank::collideTank()
{
	auto collide = false;
	auto &tanks = GameScene::getTankM()->getAllTanks();
	for (auto i = 0; i < tanks.size(); i++)
	{
		auto tank = tanks.at(i);
		if (tank == this) continue;
		auto otherPos = tank->getPosition();
		if (_newPos.x > otherPos.x - 2 * CELL_WIDTH && _newPos.x < otherPos.x + 2 * CELL_WIDTH)
		{
			if (_position.y >= otherPos.y + 2 * CELL_HEIGHT && _newPos.y < otherPos.y + 2 * CELL_HEIGHT)
			{
				_newPos.y = otherPos.y + 2 * CELL_HEIGHT;
				collide = true;
			}
			if (_position.y <= otherPos.y - 2 * CELL_HEIGHT && _newPos.y > otherPos.y - 2 * CELL_HEIGHT)
			{
				_newPos.y = otherPos.y - 2 * CELL_HEIGHT;
				collide = true;
			}
		}
		if (_newPos.y > otherPos.y - 2 * CELL_HEIGHT && _newPos.y < otherPos.y + 2 * CELL_HEIGHT)
		{
			if (_position.x >= otherPos.x + 2 * CELL_WIDTH && _newPos.x < otherPos.x + 2 * CELL_WIDTH)
			{
				_newPos.x = otherPos.x + 2 * CELL_WIDTH;
				collide = true;
			}

			if (_position.x <= otherPos.x - 2 * CELL_WIDTH && _newPos.x > otherPos.x - 2 * CELL_WIDTH)
			{
				_newPos.x = otherPos.x - 2 * CELL_WIDTH;
				collide = true;
			}
		}
	}
	return collide;
}
//�ص������
bool Tank::overlapCheck()
{
	auto overlap = false;
	auto &tanks = GameScene::getTankM()->getAllTanks();
	for (auto i = 0; i < tanks.size(); i++)
	{
		auto tank = tanks.at(i);
		if (tank == this) continue;
		auto otherPos = tank->getPosition();
		/* ̹��ǰ������һ̹���ཻ��ı����߷�������ж��ཻ�͸ı䷽����ᷢ����ֻ̹�˻�һֱ��תȦ�� */
		if (_position.x > otherPos.x - 2 * CELL_WIDTH && _position.x < otherPos.x + 2 * CELL_WIDTH)
		{
			if (_direction == UP && _position.y > otherPos.y - 2 * CELL_HEIGHT && _position.y < otherPos.y)
			{
				overlap = true;
			}
			else if (_direction == DOWN && _position.y > otherPos.y && _position.y < otherPos.y + 2 * CELL_HEIGHT)
			{
				overlap = true;
			}
		}
		if (_position.y > otherPos.y - 2 * CELL_HEIGHT && _position.y < otherPos.y + 2 * CELL_HEIGHT)
		{
			if (_direction == LEFT && _position.x < otherPos.x + 2 * CELL_WIDTH && _position.x > otherPos.x)
			{
				overlap = true;
			}
			else if (_direction == RIGHT && _position.x < otherPos.x && _position.x > otherPos.x - 2 * CELL_WIDTH)
			{
				overlap = true;
			}
		}
	}
	return overlap;
}
//���
bool Tank::shoot()
{
	auto isShoot = false;
	Vec2 bulletPos;
	auto bulletNum = GameScene::getBulletM()->getBulletNum(this);
	if (!(bulletNum < bulletNumMAX)) return isShoot;

	if (_direction == UP)
	{
		bulletPos.x = _position.x;
		bulletPos.y = _position.y + CELL_HEIGHT;
	}
	else if (_direction == DOWN)
	{
		bulletPos.x = _position.x;
		bulletPos.y = _position.y - CELL_HEIGHT;
	}
	else if (_direction == LEFT)
	{
		bulletPos.x = _position.x - CELL_WIDTH;
		bulletPos.y = _position.y;
	}
	else if (_direction == RIGHT)
	{
		bulletPos.x = _position.x + CELL_WIDTH;
		bulletPos.y = _position.y;
	}
	GameScene::getBulletM()->createBullet(this, bulletSPE,bulletPower, bulletPos, _direction,bulletDistance);
	isShoot = true;

	return isShoot;
}