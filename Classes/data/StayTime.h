/***********************************************

����һ������Ϸ��ʼ��һֱ��¼�����ļ�ʱ����
����ʵ�ִ����ɾ�

***********************************************/

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class StayTime :public Node
{
public:
	static void start();
	//����ʱ�� ��λ ��
	static int getStayTime();
private:
	//���캯��˽�л���ֻ��ͨ��start����
	StayTime();
	void stayTimeUpdate(float dt);

	int stayTime;
};
