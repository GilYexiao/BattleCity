#pragma once
#include "cocos2d.h"
/*����Ϊ�ӵ��࣬��Ҫ�ĺ����д����ӵ��ĺ����������ӵ��ƶ������е���ײ��⣬
�����ͼ�߽硢��ͼ�ϰ���ӵ���̹���������жϼ��*/
USING_NS_CC;
// ������������
enum BonusType		 
{
	hpUp = 1,		// hp+5��������ֵ+5 
	powerUp,		// power+1���ӵ�����+5
	miss,			// miss
	statusUp		//��ɫbuff,���Լӹ��������ٶ�
};

/* ���������� */
class Bonus : public Sprite
{
public:
	Bonus();
	~Bonus();
	static Bonus* create(BonusType type, Vec2 pos);//�������ߣ����ͣ����꣩
	bool init(BonusType type,Vec2 pos);
	bool isCollidePlayer();//���������ײ��̹�˽�����ײ��⣬�ж��Ƿ������̹��

private:
	void update(float dt);
	/* �Ƿ������̹�˽Ӵ� */

	BonusType _type;	// ������������ 
};