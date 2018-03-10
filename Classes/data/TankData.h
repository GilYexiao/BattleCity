/***********************************************

�����������Ϸ������̹�˵Ļ������ݣ�����̹�˵��١�HP���������ȵȣ�
���⣬��ͨ��SP������㵱ǰ̹�˵�����

***********************************************/

#pragma once
#include "cocos2d.h"
#include "DataM.h"
USING_NS_CC;

class DataM;
class TankData :public Ref
{
public:
	TankData();
	static TankData *getInstance();
	int getHP();//�õ�HP
	float getSPE();							//��������/��
	int	getATK();							//������
	int getBulletNumMAX();
	float getBulletSPE();					//��������/��
	float getBulletDistance();				//��������
	bool isAOE();
	float getAvoidProbability();			//0��1,�ٶ��ͻر�
	int getDamageDiscount();				//int ���پ����˺�
	float getReadyInterval();				//��ȴʱ��
	bool isFireUp();						//�Ƿ�����
	bool isRebirth();						//�Ƿ������Ѫ 
	float getShieldTime();					//�޵�ʱ�� /��
	int getJumpAbility();					//��˸���룬��λ ����
	int getAtkInterval();					//������� ��λ ֡��	
private:
	DataM *dataM;
};
