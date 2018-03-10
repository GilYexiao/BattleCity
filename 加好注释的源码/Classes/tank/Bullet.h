#pragma once
#include "cocos2d.h"
#include "data/Global.h"
#include "media\AudioM.h"
#include "media\BombM.h"
/*����Ϊ�ӵ��࣬��Ҫ�ĺ����д����ӵ��ĺ����������ӵ��ƶ������е���ײ��⣬
�����ͼ�߽硢��ͼ�ϰ���ӵ���̹���������жϼ��*/
USING_NS_CC;

class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();
	/**
	* �����ӵ�
	* owner �ӵ�������̹��
	* speed �ӵ��ٶ�
	* power �ӵ����� 0���ɴ��������ɴ��ư��ש��1�ɴ��������ɴ�������ש
	* pos �ӵ�λ��
	* direction �ӵ�����
	*/
	static Bullet* create(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance);
	bool init(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance);
	/* ��ȡ���ӵ�������̹�� */
	void* getOwner() { return _owner; }

private:
	void update(float dt);
	/* �ƶ� */
	void move();
	/* ��ײ��� */
	void collide();
	/* ���ͼ(��ͼ�߽缰�ϰ���)����ײ��� */
	void collideMap();
	/* ���ͼ�߽����ײ��� */
	void collideBorder();
	/* ���ͼ�ϰ������ײ��� */
	void collideObstacle();
	/* ���ӵ�����ײ��� */
	void collideBullet();
	/* ��̹�˵���ײ��� */
	void collideTank();
	/* AOE��� */
	void checkAOE();
	
	void* _owner;				// �������ӵ���̹�� 
	float _speed;				// �ӵ����ٶ� 
	int _power=0;				// �ӵ���ǿ�ȣ�0���ܴ��� 1���Դ����� 
	Vec2 _newPos;				// �ӵ���һ֡��λ�� 
	Direction _direction;		// �ӵ���λ�� 
	Vec2 _bombPos;				// �ӵ���ը��λ�� 
	bool _bomb;					// �ӵ��Ƿ�ը 
	float _dt;					// ��֮֡���ʱ���� 
	int _distance;				 //�ӵ����о���	
	float Bullet_p_x;			//�ӵ�����x����
	float Bullet_p_y;			//�ӵ�����y����
	int atk;					//���ӵ��Ĺ�����
};