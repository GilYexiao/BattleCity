/***********************************************

��������������ը����

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
enum BombType			// ��ը���� 
{

	kTankBomb,			// ̹�˱�ը 
	//kStrongholdBomb,	// ��Ӫ��ը 
	kBulletBomb			// �ӵ���ը 
};

/* ��ը�� */
class Bomb : public Sprite
{
public:
	Bomb();
	~Bomb();
	/**
	* ������ը
	* type ��ը����
	*/
	static Bomb* create(BombType type);
	virtual bool init(BombType type);
private:
	BombType _type;
};