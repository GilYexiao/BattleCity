#pragma once
/*������ǵз�̹���࣬��Ҫ�ĺ��������õз�̹�˵����ԣ�����̹�˵�Ѫ���������Ŀ���̳�̹����*/
#include "Tank.h"
#include "ui\CocosGUI.h"
using namespace ui;
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
/* ����̹���� */
class EnemyTank : public Tank
{
public:
	EnemyTank();
	~EnemyTank();
	static EnemyTank* create(int type, Vec2 pos);
	bool init(int type, Vec2 pos);
	virtual void hit(int atk);
	void dieCountBegin();
	bool setFireUp() { isFireUp = true; }

private:
	void update(float dt);

	//bool _bonus;		// �Ƿ��е��߽��� 
	//int _bonusStep;	    // ��������̹�˵�֡�� 
	int _type;//����
	float dieScale = 1;
	bool dieCountOn = false;
	bool isFireUp = false;//�Ƿ�����
	int count = 359;  //���ռ���
	Sprite *diecount = nullptr;
	//�������ֵ���������������
	int fullHP;
	Slider *enemyHPSlider;

};

