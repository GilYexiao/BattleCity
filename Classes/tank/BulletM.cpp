#include "BulletM.h"

/*����Ϊ�ӵ������࣬��Ҫ�ĺ������ṩһ�������ӵ��Ľӿڣ���ͳ���ӵ�����Ŀ*/
BulletM::BulletM()
{

}

BulletM::~BulletM()
{
}

bool BulletM::init()
{
	bool bRet = false;
	do
	{

		bRet = true;
	} while (false);
	return bRet;
}
//�õ��ӵ���Ŀ
int BulletM::getBulletNum(void* owner)
{
	auto num = 0;
	auto bullets = this->getChildren();
	for (auto i = 0; i < bullets.size(); i++)
	{
		auto bullet = (Bullet*)bullets.at(i);
		if (bullet->getOwner() == owner)
		{
			num++;
		}
	}
	return num;
}
//�����ӵ��Ľӿ�
void BulletM::createBullet(void* owner, float speed, int power, Vec2 pos, Direction direction,int distance)
{
	auto bullet = Bullet::create(owner, speed, power, pos, direction,distance);
	this->addChild(bullet);
}
//��ͣ��Ϸ�Ľӿ�
void BulletM::pauseGame()
{
	auto &bullets = this->getChildren();
	for (auto bullet : bullets)
	{
		//(static_cast<Sprite>bullet)->pause();
		bullet->pause();
	}
}
//���¿�ʼ��Ϸ�Ľӿ�
void BulletM::resumeGame()
{
	auto &bullets = this->getChildren();
	for (auto bullet : bullets)
	{
		//(static_cast<Sprite>bullet)->pause();
		bullet->resume();
	}
}