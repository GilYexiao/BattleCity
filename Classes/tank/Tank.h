#pragma once
/*�������̹���࣬�����̹�˺͵з�̹�˵ĸ��࣬��Ҫ�ĺ�����̹���ƶ���������ƺ���
�������ͼ��̹�˵���ײ���*/
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
	/*�õ�̹�˵�HP*/
	int getHP() { return HP; }
	float getSPE() { return SPE; }
	//�õ�̹�˵Ĺ�����
	int getATK() { return ATK; }
	//�õ�̹�˵��ӵ���Ŀ
	int getBulletNum() { return bulletNumMAX; }
	//�õ�̹�˵��ٶ�
	void setSPE(float spe) { SPE = spe;}
	//����̹�˵Ĺ�����
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

	int HP;//����HP
	float SPE;//�����ٶ�
	int ATK;//���ù�����
	int bulletNumMAX;//�����ӵ������Ŀ
	float bulletSPE;//�����ӵ��ٶ�
	float bulletDistance;//�����ӵ����
	int bulletPower = 0;		// �ӵ�������(0���ɴ�������1�ɴ�����) 
	bool isAvoid = false;//�����Ƿ�����
};