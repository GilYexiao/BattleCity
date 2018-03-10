#pragma once
/*�������̹�˵��࣬��Ҫ�Ĺ��ܾ��Ǽ̳�̹���࣬ͬʱ�ֶ�̹�˷Ŵ��н���ʵ�֣�����̹�����Լӳɵĺ���*/
#include "Tank.h"
class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
class PlayerTank : public Tank
{
public:
	PlayerTank();
	~PlayerTank();
	static PlayerTank* create(HeroType heroType);
	virtual void hit(int atk);
	bool init(HeroType type);

	void setAvo(float avo) { AvoidProbability = avo; }
	/* ��ʼ��λ�� */
	void initPos();

	/* ��Ϸ��ͣ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/*Bonus*/
	void addHP();//��Ѫ
	void powerUp();//������
	void missUp();//������
	void statusUp();//��buff
	bool FireUpStatus() { return FireUp; }//�Ƿ������յ�Ч��


private:
	void update(float dt);
	void shieldOn();//�޵�
	void speUp();//����
	void dieCountAll();//�������̹��
	bool collidePos(Vec2 pos);//
	bool overlapCheckPos(Vec2 pos);

	Sprite* _shield;
	HeroType _heroType;
	float AvoidProbability;

	bool isShield = false;
	bool isAOE;
	bool FireUp = false;				
	int DamageDiscount;			//int
	
	float shieldTime=5.0;
	int jumpAbility=3;//��������
	bool isRebirth = false;
	int atkInterval=0;

	Vec2 _oldpos;				//for speUP()

	
};