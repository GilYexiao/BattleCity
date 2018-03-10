#pragma once
#include "cocos2d.h"
#include "Bullet.h"
/*����Ϊ�ӵ������࣬��Ҫ�ĺ������ṩһ�������ӵ��Ľӿڣ���ͳ���ӵ�����Ŀ*/
class Bullet;

USING_NS_CC;

/* �ӵ������� */
class BulletM : public Layer
{
public:
	BulletM();
	~BulletM();
	CREATE_FUNC(BulletM);
	bool init();
	/* ��ȡ��̹�˷�����ӵ���Ŀ */
	int getBulletNum(void* owner);
	/**
	* �����ӵ�
	* owner �ӵ�������̹��
	* speed �ӵ��ٶ�
	* power �ӵ����� 0���ɴ��������ɴ��ư��ש��1�ɴ��������ɴ�������ש
	* pos �ӵ�λ��
	* direction �ӵ�����
	* distance �ӵ�����
	*/
	void createBullet(void* owner, float speed, int power, Vec2 pos, Direction direction,int distance);
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* �ָ���Ϸ */
	void resumeGame();
};
