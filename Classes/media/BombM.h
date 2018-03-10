#pragma once
#include "cocos2d.h"
#include "Bomb.h"
USING_NS_CC;
/* ��ը������ */
class BombM : public Layer
{
public:
	BombM();
	~BombM();
	CREATE_FUNC(BombM);
	/**
	* ������ը
	* type ��ը����
	* pos ��ըλ��
	*/
	void createBomb(BombType type, Vec2 pos);
	/* ��ͣ��Ϸ����ͣ�������б�ը������ */
	void pauseGame();
	/* ������Ϸ�������������б�ը������ */
	void resumeGame();
};
