#pragma once

#include "cocos2d.h"
#include "data\Global.h"
#include "data\DataM.h"
#include "input\keyboardInput.h"
#include "data\TankData.h"

class GameScene;
class Stage;
class Tank;
class PlayerTank;
class TankM;
class EnemyTank;
USING_NS_CC;
class Tank : public Sprite {
public:
	Tank();
	~Tank();
	virtual bool init();
	//int getType() { return _type; }
	/* ���ӵ��� */
	virtual void hit(int atk)=0;
	int getHP() { return HP; }
	float getSPE() { return SPE; }
	int getATK() { return ATK; }
	int getBulletNum() { return bulletNumMAX; }
	void setSPE(float spe) { SPE = spe;}
	void setATK(int atk) { ATK = atk; }


protected:
	/* ��ʼ��λ�� */
	void initPos();
	/* ����λ�úͷ��� */
	void setPos(Vec2 pos, Direction direction);
	/* �����ƶ�	*/
	void moveUp();
	/* �����ƶ�	*/
	void moveRight();
	/* �����ƶ�	*/
	void moveDown();
	/* �����ƶ�	*/
	void moveLeft();
	/* ����תΪ����	*/
	void turnUp();
	/* ����תΪ����	*/
	void turnRight();
	/* ����תΪ����	*/
	void turnDown();
	/* ����תΪ����	*/
	void turnLeft();
	/* �������ƶ���Ϊ�����ƶ�ʱ������x���� */
	void adjustPosX();
	/* �������ƶ���Ϊ�����ƶ�ʱ������y���� */
	void adjustPosY();
	/* ���ͼ����ײ��� */
	bool collideMap();
	/* ��̹�˵���ײ��� */
	bool collideTank();
	/* ����Ƿ�������̹���ص� */
	bool overlapCheck();
	/* �����ӵ� */
	bool shoot();
//	/* ���߶���֡������ */
//	void addStep();


	Vec2 _newPos;			//�ƶ��������
	Direction _direction;	// ���� 
	float _dt;

	int HP;
	float SPE;
	int ATK;
	int bulletNumMAX;
	float bulletSPE;
	float bulletDistance;
	int bulletPower = 0;		// �ӵ�������(0���ɴ�������1�ɴ�����) 
	bool isAvoid = false;
};